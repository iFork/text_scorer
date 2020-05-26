
/**
 * @file 
*/

#ifndef TEXT_SCORER_EXCEPTION_BASE_EXCEPTION_HPP
#define TEXT_SCORER_EXCEPTION_BASE_EXCEPTION_HPP

#include <exception>
#include <string>

namespace instigate {
namespace text_scorer {
namespace exception {


class base_exception : public std::exception {

public:
    /**
     * C-tor
     */
    base_exception() {}

    /**
     * D-tor
     */
    virtual ~base_exception() throw() {}

    /**
     * Set error message.
     */
    void set_message(const std::string& msg);

    /**
     * Override exception reporter.
     */
    virtual const char* what() const throw();

protected:
    //Protected data members
    std::string m_message;


};

} //exception
} //text_scorer
} //instigate

#endif //TEXT_SCORER_EXCEPTION_BASE_EXCEPTION_HPP
