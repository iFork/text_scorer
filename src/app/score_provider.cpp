
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
    PLOGD << "Constructing score_provider at " << this ;
    PLOGV << "with init_mode `" << mode << "`"
        << ", terms_file_path `" << terms_file_path << "`"
        << ", seed `" << seed << "`"
        << ", hash_load_factor `" << hash_load_factor << "`"
        << ", stopwords_file_path `" << stopwords_file_path << "`";
    try {
        if(init_mode_user_files == mode) {
            m_terms_p = new dictionary::term_dictionary(terms_file_path, seed, 
                    hash_load_factor);
            m_stopwords_p = new dictionary::term_list(stopwords_file_path);
        }
        else {
            std::ostringstream msg;
            msg << "Init mode " << static_cast<int>(mode) 
                << " is not implemented";
            PLOGF << msg;
            throw std::runtime_error(msg.str());
            //TODO: custom exception, document exception 
        }
    } catch (...) {
        PLOGF << "Exception caught in c-tor of " << this << ". Cleaning up...";
        cleanup();
        throw;
        //TODO: DOING 
    }
}

score_provider::~score_provider()
{
    PLOGD << "Destructing score_provider at " << this ;
    cleanup();
}

void score_provider::cleanup()
{
    PLOGV << "Called...";
    delete m_terms_p;
    delete m_stopwords_p;
}

//Accessors Implementation
const dictionary::term_dictionary* score_provider::get_term_dictionary_ptr() const
{
    PLOGD << "Called..."; 
    assert(m_terms_p);
    return m_terms_p;
}
const dictionary::term_list* score_provider::get_stopwords_ptr() const
{
    PLOGD << "Called...";
    assert(m_stopwords_p);
    return m_stopwords_p;
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

