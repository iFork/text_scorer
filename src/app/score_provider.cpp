
#include "score_provider.hpp"

#include <plog/Log.h>
#include <stdexcept>
#include <sstream>

namespace instigate {
namespace text_scorer {
namespace app {


score_provider::score_provider(const init_mode mode,
                    const std::string& terms_file_path, 
                    size_t seed, size_t hash_load_factor,
                    const std::string& stopwords_file_path)
{
    if(init_mode_user_files == mode) {
        m_terms = new dictionary::term_dictionary(terms_file_path, seed, 
                hash_load_factor);
        m_stopwords = new dictionary::word_list(stopwords_file_path);
    }
    else {
        std::ostringstream msg;
        msg << "Init mode " << static_cast<int>(mode) 
            << " is not implemented";
        PLOGF << msg;
        throw std::runtime_error(msg.str());
        //TODO: custom exception 
    }
}

score_provider::~score_provider()
{
    delete m_terms;
    delete m_stopwords;
}

//Accessors Implementation
const dictionary::term_dictionary* score_provider::get_term_dictionary_ptr() const
{
    return m_terms;
}
const dictionary::word_list* score_provider::get_stopwords_ptr() const
{
    return m_stopwords;
}

//Stream operator overload
std::ostream& operator<<(std::ostream& stream, 
        const score_provider& sp)
{
    stream << "Term Dictionary: <" << *sp.get_term_dictionary_ptr() 
    << ">; Stop Words: <" << *sp.get_stopwords_ptr() << ">"
    << std::endl;
    return stream;
}

//=============TESTING

void test_score_provider_ctor()
{
    
    //const char* file_path = "user_data/terms.txt";
    //score_provider sp(score_provider::init_mode_user_files(),
    //                    file_path, 1, 
    //                    file_path);
    //PLOGV << sp;
}


} //app
} //text_scorer
} //instigate

