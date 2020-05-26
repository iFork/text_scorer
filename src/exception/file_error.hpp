
/**
 * @file 
 */

#ifndef TEXT_SCORER_EXCEPTION_FILE_ERROR_HPP
#define TEXT_SCORER_EXCEPTION_FILE_ERROR_HPP

#include "base_exception.hpp"

namespace instigate {
namespace text_scorer {
namespace exception {

// TODO: DOING ........


class file_error : public base_exception{

};

class file_open_error : public file_error {

};

class file_read_error : public file_error {

};


//
// TODO: DOING ........
//

//  out_of_spec_input
//    from terms list files 
//    from cin 
//     input / interactive input errors / 
//   invalid_symbols
//   out_of_range
//   invalid_format - for input 
//
//config errors ??




} //exception
} //text_scorer
} //instigate

#endif //TEXT_SCORER_EXCEPTION_FILE_ERROR_HPP
