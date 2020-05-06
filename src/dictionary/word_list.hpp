
/**
 * @file src/dictionary/dictionary.hpp 
 * @brief 
 * TODO: 
*/

#ifndef TEXT_SCORER_DICTIONARY_WORD_LIST_HPP
#define TEXT_SCORER_DICTIONARY_WORD_LIST_HPP 



#include <string>

#include <boost/unordered_set.hpp>

namespace instigate {
namespace text_scorer {
namespace dictionary {

//=============TESTING

void test_word_list_ctor();

class word_list {

public:
    /**
    * Typedef for hashed set
    */
    typedef boost::unordered_set<std::string> set;


//C-tors
    /**
     * Default c-tor 
     */
    word_list() {}


    /**
     * A c-tor parsing word list file
     * @param user_file_path Path to the file with words list.
     *                            One term (word) per line.
     */
    word_list(const std::string& user_file_path); 

    /**
     * A d-tor 
     */
    ~word_list() throw ();

//Accessors
    /**
     * Insert a term into a word_list
     */
    word_list& insert(std::string term);
        //TODO. will be used for dicing sentence and pushing into a 
        //default constructed word_list
        //DISCUSS: will drop if `tokenize` class added 
        
    /**
     * Output stream insertion operator overload
     */
    friend std::ostream& operator<<(std::ostream& stream, 
            const word_list& wl);
private:
    //Private data members
    set m_word_list;

//TODO: ITERATORS - EXPOSE 
    //!!!!!!!!

//TODO: Special member function not supported
	word_list(const word_list&);
	word_list& operator=(const word_list&);
};


} //dictionary
} //text_scorer
} //instigate

#endif //TEXT_SCORER_DICTIONARY_WORD_LIST_HPP
