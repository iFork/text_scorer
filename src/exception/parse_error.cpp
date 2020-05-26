
#include "parse_error.hpp"

#include <sstream>

namespace instigate {
namespace text_scorer {
namespace exception {

parse_error::parse_error(size_t block_number, size_t position,
                              const std::string& offender):
        m_block_number(block_number),
        m_position(position),
        m_offender(offender)
{
    std::ostringstream msg;
    msg << "Parse Error at line/block " 
                          << m_block_number
                          << ". Error occurred when processing `"
                          << m_offender << "` at position " << m_position
                          << ".";
    set_message(msg.str());
}

tokens_count_out_of_range::tokens_count_out_of_range(size_t tokens_count, 
                              size_t block_number, size_t position,
                              const std::string& offender):
            parse_error(block_number, position, offender),
            m_tokens_count(tokens_count)
{
    std::ostringstream msg;
    msg << "Tokens count out-of-range error when parsing"
                           " line/block " 
                          << m_block_number
                          << ". Error occurred at token count "
                          << m_tokens_count
                          << " when processing `"
                          << m_offender << "` at position " << m_position
                          << ".";
    set_message(msg.str());
}

symbol_out_of_spec::symbol_out_of_spec(size_t block_number, size_t position,
                              const std::string& offender):
            parse_error(block_number, position, offender)
{
    std::ostringstream msg;
    msg << "Symbol out-of-specification error when parsing"
                           " line/block " 
                          << m_block_number
                          << ". Error occurred when processing symbol `"
                          << m_offender << "` at position " << m_position
                          << ".";
    set_message(msg.str());
}


} //exception
} //text_scorer
} //instigate
