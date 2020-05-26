
/**
 * @file 
 */

#ifndef TEXT_SCORER_APP_SCORE_PROVIDER_HPP
#define TEXT_SCORER_APP_SCORE_PROVIDER_HPP 


#include "dictionary/term_dictionary.hpp"
#include "dictionary/term_list.hpp"

#include "score_matrix/score_matrix.hpp"


#include <string>


namespace instigate {
namespace text_scorer {
namespace app {

//=============TESTING
void test_score_provider_ctor();

/**
 * Handle resources providing score specification for a term 
 */
class score_provider {

public:

    /**
     * Enum for c-tor disambiguation
     */
    enum init_mode {
        /**
         * For initializing score_provider based on user-provided files
         */
        init_mode_user_files,
        /** 
         * For initializing score_provider using existing cash
         */
        init_mode_app_cash
    };


    //C-tor, d-tor
    /**
     * C-tor 
     * @param mode  Set initialization mode.
     * @param terms_file_path   Path to the file with terms list - one term 
     *                          per line.
     * @param seed Initial seed for randomizing score matrices in terms 
     *              dictionary.
     * @param hash_load_factor Desired load factor of hashmap buckets in 
     *                          terms dictionary.
     * @param stopwords_file_path Path to the file with stop-words list.
     *                            One term (word)  per line.
     * @throws @todo //TODO document exceptions 
     */
    score_provider(const init_mode mode,
                    const std::string& terms_file_path, 
                    size_t seed, size_t hash_load_factor,
                    const std::string& stopwords_file_path);

    /**
     * D-tor
     */
    ~score_provider();

    //Accessors
    /**
     * Get dictionary of terms
     */
    const dictionary::term_dictionary* get_term_dictionary_ptr() const;
    /**
     * Get stopwords
     */
    const dictionary::term_list* get_stopwords_ptr() const;

    //void dump(const char* terms_dump_file, const char* stopwords_dump_path);

private:
    //Private data members
    //parsed / deserialized data
    dictionary::term_dictionary* m_terms_p;
    dictionary::term_list* m_stopwords_p;

    //Private helpers
    void cleanup();

    //Special member function not supported
	score_provider(const score_provider&);
	score_provider& operator=(const score_provider&);
};

/**
* Output stream insertion operator overload
*/
std::ostream& operator<<(std::ostream& stream, 
        const score_provider& sp);

} //app
} //text_scorer
} //instigate

#endif //TEXT_SCORER_APP_SCORE_PROVIDER_HPP
