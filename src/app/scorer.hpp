/**
 * @file 
 */

#ifndef TEXT_SCORER_APP_SCORER_HPP
#define TEXT_SCORER_APP_SCORER_HPP 

#include "score_provider.hpp"
#include "scoring_info.hpp"

#include "dictionary/stub_dictionary.hpp"

#include <string>


namespace instigate {
namespace text_scorer {
namespace app {

/**
 * Manage scoring of a word_sequence
 */
class scorer {

public:
    //Public static constants
    /**
     * Maximum length of term considered when 
     * synthesizing terms from a word sequence
     */
    static const size_t MAX_TERM_LENGTH = 10;
    //TODO: get from upstream classes ??

    //Public nested helper enum 
    /**
     * Scoring policies supported.
     */
    enum scoring_policy {
        /**
         * Big term eats small terms in both directions.
         * Terms which share some part with a bigger term 
         * are not accounted.
         * Score only of the bigger (longer) term is accounted.
         * Precedence race: If terms share a part and have equal length,  
         * only left-side term is accounted. 
         */
        big_eats_littles_bd,

        /*
         * TODO: DISCUSS
         * Terms which are also part of a bigger super-term are not accounted.
         * Score only of this super-term is accounted. 
         * Precedence of equal-length terms is left-to-right.
         */
        //superterm_supersedes_ltr,
        /**
         * Terms which are also part of a bigger term are accounted.
         * Score of all super-term and sub-terms are accounted. 
         */
       littles_survives
    };

    //C-tor, d-tor
    /**
     * C-tor based on word_sequence input
     * @param word_sequence string to be scored 
     */
    scorer(const std::vector<std::string>& word_sequence);
    
    /**
     * D-tor
     */
    ~scorer();

    /**
     * Evaluate score of the word sequence according to score_provider 
     * specification.
     * @param sp score_provider to evaluate word_sequence against
     * @remark Result can be accessed via respective member accessors.
     */
    void score_against(const score_provider& sp, const scoring_policy policy);

private:
    //Private data members

    //TODO: maybe convert m_word_sequence string to pointer ?
    //to spare memory or DROP ?
    //std::string m_word_sequence; // or word_sequence pre-validated

    dictionary::stub_dictionary m_stubs;
    std::vector<scoring_info> m_scores;
    score_matrix::score_matrix m_total_score;


    //Private Helpers
    
    void fetch_scores(const score_provider& sp);

    bool is_stopword(
            const dictionary::stub_dictionary::iterator stub_it,
            const score_provider& sp);

    void update_stub_info(
            const dictionary::stub_dictionary::iterator stub_it,
            const score_provider& sp);

    void push_score(
        const dictionary::stub_dictionary::iterator stub_it);

    static bool has_overlap_from_right(
        const dictionary::span& this_span,
        const dictionary::span& next_span);

    static bool overlapper_is_longer(
        const dictionary::span& this_span,
        const dictionary::span& overlapper_span);

    void bounce(const scoring_policy policy);

    void bounce_small_terms_bd();

    void sum_scores();
    
    void bounce_subterm();

private:
    //Special member function not supported
	scorer(const scorer&);
	scorer& operator=(const scorer&);
};

} //app
} //text_scorer
} //instigate

#endif //TEXT_SCORER_APP_SCORER_HPP
