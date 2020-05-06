#include "term_dictionary.hpp"

#include <plog/Log.h>

#include <string>
#include <fstream>
#include <cassert>

//#include <iostream>

namespace instigate {
namespace text_scorer {
namespace dictionary {


term_dictionary::term_dictionary(const std::string& user_file_path, size_t seed, 
               size_t hash_load_factor)
                                            //TODO: will throw what?
{
    PLOGD << "Constructing term_dictionary at " << this 
        << " with random score matrices from " 
        << user_file_path << " file with starting seed = " << seed;
    std::ifstream file;
    std::string term;
    file.open(user_file_path.c_str());
    if(!file.is_open()){
        //TODO: EXCEPTION
        std::cout << "file is not opened \n";
    }
    while (std::getline(file, term)){ 
        //TODO: catch seed++ overflow and/or initial seed being close to limit
        
        //TODO: catch invalid chars in term - terminate or skip ?
        //TODO: make lower case !!

        score_matrix::score_matrix_randomizer smr(seed);
        seed++;
        score_matrix::score_matrix sm(smr);
        m_term_score.emplace(term, sm);
    }
    if(file.bad()) {
        //TODO: EXCEPTION
        std::cout << "badbit raised when reading file \n" ; // 
    }
    //file.close();
    //TODO: check load factor and rehash if many collisions
    //
    PLOGV << "term_dictionary constructed at " << this 
        << " with average load factor of " << m_term_score.load_factor()
        << " and max load factor of " << m_term_score.max_load_factor();
}

term_dictionary::~term_dictionary() throw()
{
    PLOGD << "Destructing term_dictionary at " << this ;
}

//Accessors Implementation

//std::pair<bool, const score_matrix::score_matrix&> 
//        term_dictionary::find_score(const std::string& term) const
//        // copying score_matrix ?
//{
//    std::pair<bool, const score_matrix::score_matrix&> result;
//    const_iterator cit = m_term_score.find(term);
//    
//    //TODO: ...............
//    //if nor found - default construct bits et and return
//    //OR leave find and - dereference - to user
//}

term_dictionary::const_iterator term_dictionary::find(const std::string& term)
{
    return m_term_score.find(term);
}

//Stream operator overload
std::ostream& operator<<(std::ostream& stream, 
            const term_dictionary& d)
{
    term_dictionary::const_iterator cit = d.cbegin();
    for (; cit != d.cend(); cit++) {
        stream << "Key: " << cit->first; 
        stream << "; Value: " << cit->second; 
        stream << std::endl;
    }
    return stream;
}


//=============TESTING

void test_term_dictionary_ctor()
{
    
    const std::string file_path = "user_data/terms.txt";
    term_dictionary d2(file_path, 1, 1);
    //std::cout << d2 << std::endl;
    PLOGV << d2;
}

void test_term_find()
{
    const std::string file_path = "user_data/terms.txt";
    term_dictionary d(file_path, 1, 1);
    std::string term_1 = "Hello";
    term_dictionary::const_iterator cit = d.find(term_1);
    if(cit != d.end()) {
        PLOGV << term_1 << " is found and its score_matrix is "
            << cit->second;
    }
    else {
        PLOGV << term_1 << " not found";
    }
    std::string term_2 = "Nello";
    cit = d.find(term_2);
    if(cit != d.end()) {
        PLOGV << term_2 << " is found and its score_matrix is "
            << cit->second;
    }
    else {
        PLOGV << term_2 << " not found";
    }
}
//////////////////

/*
std::string term_dictionary::read_data(const char* file_name) throw()
{
    assert(NULL != file_name);
    std::ifstream file;
    std::string data;
    std::string temp;
    file.open(file_name);
    assert(!file.fail());
    while (!file.eof()) { 
        file >> temp; //TODO: may use string stream to fill in, than convert
        data.append(temp);
    }
    file.close();
    assert(!file.fail());
    return data;
}
*/
   
/*
term_dictionary::pars_data(const std::string& data)
{
    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(data);
    m_data = result.extract<Poco::JSON::Object::Ptr>();
    assert(m_data);
}
*/

} //dictionary
} //text_scorer
} //instigate

