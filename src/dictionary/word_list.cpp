
#include "word_list.hpp"

#include <plog/Log.h>

#include <string>
#include <fstream>
#include <cassert>

// DEV TEMPO
#include <iostream>

namespace instigate {
namespace text_scorer {
namespace dictionary {


//TODO: file parsing 
word_list::word_list(const std::string& user_file_path)
                                            //TODO: remove throw(), will throw
{
    PLOGD << "Constructing word_list at " << this << " from " 
        << user_file_path; 
    std::ifstream file;
    std::string term;
    file.open(user_file_path.c_str());
    if(!file.is_open()){
        //TODO: EXCEPTION
        std::cout << "file is not opened \n";
    }
    while (std::getline(file, term)){ 
        
        //TODO: catch invalid chars in term - terminate or skip ?
        //TODO: make lower case !!
        
        m_word_list.insert(term);
    }
    if(file.bad()) {
        //TODO: EXCEPTION
        std::cout << "badbit raised when reading file \n" ; // 
    }
    PLOGV << "word_list constructed at " << this 
        << " with average load factor of " << m_word_list.load_factor()
        << " and max load factor of " << m_word_list.max_load_factor();
}

word_list::~word_list() throw()
{
    PLOGD << "Destructing word_list at " << this ;
}


//Stream operator Implementation
std::ostream& operator<<(std::ostream& stream, 
            const word_list& d)
{
    word_list::set::const_iterator cit = d.m_word_list.cbegin();
    for (; cit != d.m_word_list.cend(); cit++) {
        stream << "Term: " << *cit << std::endl;
    }
    return stream;
}

//=============TESTING

void test_word_list_ctor()
{
    
    const char* file_path = "user_data/terms.txt";
    word_list d2(file_path);
    //std::cout << d2 << std::endl;
    PLOGV << "\n" << d2;
}


} //dictionary
} //text_scorer
} //instigate

