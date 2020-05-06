
#include "top.hpp"

#include <plog/Log.h>

#include <string>

namespace instigate {
namespace text_scorer {
namespace app {

        
top::top(const score_provider::init_mode mode,
            const std::string& terms_file_path, 
            size_t seed, size_t hash_load_factor,
            const std::string& stopwords_file_path):
    m_score_provider(mode, terms_file_path, 
                    seed, hash_load_factor,
                    stopwords_file_path)
{
    //TODO: DISCUSS: if existing app-cash to be used => score_provider c-tor
    //*signature changes* OR how to preserve signature to avoid default 
    //initialization and if-branching iside the func's body ?

    //TODO: add: dump_flag / dump_file_dir
    //if(to_dump) => score_provider.dump(dump_file_dir)
}


void top::run()
{
    while(true) {
        //ask for input
        std::string user_input;
        user_input = "Default user input.";
        //process cin 
        //
        //switch (input_profile) { ... }
        //
        //scorer sentence_scorer(user_input);
        //sentence_scorer.score_against(m_score_provider);
        //
        //
    }
}

} //app
} //text_scorer
} //instigate

