/**
 * @file src/dictionary/term_dictionary.hpp 
 * @brief 
 * TODO: 
 */

#ifndef TEXT_SCORER_DICTIONARY_TERM_DICTIONARY_HPP
#define TEXT_SCORER_DICTIONARY_TERM_DICTIONARY_HPP 


/* for poco TODO: drop??
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
*/

#include "common/defines.hpp"
#include "score_matrix/score_matrix.hpp"

#include <string>

#include <boost/unordered_map.hpp>

namespace instigate {
namespace text_scorer {
namespace dictionary {


//===TEST
void test_term_dictionary_ctor();
void test_term_find();

/**
 * Dictionary of terms. 
 *
 * Keys in the dictionary are terms and values are 
 * their score matrices.
 */
class term_dictionary
{

public:
    /**
    * Typedef for hash map
    */
    typedef boost::unordered_map<std::string, score_matrix::score_matrix> map;
    //TODO: what if INHERIT stub_dictionary : public map 
    //  need for iterator exposure and func wrapping will drop !!!!

    //C-tors, d-tor
	/**
     * A c-tor converting term list into a term_dictionary with random
     * score matrics.
     * @param terms_file_path Path to the text file with a term list.
     * @param seed Starting seed for creating random score matrices.
     * @param hash_load_factor Desired load factor of hashmap buckets in 
     *                          terms dictionary.
     */
    term_dictionary(const std::string& terms_file_path, size_t seed,
            size_t hash_load_factor);

	/**
	* A d-tor 
	*/
	~term_dictionary() throw ();

private:
    //Private data members
    //hash map of terms and their score_matrix
    map m_term_score;
    
public:
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
        return m_term_score.begin();
    }
    /**
     * Iterator end
     */
    iterator end()
    {
        return m_term_score.end();
    }
    /**
     * Const iterator begin
     */
    const_iterator cbegin() const
    {
        return m_term_score.cbegin();
    }
    /**
     * Const iterator end
     */
    const_iterator cend() const
    {
        return m_term_score.cend();
    }

    //Accessors 
    /**
     * Find a term in a dictionary.
     *
     * @param term string to search
     * @return An iterator to an element with key equivalent to 
     *         term, or end() if no such element exists.
     */
    const_iterator find(const std::string& term) const;

    /*
     * Find score of a given term in a dictionary.
     *
     * @param term string to search
     * @return pair where first is bool which is true when found 
     * @return An iterator pointing to an element with key equivalent to k, or b.end() if no such element exists.
     */
    //std::pair<bool, const score_matrix::score_matrix&> 
     //   find_score(const std::string& term) const;


//TODO: dump / serialize obj
    //either << operator overload 
    //OR boost serialize REVIEW
	// OR write stringified 


private:
    //Special member function not supported
	term_dictionary(const term_dictionary&);
	term_dictionary& operator=(const term_dictionary&);

};



/**
* Output stream insertion operator overload
*/
std::ostream& operator<<(std::ostream& stream, 
        const term_dictionary& d);


} //dictionary
} //text_scorer
} //instigate

#endif //TEXT_SCORER_DICTIONARY_TERM_DICTIONARY_HPP


