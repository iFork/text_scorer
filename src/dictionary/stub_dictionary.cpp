
#include "stub_dictionary.hpp"

#include <plog/Log.h>

#include <string>
#include <cassert>


namespace instigate {
namespace text_scorer {
namespace dictionary {

//C-tor, d-tor Implementation
stub_dictionary::stub_dictionary(const std::vector<std::string>& word_sequence, 
                const size_t max_term_length)
{
    PLOGD << "Constructing stub_dictionary at " << this ;
    PLOGV  
          //TODO: overload << op for string vector ?
          /* << "with word_sequence `" << word_sequence << "`" */
          << ", max_term_length `" << max_term_length << "`";
    //assert(//word_sequence.empty() or length );
       
   //TODO >>>>>>>>>>>>>> 
    size_t word_count = word_sequence.size();
    const size_t local_max_term_length =
        (max_term_length > word_count) ? word_count : max_term_length;
    std::vector<std::string>::const_iterator anchor_it = word_sequence.begin();
    int anchor_index = 0;
    std::vector<std::string>::const_iterator end_it = word_sequence.end();
    for(; anchor_it != end_it; anchor_it++, anchor_index++) {
        insert_stubs(anchor_it, anchor_index, end_it, local_max_term_length);
    }
    PLOGV << "stub_dictionary constructed at " << this 
        << " with average load factor of " << m_stub_stub_info.load_factor()
        << " and max load factor of " << m_stub_stub_info.max_load_factor();
}

stub_dictionary::~stub_dictionary() throw()
{
    PLOGD << "Destructing stub_dictionary at " << this ;
}

//Helpers Implementation
bool inline stub_dictionary::stub_length_is_good(
            std::vector<std::string>::const_iterator anchor_it,
            std::vector<std::string>::const_iterator end_slider_it,
            const size_t max_term_length)
{
    //TODO: add asserts for size_t to long int cast wrap-around catching ??
    return (end_slider_it - anchor_it) < 
            static_cast<long int>(max_term_length);
    //or std::distance(anchor_it, end_slider_it)
}

void stub_dictionary::insert_stub(const std::string& stub, 
                            int start_index, int end_index)
{
    stub_info si = stub_info();
    si.get<tuple_elem_span>().start = start_index;
    si.get<tuple_elem_span>().end = end_index;
    m_stub_stub_info.emplace(stub, si);
}

void stub_dictionary::insert_stubs(
        std::vector<std::string>::const_iterator anchor_it,
        int anchor_index,
        std::vector<std::string>::const_iterator end_it,
        const size_t max_term_length)
{
    PLOGD << "Called";
    std::string stub;
    assert(end_it >= anchor_it);
    std::vector<std::string>::const_iterator end_slider_it = anchor_it;
    int end_slider_index = anchor_index;
    if(end_slider_it != end_it 
       //following is relevant only in case of max_term_length = 0
       && stub_dictionary::stub_length_is_good(anchor_it, end_slider_it,
                                                max_term_length)) {
        stub = *end_slider_it++;
        end_slider_index++;
        insert_stub(stub, anchor_index, end_slider_index);
        PLOGV << "stub added: " << stub;
    }
    while(end_slider_it != end_it
       && stub_dictionary::stub_length_is_good(anchor_it, end_slider_it,
                                                max_term_length)) {

        stub += " " + *end_slider_it++;
        end_slider_index++;
        insert_stub(stub, anchor_index, end_slider_index);
        PLOGV << "stub added: " << stub;
    }
}

//Stream operator overload
std::ostream& operator<<(std::ostream& stream, 
            const stub_dictionary& sd)
{
    stub_dictionary::const_iterator cit = sd.cbegin();
    for (; cit != sd.cend(); cit++) {
        stream << "Key: " << cit->first; 
        stream << "; Value: " << cit->second; 
        stream << std::endl;
    }
    return stream;
}


//=============TESTING

void test_stub_dictionary_ctor()
{
    
    const std::string sentence = "Hello from New York Stock Exchange rooftop";
    std::vector<std::string> word_seq;
    word_seq.push_back("Hello");
    word_seq.push_back("from");
    word_seq.push_back("New");
    word_seq.push_back("York");

    stub_dictionary sd(word_seq, 15);
    //std::cout << d2 << std::endl;
    PLOGV << sd;

}

} //dictionary
} //text_scorer
} //instigate

