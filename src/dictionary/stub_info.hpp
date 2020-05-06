

/**
 * @file src/dictionary/stub_info.hpp 
 * @brief 
 * TODO: 
 */

#ifndef TEXT_SCORER_DICTIONARY_STUB_INFO_HPP
#define TEXT_SCORER_DICTIONARY_STUB_INFO_HPP 



#include "score_matrix/score_matrix.hpp"

#include <string>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>

namespace instigate {
namespace text_scorer {
namespace dictionary {


//==========TESTING
void test_stub_info() ;


/**
 * Struct holding start and end positions of a stub
 */
struct span {
    /**
     * Start index (inclusive) of a stub in a sentence from which it was cut out
     */
    size_t start;
    /**
     * End index (exclusive) of a stub in a sentence from which it was cut out
     */
    size_t end;
};

/**
* Output stream insertion operator overload
*/
std::ostream& operator<<(std::ostream& stream, 
        const span& s);

/**
 * Typedef stub_info onto boost::tuple
 * 
 * @tparam bool     Holds is_stop_word boolean to indicate if stub is stop word
 * @tparam span     Holds span (start, end) of a stub
 * @tparam bool     Holds has_matched boolean to indicate if stub is found 
 *                  in a dictionary
 * @tparam score_matrix     Holds a score matrix of stub as retrieved from 
 *                          term dictionary
 */
typedef boost::tuple<bool, span, bool, score_matrix::score_matrix> stub_info;

/**
 * Enum for indexing stub_info tuple
 */
enum stub_info_index {
    tuple_elem_is_stop_word,
    tuple_elem_span,
    tuple_elem_has_matched,
    tuple_elem_score_matrix
};

} //dictionary
} //text_scorer
} //instigate

#endif //TEXT_SCORER_DICTIONARY_STUB_INFO_HPP

