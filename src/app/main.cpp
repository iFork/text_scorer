/**
 * @file 
*/

#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>

//DEV includes
#include <iostream>
#include <sstream>

#include "config_values.hpp"
#include "top.hpp"

#include "common/defines.hpp"

#include "scoring_info.hpp"  //testing
#include "dictionary/term_dictionary.hpp"
#include "dictionary/term_list.hpp"
#include "dictionary/stub_dictionary.hpp"
#include "dictionary/stub_info.hpp"

#include "score_matrix/score_matrix.hpp"

#include "boost/unordered_map.hpp"



using namespace instigate::text_scorer;


void init_logger(const plog::Severity log_severity, const std::string& log_file,
        bool enable_console_logging);

void log_catchup(int argc, char* argv[], 
        const app::config_values& cfg_vals);

int main(int argc, char* argv[])
{
    //parse command line args into const configuration values
    const app::config_values cfg_vals(argc, argv);
    //initialize logger using config values
    init_logger(cfg_vals.log_severity, cfg_vals.log_file, 
        cfg_vals.enable_console_logging);        
    log_catchup(argc, argv, cfg_vals);
    //initialize top object using config values and run
    //TODO:DISCUSS: for run_mode = app_cash - branching here or inside c-tor ?
    app::top a_top(cfg_vals.run_mode, cfg_vals.terms_file, 
                    cfg_vals.seed, cfg_vals.hash_load_factor,
                    cfg_vals.stopwords_file);
    try {
        //extend try block up ?
        a_top.run();
    } 
    // catch (const file_open_error)
        //TODO: change to specific exceptions 
        //score provided -- std::bad_alloc 
        //or plese_terminate_me as- new_handler -- to set 
        //
    catch (...) {
        PLOGF << "Unhandled exception. Exiting...";
        return 1;
    }

// Tests 
    //app::test_score_provider_ctor();
    //app::test_scoring_info_less_than();

    //dictionary::test_term_list_ctor();
    //dictionary::test_term_list_lookup();
    
    //dictionary::test_term_dictionary_ctor();
    //dictionary::test_term_find();

    //dictionary::test_stub_dictionary_ctor();
    //dictionary::test_stub_info() ;
    //dictionary::test_span_less_than();

    //score_matrix::test_radom_num_gen();

    //score_matrix::test_score_matrix_ctor();
    //score_matrix::test_score_matrix_randomizer_ctor();

    //score_matrix::test_score_matrix_subscripting();
    //score_matrix::test_score_matrix_equality();
    //score_matrix::test_score_matrix_addition();
    return 0;

}


//initialize logger
/**
 * Initialize logger.
 * @param log_severity Enum value for log severity level.
 * @param log_file File to write log into.
 * @param enable_console_logging Boolean to add also console logging.
 * @remark Mapping of supported macros and log level and corresponding enum:
 * Macro | Log Level | Enum Value
 * ----- | --------  | ----------
 * PLOGV | "verbose" | 6
 * PLOGD | "debug"   | 5
 * PLOGI | "info"    | 4
 * PLOGW | "warning" | 3
 * PLOGE | "error"   | 2
 * PLOGF | "fatal"   | 1
 * PLOGN | "none"    | 0
 */
void init_logger(const plog::Severity log_severity, const std::string& log_file,
        bool enable_console_logging)
{
    //plog::Logger<0> logger = plog::init(log_severity, &file_appender);
    const char* log_file_c = log_file.c_str();
    //TODO: move these constants to config ?
    const size_t MAX_FILE_SIZE = 50000;//*< Max size per file for a rolling
                                      //*< buffer of logging 
    const size_t MAX_FILE_COUNT = 4; //*< Max number of files for a rolling
                                    //*< buffer of logging 
    if(enable_console_logging) {
        static plog::RollingFileAppender<plog::TxtFormatter> 
            file_appender(log_file_c, MAX_FILE_SIZE, MAX_FILE_COUNT); 
        static plog::ColorConsoleAppender<plog::TxtFormatter> console_appender; 
        //logger.addAppender(&console_appender);
        plog::init(log_severity, &file_appender).addAppender(&console_appender);
        PLOGN << "Logger initialized with severity level " << log_severity;
        PLOGD << "Log goes to console and file." 
            << " RollingFileAppender is at " << log_file_c 
            << " with size limit " << MAX_FILE_SIZE
            << " and files count limit of " << MAX_FILE_COUNT;
    }
    else {
        static plog::RollingFileAppender<plog::TxtFormatter> 
            file_appender(log_file_c, MAX_FILE_SIZE, MAX_FILE_COUNT); 
        plog::init(log_severity, &file_appender);
        PLOGN << "Logger initialized with severity level " << log_severity;
        PLOGD << "Log goes to file." 
             << " RollingFileAppender is at " << log_file_c 
            << " with size limit " << MAX_FILE_SIZE
            << " and files count limit of " << MAX_FILE_COUNT;
    }
}


void log_catchup(int argc, char* argv[], 
        const app::config_values& cfg_vals)
{
    std::stringstream ss;
    for (int i = 0; i != argc; i++) {
        ss << argv[i] << " ";
    }
    PLOGD << "Command line arguments passed are "
        << " argc = " << argc << ", argv = " << ss.str();
    PLOGD << "config_values has been created at " << &cfg_vals 
        << " with values: " << cfg_vals;
}
