
/**
 * @file
*/

#ifndef TEXT_SCORER_DICTIONARY_TERM_LIST_HPP
#define TEXT_SCORER_DICTIONARY_TERM_LIST_HPP 



#include <string>

#include <boost/unordered_set.hpp>

namespace instigate {
namespace text_scorer {
namespace dictionary {

//=============TESTING

void test_term_list_ctor();
void test_term_list_lookup();

class term_list {

public:
    /**
    * Typedef for hashed set
    */
    typedef boost::unordered_set<std::string> set;


    //C-tors
    /**
     * Default c-tor 
     */
    term_list() {}

    /**
     * A c-tor parsing word list file
     * @param terms_file_path Path to the file with words list.
     *                            One term (word) per line.
     */
    term_list(const std::string& terms_file_path); 

    /**
     * A d-tor 
     */
    ~term_list() throw ();

    //Exposing lookups
    /**
     * @param term String to check presence of in the term_list
     * @return true if term exists in the list.
     */
    bool exists(const std::string& term) const;
        
    /**
     * Output stream insertion operator overload
     */
    friend std::ostream& operator<<(std::ostream& stream, 
            const term_list& wl);
private:
    //Private data members
    set m_term_list;

//TODO: ITERATORS - EXPOSE ?

//TODO: Special member function not supported
	term_list(const term_list&);
	term_list& operator=(const term_list&);
};


} //dictionary
} //text_scorer
} //instigate

#endif //TEXT_SCORER_DICTIONARY_TERM_LIST_HPP

