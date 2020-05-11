/**
 * @file 
 */

#ifndef TEXT_SCORER_APP_SCORING_INFO_HPP
#define TEXT_SCORER_APP_SCORING_INFO_HPP 

//#include "score_provider.hpp"
    // check . or include top.hpp

//#include "dictionary/stub_dictionary.hpp"

#include "dictionary/stub_info.hpp"

namespace instigate {
namespace text_scorer {
namespace app {

//=====TESTING
void test_scoring_info_less_than();

/**
 * Hold scoring information of individual evaluable terms.
 *
 * Evaluable in the sense that the term is not stop-word 
 * and was found in the terms dictionary. 
 */
struct scoring_info {
    /**
     * Pointer to the span of the term with respect to the originating 
     * user input.
     */
    dictionary::span* term_span_p;
    /**
     * State indicating if the applied scoring policy 
     * bounced the term.
     */
    bool bounced;
    //NOTE: consider weighting / weight factor / by scoring policy.
    /**
     * Pointer to a score matrix with the retrieved term score.
     */
    score_matrix::score_matrix* term_score_p;

    //Overloads for sorting
    /**
     * Comparison operator overload.
     */
    bool operator<(const scoring_info& rhs) const;

};

/**
* Output stream insertion operator overload
*/
std::ostream& operator<<(std::ostream& stream, 
            const scoring_info& si);

} //app
} //text_scorer
} //instigate

#endif //TEXT_SCORER_APP_SCORING_INFO_HPP
