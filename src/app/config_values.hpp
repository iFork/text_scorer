
/**
 * @file src/app/config_values.hpp
 */

#ifndef TEXT_SCORER_APP_CONFIG_VALUES_HPP
#define TEXT_SCORER_APP_CONFIG_VALUES_HPP 

#include "score_provider.hpp"
#include "defines.hpp"

#include <plog/Log.h>
//#include "tclap/CmdLine.h"
#include <tclap/CmdLine.h>

#include <string>
#include <cstdlib>

namespace instigate {
namespace text_scorer {
namespace app {

/**
 * Manages command line options, config value defaults 
 */
struct config_values {
    //C-tor 
    /**
     * C-tor parsing command line arguments.
     *
     * Sets up command line flags, their usage description and default values.
     * Handles terminal flags (such as --help) printing responses and exiting.
     * Handles out-of-specification arguments with error messages and exits.
     * @param argc argc of command line
     * @param argv argv of command line
     * @warning Can exit with error code 
     * TEXT_SCORER_APP_ERROR_CMDLINE_ARG_PARSING when parser
     * throws exception.
     */
    config_values(int argc, char* argv[]);

    //Public data members
    //logger config
    plog::Severity log_severity; ///< Log severity level.
                                 ///< From 0 (none) to 6 (verbose).
    std::string log_file;     ///< Name of the file to write log into.
    bool enable_console_logging; ///< Switch to turn console logging on.
    //run mode
    score_provider::init_mode run_mode; ///< Score provider initialization mode.
    //run-mode specific input files and options 
    std::string terms_file;  ///< Name of the file to read terms list from.
    std::string stopwords_file; ///< Name of the file to read stopwords list from.
    size_t hash_load_factor; ///< Desired load factor of buckets in hashmap 
                             ///< of terms dictionary.
    size_t seed; ///< Initial seed used for score_matrix randomization.

    //TODO: implement dictionary dump and run_app_cash feature
    //const bool to_dump;
    //const std::string terms_dump_file;
    //const std::string stopwords_dump_file;

}; 

} //app
} //text_scorer
} //instigate

#endif //TEXT_SCORER_APP_CONFIG_VALUES_HPP
