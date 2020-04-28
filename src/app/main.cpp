
#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>

//DEV includes
#include <iostream>

#include "dictionary/dictionary.hpp"

#include "score_matrix/score_matrix.hpp"

#include "boost/unordered_map.hpp"

#define DEBUG_VERBOSE

using namespace instigate::text_scorer;

int main(int argc, char* argv[])
{
    //initialize logger
    const char* LOG_FILE = "app_data/log.txt";
    //const plog::Severity LOG_SEVERITY = plog::debug;
    const plog::Severity LOG_SEVERITY = plog::verbose;
    static plog::RollingFileAppender<plog::TxtFormatter> 
            fileAppender(LOG_FILE, 8000, 3); 
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender; 
    plog::init(LOG_SEVERITY, &fileAppender).addAppender(&consoleAppender);
    //plog::init(LOG_SEVERITY, LOG_FILE, 10000, 2);
    PLOGN << "Logger initialized with severity level " << LOG_SEVERITY;

    std::cout << "Hi \n";
    
//    dictionary::dictionary d;
//    d.say_hi();

    dictionary::test_dictionary_ctor();
    

    score_matrix::test_radom_num_gen();

    score_matrix::test_score_matrix_ctor();
    score_matrix::test_score_matrix_randomizer_ctor();

    score_matrix::test_score_matrix_subscripting();
    score_matrix::test_score_matrix_equality();
    score_matrix::test_score_matrix_addition();
    return 0;

}
