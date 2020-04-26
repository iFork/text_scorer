/**
 * @file src/dictionary/dictionary.hpp 
 * @brief 
 * TODO: 
*/

#ifndef TEXT_SCORER_DICTIONARY_HPP
#define TEXT_SCORER_DICTIONARY_HPP 


/* for poco TODO: drop??
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
*/

#include "score_matrix/score_matrix.hpp"

#include <string>

#include <boost/unordered_map.hpp>

namespace instigate {
namespace text_scorer {
namespace dictionary {


//===TEST
void test_dictionary_ctor();


class dictionary
{

public:
    /**
    * Typedef for hash map
    */
    typedef boost::unordered_map<std::string, score_matrix::score_matrix> map;
    
private:
    //Private data members
    //hash map of terms and their score_matrix
    map m_term_score;
    

    std::string m_dirname;
//non-static data member initializers only available with -std=c++11
    std::string m_filename;
//TODO: turn dirname (and? filename) public constant
// USER_DATA_DIR //to read - app will pass this
//
//      terms.txt
//      stopword.txt
// APP_DATA_DIR //to write 
//      -- app should pass app_data dir 
//      -- dict class will create filename based on input file
//      -- appending _dictionary.json
//
//       terms_dictionary.json
//       stopwords_dictionary.json


/* TODO: TODELETE     
    std::string get_filename() const throw ();
    void set_filename(const std::string&) throw ();
*/

public:

//C-tors
	//dictionary() throw ();
    
	/**
	* A c-tor converting word list into a dictionary
    * @param user_file_path
    *
	*/
    dictionary(const char* user_file_path, size_t seed) throw();

    //TODO: DISCUSS: how to explicitly distingush 2 contructors -
    //accepting a) raw text list to process
    //b) dictionary file to parse JSON or map ??
    // split into 2 sibling classes ?? - 
    // or have special / static methods ?
    //      dict::dictify(output_file_dictionary) ??
	/**
	* A c-tor converting word list into a dictionary
    * @param dictionary_file_path
    *
	*/
	//dictionary(dictionary_file_path) throw ();
	/**
	* A d-tor 
	*/
	~dictionary() throw ();


private:



//TODO: Special member function not supported
//defaulted and deleted functions only available with -std=c++11
	dictionary(const dictionary&);
//	dictionary(const dictionary&&);
	dictionary& operator=(const dictionary&);
//	dictionary& operator=(const dictionary&&);


public:
    //Accessors
    /**
     * Output stream insertion operator overload
     */
    friend std::ostream& operator<<(std::ostream& stream, 
            const dictionary& d);

//TODO: dump / serialize obj
    //either << operator overload 
    //OR boost serialize REVIEW

	/**
	* Write obj into provided stringstream 
	*/
	//void stringify(std::stringstream& str) const; 

    /**
    * @brief Write given data in into a file with a given name
    * @param file_name name of the file
    * @param datad data to write
    * @return 0 if successful, -1 otherwise
    */
    //void write_data(const char* file_name, const std::string& data) throw ();
    //or dump() 

};





} //dictionary
} //text_scorer
} //instigate

#endif //TEXT_SCORER_DICTIONARY_HPP


