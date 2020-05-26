
/**
 * @file
 */

#ifndef TEXT_SCORER_APP_TOP_HPP
#define TEXT_SCORER_APP_TOP_HPP 

#include "score_provider.hpp"
#include "scorer.hpp"

#include "parser/parser.hpp"
#include "exception/parse_error.hpp"
//move to cpp 

#include <vector>
#include <string>


namespace instigate {
namespace text_scorer {
namespace app {

/**
 * Class to manage score_provider and sentence scoring.
 */
class top {

public:
    //C-tor, d-tor
    /**
     * C-tor
     *
     * @param mode  Set initialization mode for score_provider.
     * @param terms_file_path   Path to the file with terms list - one term 
     *                          per line.
     * @param seed Initial seed for randomizing score matrices in terms 
     *              dictionary.
     * @param hash_load_factor Desired load factor of hashmap buckets in 
     *                          terms dictionary.
     * @param stopwords_file_path Path to the file with stop-words list.
     *                            One term (word)  per line.
     */    
    top(const score_provider::init_mode mode,
            const std::string& terms_file_path, 
            size_t seed, size_t hash_load_factor,
            const std::string& stopwords_file_path);
            //TODO: add: dump_flag / dump_file_dir

    /**
     * D-tor
     */
    ~top();

    //Public methods
    /**
     * Start engagement with user.
     *
     * Get user input - sentences to evaluate the score of
     * and print results of scoring.
     */
    void run();

private:
    //Private data members
    score_provider m_score_provider;
    parser::term_parser m_term_parser;
    //TODO
    std::string m_delimiters;
    std::vector<std::string> m_tokens;

    //Private helpers


    //TODO: process / validate interactive input 
        //TODO: catch invalid chars in term - terminate or skip ?
        //TODO: make lower case !!
        //no puntuation ? 
        //no terminal punctuation ?
        //or keep punctiuation as part of term ?
    //enum input_profile { ... } input_profiler(std::string line);
    
    //bool validate_chars();

    //Special member function not supported
	top(const top&);
	top& operator=(const top&);
};

} //app
} //text_scorer
} //instigate

#endif //TEXT_SCORER_APP_TOP_HPP
