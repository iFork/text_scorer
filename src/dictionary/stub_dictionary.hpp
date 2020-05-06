
/**
 * @file src/dictionary/stub_dictionary.hpp 
 * @brief 
 * TODO: 
 */

#ifndef TEXT_SCORER_DICTIONARY_STUB_DICTIONARY_HPP
#define TEXT_SCORER_DICTIONARY_STUB_DICTIONARY_HPP 



//#include "score_matrix/score_matrix.hpp"
#include "stub_info.hpp"

#include <string>

#include <boost/unordered_map.hpp>

namespace instigate {
namespace text_scorer {
namespace dictionary {

/**
 * Decompose sentence into a set of all possible sequential stabs
 * of given maximum lenght and store stub_info for each stub
 */
class stub_dictionary {

public:
    /**
    * Typedef for hash map
    */
    typedef boost::unordered_map<std::string, stub_info> map;
    //TODO: what if INHERIT stub_dictionary : public map 
    //  need for iterator exposure and func wrapping will drop !!!!
        
    //Public static constants
    static const int MAX_TERM_LENGTH = 10; 

    //C-tor, d-tor
    /**
    * C-tor decomposing sentence into a set of all possible sequential stabs
    * @param sentence a string to decompose
    */
    stub_dictionary(const std::string& sentence);
        //no puntuation ? 
        //no terminal punctuation ?
        //or keep punctiuation as part of term ?
    
    /**
     * D-tor
     */
    ~stub_dictionary() throw();


    //Iterators
    /**
     * Iterator typedef
     */
    typedef map::iterator iterator;
    /**
     * Const iterator typedef
     */
    typedef map::const_iterator const_iterator;

    /**
     * Iterator begin
     */
    iterator begin()
    {
        return m_stub_stub_info.begin();
    }
    /**
     * Iterator end
     */
    iterator end()
    {
        return m_stub_stub_info.end();
    }
    /**
     * Const iterator begin
     */
    const_iterator cbegin() const
    {
        return m_stub_stub_info.cbegin();
    }
    /**
     * Const iterator end
     */
    const_iterator cend() const
    {
        return m_stub_stub_info.cend();
    }

private:
    //Private data members
    //hash map of term-stubs and their info
    map m_stub_stub_info;

//Special member function not supported
	stub_dictionary(const stub_dictionary&);
	stub_dictionary& operator=(const stub_dictionary&);

};

/**
* Output stream insertion operator overload
*/
std::ostream& operator<<(std::ostream& stream, 
        const stub_dictionary& sd);

} //dictionary
} //text_scorer
} //instigate

#endif //TEXT_SCORER_DICTIONARY_STUB_DICTIONARY_HPP

