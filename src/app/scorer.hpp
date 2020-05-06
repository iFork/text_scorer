/**
 * @file src/app/scorer.hpp
 * @brief 
 * TODO: 
 */

#ifndef TEXT_SCORER_APP_SCORER_HPP
#define TEXT_SCORER_APP_SCORER_HPP 

#include "score_provider.hpp"
    // check . or include top.hpp

#include "dictionary/stub_dictionary.hpp"

#include <string>


namespace instigate {
namespace text_scorer {
namespace app {

/**
 * Manage scoring of a sentence
 */
class scorer {

public:
    //C-tor, d-tor
    /**
     * C-tor based on sentence input
     * @param sentence string to be scored 
     */
    scorer(const std::string& sentence);

private:
    //Private data members
    std::string m_sentence; // or sentence pre-validated
    dictionary::stub_dictionary m_stubs;
    score_matrix::score_matrix m_sentence_score;


    //Helpers
    //score_stubs(
    void score() // evaluate
    {
     //   stubs(sentence); //TODO: - stubs shoud be copy constructable / assignable
        //evaluate stubs per term_dictionary / score stubs
        //score_stubs(stubs) //method of app class
        
        //stubs.score_against( // criterion/scores_reference.term dictionary ) 
        //                          //score_provider
        //                                          ^.get_term_dict
        //                                          ^.get_stopwords_set
        //                      // member of Settings/Shared-resources
        //                      // Criterion / Scores / Scale / Bill
        //                      // Standard / Reference  class
    }

private:
    //Special member function not supported
	scorer(const scorer&);
	scorer& operator=(const scorer&);
};

} //app
} //text_scorer
} //instigate

#endif //TEXT_SCORER_APP_SCORER_HPP
