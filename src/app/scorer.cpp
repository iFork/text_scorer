
#include "scorer.hpp"

#include <plog/Log.h>

//#include <string>
#include <boost/next_prior.hpp>
#include <algorithm>

namespace instigate {
namespace text_scorer {
namespace app {


scorer::scorer(const std::vector<std::string>& word_sequence):
    //m_word_sequence(word_sequence),
    //TODO: RECONSIDER: restructure stub_dictionary as a vector of 
    //stub_info (extending stub_info as a struct with a stub string,
    //retire unordered_set of stub_dictionary
    m_stubs(word_sequence, MAX_TERM_LENGTH)
{
    PLOGD << "Constructing scorer at " << this ;
    //TODO: overload << op for string vector ?
    /* PLOGV << "with word_sequence `" << word_sequence << "`"; */
}

scorer::~scorer()
{
    PLOGD << "Destructing scorer at " << this ;
}

//calculate score against give score provider and scoring policy
void scorer::score_against(const score_provider& sp, 
                            const scoring_policy policy)
{

    PLOGD << "Called...";
    fetch_scores(sp);
    bounce(policy);
    sum_scores();
}

//TODO: void pretty_print_result()


//fetch score matrices from term dictionary, store in m_scores
void scorer::fetch_scores(const score_provider& sp)
{
    PLOGD << "Called ...";
    dictionary::stub_dictionary::iterator stub_it = m_stubs.begin();
    for(; stub_it != m_stubs.end(); stub_it++) {
        if (!is_stopword(stub_it, sp)) {
            update_stub_info(stub_it, sp);
            const bool this_is_match = 
                stub_it->second.get<dictionary::tuple_elem_has_matched>();
            if(this_is_match) {
                push_score(stub_it);
            }
        }
    } 
}

//check if stub is a stop-word 
bool scorer::is_stopword(
        const dictionary::stub_dictionary::iterator stub_it,
        const score_provider& sp)
{
    PLOGD << "Called...";
    const dictionary::term_list* stopword_list_p = 
                                        sp.get_stopwords_ptr();
    assert(stopword_list_p); 
    //NOTE: Question: may be asserts inside getters suffice? 
    //May be no - purposes do not mix 
    if(stopword_list_p->exists(stub_it->first)) {
       /* stub_it->second.get<dictionary::tuple_elem_is_stop_word>() */ 
       /*                                  = true; */
        PLOGD << "`" << stub_it->first << "`" << " is stopword";
        return true;
    }
    else {
        PLOGV << "`" << stub_it->first << "`" << " is not a stopword";
        return false;
    }
}

//get score matrix of a stub present in a term dictionary,
//set match flag
void scorer::update_stub_info(
        const dictionary::stub_dictionary::iterator stub_it,
        const score_provider& sp)
{
    PLOGD << "Called...";
    const dictionary::term_dictionary* terms_dict_p = 
                                        sp.get_term_dictionary_ptr();
    assert(terms_dict_p);
    dictionary::term_dictionary::const_iterator found_it = 
                                terms_dict_p->find(stub_it->first);
    if(found_it != terms_dict_p->cend()) {
        stub_it->second.get<dictionary::tuple_elem_has_matched>() = true;
        score_matrix::score_matrix& stub_score_matrix = 
            stub_it->second.get<dictionary::tuple_elem_score_matrix>();
        stub_score_matrix = found_it->second; 
        PLOGD << "`" << stub_it->first << "`" 
              << " has matched and its score matrix is: "
              << stub_score_matrix;
    }
    else {
        PLOGV << "`" << stub_it->first << "`" 
              << " has no match in terms dictionary";
    }
}

/*
 * TODO: CONSIDER: change m_scores / scoring_info structure depending 
 * on debug macro - adding original terms - on top of spans
 * to ease debug tracing 
 *  #ifdef DEBUG_VERBOSE
 *      std::string* term
 *  #endif //DEBUG_VERBOSE
 *  OR: as performance cost of adding a pointer is low,
 *  may be - just always have it ? 
 */
//initialize scoring_info for the term, push it into m_scores
void scorer::push_score(
        const dictionary::stub_dictionary::iterator stub_it)
{
    PLOGD << "Called ...";
    scoring_info si;
    si.term_span_p = &stub_it->second.get<dictionary::tuple_elem_span>();
    si.term_score_p = 
    &stub_it->second.get<dictionary::tuple_elem_score_matrix>();
    m_scores.push_back(si);
    PLOGV << "scoring_info pushed is: " << si;
}


//bounce terms per given scoring_policy
void scorer::bounce(const scoring_policy policy)
{
    PLOGD << "Called...";
    std::sort(m_scores.begin(), m_scores.end());
    PLOGV << "scoring_info's sorted";
    switch (policy) {
        case big_eats_littles_bd:
            bounce_small_terms_bd();
            break;
        case littles_survives: 
            //nothing to bounce
            break;
    }
}

//set bounced flag for terms superseded by bigger terms
//check if there are other (proceeding) terms with at least partial overlap
//check if the length of the (proceeding) overlapping term is greater than the 
//length of this term, if yes, bounce that term
void scorer::bounce_small_terms_bd()
{
    PLOGD << "Called...";
    std::vector<scoring_info>::iterator this_it = m_scores.begin();
    std::vector<scoring_info>::iterator next_it = boost::next(this_it);
    std::vector<scoring_info>::iterator end_it = m_scores.end();
    while(next_it != end_it) {
        assert(this_it->term_span_p);
        const dictionary::span& this_span = *(this_it->term_span_p);
        for(; next_it != end_it; next_it++) {
            assert(next_it->term_span_p);
            const dictionary::span& next_span = *(next_it->term_span_p);
            if(this_span.has_overlap_with(next_span)) {
                //precondition: arguments come sorted in non-descending order
                assert(this_span < next_span);
                //TODO: possibility to optimize: once has_overlap_with returns
                //false - next terms will have no more overlaps
                if(next_span.is_longer_than(this_span)) {
                    //if this term is shorter than overlapping neighbor, 
                    //this term is bounced
                    this_it->bounced = true;
                    PLOGV << "Term with span `" << this_span
                        << "` was bounced by the bigger term with span `"
                        << next_span << "`";
                }
                else {
                    //if this term has equal (or bigger) length with the 
                    //overlapping neighbor, neighbor is bounced
                    next_it->bounced = true;
                    PLOGV << "Term with span `" << next_span
                        << "` was bounced by the left-standing term with span `"
                        << this_span << "`";
                }
            }
        }
        this_it++;
        next_it = boost::next(this_it);
    }
}

void scorer::sum_scores()
{
    PLOGD << "Called...";
    std::vector<scoring_info>::const_iterator it = m_scores.begin();
    /* std::vector<scoring_info>::iterator end_it = m_scores.end(); */
    for(; it != m_scores.end(); it++) {
        if(!it->bounced) {
            assert(it->term_score_p);
            m_total_score += *(it->term_score_p);      
        }
    }
    PLOGV << "resulted total score is: " << m_total_score;
}

} //app
} //text_scorer
} //instigate

