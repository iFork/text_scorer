
#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>

//DEV includes
#include <iostream>

#include "config_values.hpp"
#include "top.hpp"

#include "dictionary/term_dictionary.hpp"
#include "dictionary/word_list.hpp"
#include "dictionary/stub_dictionary.hpp"
#include "dictionary/stub_info.hpp"

#include "score_matrix/score_matrix.hpp"

#include "boost/unordered_map.hpp"



using namespace instigate::text_scorer;


void init_logger(const plog::Severity log_severity, const std::string& log_file,
        bool enable_console_logging);

int main(int argc, char* argv[])
{

    const app::config_values cfg_vals(argc, argv);

    init_logger(cfg_vals.log_severity, cfg_vals.log_file, 
        cfg_vals.enable_console_logging);        

    std::cout << "Hi \n";
    
//    term_dictionary::term_dictionary d;
//    d.say_hi();

    app::test_score_provider_ctor();

    dictionary::test_word_list_ctor();
    
    dictionary::test_term_dictionary_ctor();
    dictionary::test_term_find();

    dictionary::test_stub_info() ;

    score_matrix::test_radom_num_gen();

    score_matrix::test_score_matrix_ctor();
    score_matrix::test_score_matrix_randomizer_ctor();

    score_matrix::test_score_matrix_subscripting();
    score_matrix::test_score_matrix_equality();
    score_matrix::test_score_matrix_addition();
    return 0;

}


//initialize logger
void init_logger(const plog::Severity log_severity, const std::string& log_file,
        bool enable_console_logging)
{
    //plog::Logger<0> logger = plog::init(log_severity, &file_appender);
    const char* log_file_c = log_file.c_str();
    if(enable_console_logging) {
        static plog::RollingFileAppender<plog::TxtFormatter> 
            file_appender(log_file_c, 8000, 3); 
        static plog::ColorConsoleAppender<plog::TxtFormatter> console_appender; 
        //logger.addAppender(&console_appender);
        plog::init(log_severity, &file_appender).addAppender(&console_appender);
    }
    else {
        static plog::RollingFileAppender<plog::TxtFormatter> 
            file_appender(log_file_c, 8000, 3); 
        plog::init(log_severity, &file_appender);
    }
    //plog::init(LOG_SEVERITY, LOG_FILE, 10000, 2);
    PLOGN << "Logger initialized with severity level " << log_severity;
}


