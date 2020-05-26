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
 * Hold (without owning) scoring information of individual evaluable terms.
 *
 * Evaluable in the sense that the term is not stop-word 
 * and was found in the terms dictionary. 
 * Data members are not-owning (observing) pointers.
 */
struct scoring_info {
    /**
     * Default c-tor
     */
    scoring_info();
    /**
     * Copy c-tor with shallow copying
     */
	scoring_info(const scoring_info& source);
    /**
     * Copy assignment operator with shallow copying
     */
	scoring_info& operator=(const scoring_info& rhs);
    /**
     * D-tor
     */
    ~scoring_info();

    //Public data members
    /**
     * Pointer to the span of the term with respect to the originating 
     * user input.
     */
    dictionary::span* term_span_observer_p;
    /**
     * State indicating if the applied scoring policy 
     * bounced the term.
     * This is not-owning (observer) pointer.
     */
    bool bounced;
    //NOTE: consider weighting / weight factor / by scoring policy.
    /**
     * Pointer to a score matrix with the retrieved term score.
     * This is not-owning (observer) pointer.
     */
    score_matrix::score_matrix* term_score_observer_p;

    //Overloads for sorting
    /**
     * Comparison operator overload.
     */
    bool operator<(const scoring_info& rhs) const;

private:
    //Special member function not supported
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
