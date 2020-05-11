

#include "config_values.hpp"

#include <plog/Log.h>

#include <string>

namespace instigate {
namespace text_scorer {
namespace app {

config_values::config_values(int argc, char* argv[])
{
	try {
    TCLAP::CmdLine cmd(
    "Calculate score of the sentence based on the dictionary."
    " Score of the sentence is a matrix constructed as binary sum of the score"
    " matrices from terms in a sentence. \n Specify command line arguments to"
    " override defaults and run the program to enter sentence to be scored."
            , ' ', "0.1");
    //Command line argument descriptions
    std::vector<size_t> log_levels;
    for(int i = 0; i <= 6; i++) {
        log_levels.push_back(i);
    }
    TCLAP::ValuesConstraint<size_t> allowed_log_levels(log_levels);
    TCLAP::ValueArg<size_t> log_level_arg("l", "logl", "Log level"
            "\n 0 - none," "\n 1 - fatal," "\n 2 - error,"
            "\n 3 - warning," "\n 4 - info," "\n 5 - debug,"
            "\n 6 - verbose"
            , false, 5, &allowed_log_levels);
	cmd.add(log_level_arg);
    TCLAP::SwitchArg enable_console_logging_arg("", "logc", "Enable console"
            " logging", false);
	cmd.add(enable_console_logging_arg);
    TCLAP::ValueArg<std::string> log_file_arg("", "logf", "Log file", false,
                "app_data/log.txt", "path/to/logfile");
	cmd.add(log_file_arg);
    std::vector<size_t> run_modes;
    run_modes.push_back(0);
    TCLAP::ValuesConstraint<size_t> allowed_run_modes(run_modes);
    TCLAP::ValueArg<size_t> run_mode_arg("r", "runm", "Run mode - specify how to"
            " initialize terms dictionary and stopword list"
            "\n 0 - using term and stopword lists, term dictionary is created"
            " with random score matrices (default)" 
            "\n [other modes NOT SUPPORTED in this version]" 
            , false, 0, &allowed_run_modes);
	cmd.add(run_mode_arg);
    TCLAP::ValueArg<std::string> dump_file_dir_arg("", "dumpd", "Dump file"
            "directory, if flag is present dump term and stopword dictionaries"
            "in given or default directory. \n This files will be used when"
            "--runm <app cash> is set."
            "\n [NOT SUPPORTED in this version]" 
            , false, "app_data", "path/to/dump_dir");
	cmd.add(dump_file_dir_arg);
    TCLAP::ValueArg<std::string> terms_file_arg("t","terms","Terms file", false,
                "user_data/terms.txt", "path/to/terms_list");
    cmd.add(terms_file_arg);
    TCLAP::ValueArg<std::string> stopwords_file_arg("s","stops","Stopwords file", 
                false, "user_data/stopwords.txt", "path/to/stopwords_list");
    cmd.add(stopwords_file_arg);
    TCLAP::ValueArg<size_t> hash_load_factor_arg("","hload","Load factor of"
                " hashmap buckets", false, 1, "positive integer");
        //TODO: add constraint for load factor - custom class or simple range ?
    cmd.add(hash_load_factor_arg);
    TCLAP::ValueArg<size_t> seed_arg("","seed","Seed for score matrix"
            " randomization", false, 1, "positive integer");
    cmd.add(seed_arg);
    //TODO: terms_dump_files; topwords_dump_file
	cmd.parse(argc, argv);
	// Get the value parsed by each arg.
	log_severity = static_cast<plog::Severity>(log_level_arg.getValue());
    enable_console_logging = enable_console_logging_arg.getValue();
    log_file = log_file_arg.getValue();
    run_mode = static_cast<score_provider::init_mode>(run_mode_arg.getValue());
    terms_file = terms_file_arg.getValue();
    stopwords_file = stopwords_file_arg.getValue();
    hash_load_factor = hash_load_factor_arg.getValue();
    seed = seed_arg.getValue();
	} catch ( TCLAP::ArgException& e) {  // catch any exceptions
        PLOGF << e.error() << " for arg " << e.argId() << ". Exiting.";
        std::exit(TEXT_SCORER_APP_ERROR_CMDLINE_ARG_PARSING);
    }
}

std::ostream& operator<<(std::ostream& stream, 
        const config_values& cv)
{
    stream << "< "
        <<  " log_severity: " << cv.log_severity
        << ", log_file: " << cv.log_file
        << ", enable_console_logging: " << cv.enable_console_logging
        << ", run_mode: " << cv.run_mode
        << ", terms_file: " << cv.terms_file
        << ", stopwords_file: " << cv.stopwords_file
        << ", hash_load_factor: " << cv.hash_load_factor
        << ", seed: " << cv.seed
        << " >";
    return stream;
}

} //app
} //text_scorer
} //instigate

