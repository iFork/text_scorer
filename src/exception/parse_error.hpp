
/**
 * @file 
 */

#ifndef TEXT_SCORER_EXCEPTION_PARSE_ERROR_HPP
#define TEXT_SCORER_EXCEPTION_PARSE_ERROR_HPP

#include "base_exception.hpp"

namespace instigate {
namespace text_scorer {
namespace exception {

class parse_error : public base_exception {

public:
    /**
     * C-tor.
     * @param block_number Number of offending block or line.
     * @param position Position of offending element within a block/line.
     * @param offender Offending element.
     */
    parse_error(size_t block_number, size_t position,
                              const std::string& offender);

    /**
     * D-tor
     */
    virtual ~parse_error() throw() {}

protected:
    //Protected data members
    //number of offending block or line
    size_t m_block_number;
    //position within a block/line
    size_t m_position;
    //offending element
    std::string m_offender;
};

class tokens_count_out_of_range : public parse_error {
public:
    /**
     * C-tor.
     * @param tokens_count Offending tokens count.
     * @param block_number Number of offending block or line.
     * @param position Position of offending element within a block/line.
     * @param offender Offending element.
     */
    tokens_count_out_of_range(size_t tokens_count, 
                              size_t block_number, size_t position,
                              const std::string& offender);

    /**
     * D-tor
     */
    virtual ~tokens_count_out_of_range() throw() {}

protected:
    //Private data members
    size_t m_tokens_count;
};

class symbol_out_of_spec : public parse_error {
public:
    /**
     * C-tor.
     * @param block_number Number of offending block or line.
     * @param position Position of offending element within a block/line.
     * @param offender Offending element.
     */
    symbol_out_of_spec(size_t block_number, size_t position,
                              const std::string& offender);

    /**
     * D-tor
     */
    virtual ~symbol_out_of_spec() throw() {}

};

} //exception
} //text_scorer
} //instigate

#endif //TEXT_SCORER_EXCEPTION_PARSE_ERROR_HPP
