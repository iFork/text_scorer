
#include "top.hpp"

#include <plog/Log.h>

#include <string>

namespace instigate {
namespace text_scorer {
namespace app {

        
top::top(const score_provider::init_mode mode,
            const std::string& terms_file_path, 
            size_t seed, size_t hash_load_factor,
            const std::string& stopwords_file_path)
try     
    : m_score_provider(mode, terms_file_path, 
                    seed, hash_load_factor,
                    stopwords_file_path)
{
    PLOGD << "Constructing top at " << this;
    PLOGV << " with init_mode `" << mode << "`"
        << ", terms_file_path `" << terms_file_path << "`"
        << ", seed `" << seed << "`"
        << ", hash_load_factor `" << hash_load_factor << "`"
        << ", stopwords_file_path `" << stopwords_file_path << "`";

    //TODO: DISCUSS: if existing app-cash to be used => score_provider c-tor
    //*signature changes* OR how to preserve signature to avoid default 
    //initialization and if-branching iside the func's body ?
    //OR have branching inside main()

    //TODO: add: dump_flag / dump_file_dir
    //if(to_dump) => score_provider.dump(dump_file_dir)
}
catch (...) {
    PLOGF << "Exception caught in c-tor of " << this << " called"
        << " with init_mode `" << mode << "`"
        << ", terms_file_path `" << terms_file_path << "`"
        << ", seed `" << seed << "`"
        << ", hash_load_factor `" << hash_load_factor << "`"
        << ", stopwords_file_path `" << stopwords_file_path << "`";
    throw;
}

top::~top()
{
    PLOGD << "Destructing top at " << this ;
}


void top::run()
{
    PLOGD << "run() called at " << this;
    while(true) {
        //ask for input
        //process cin 
        //switch (input_profile) { ... }
        std::string user_input;
        user_input = "Hello from New York Stock Exchange rooftop";

        std::string sentence;
        size_t line_number = 0;
        while (std::getline(std::cin, sentence)){
           //TODO: add tokens_p vector*
           m_term_parser.parse(sentence, line_number, 
                                parser::parsing_policy::none);
           line_number++;
        }
        if(std::cin.bad()) {
            //TODO: EXCEPTION
            PLOGE << "badbit raised when reading standard input";
        }

        std::vector<std::string> word_seq;
        word_seq.push_back("Hello");
        word_seq.push_back("from");
        word_seq.push_back("the");
        word_seq.push_back("New");
        word_seq.push_back("York");
        word_seq.push_back("stock");
        word_seq.push_back("exchange");
        //
        scorer word_seq_scorer(word_seq);
        word_seq_scorer.score_against(m_score_provider, 
                    scorer::big_eats_littles_bd);
        //word_seq_scorer.pretty_print_result();
        //
        //
        //
        break;
    }


}

} //app
} //text_scorer
} //instigate

