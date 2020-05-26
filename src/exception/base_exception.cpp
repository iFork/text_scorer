
#include "base_exception.hpp"

namespace instigate {
namespace text_scorer {
namespace exception {


void base_exception::set_message(const std::string& msg)
{
    m_message = msg;
}

const char* base_exception::what() const throw()
{
    return m_message.c_str();
}


} //exception
} //text_scorer
} //instigate
