
#include "term_list.hpp"

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
term_list::term_list(const std::string& terms_file_path)
                                            //TODO: remove throw(), will throw
{
    PLOGD << "Constructing term_list at " << this ;
    PLOGV << "with terms_file_path `" << terms_file_path << "`";
    std::ifstream file;
    std::string term;
    file.open(terms_file_path.c_str());
    if(!file.is_open()){
        //TODO: EXCEPTION
        PLOGE << terms_file_path << " file is not opened at " << &file;
    }
    while (std::getline(file, term)){ 
        
        //TODO: catch invalid chars in term - terminate or skip ?
        //TODO: make lower case !!
        
        m_term_list.insert(term);
    }
    if(file.bad()) {
        //TODO: EXCEPTION
        PLOGE << "badbit raised when reading file at " << &file;  
    }
    PLOGD << "term_list constructed at " << this 
        << " with average load factor of " << m_term_list.load_factor()
        << " and max load factor of " << m_term_list.max_load_factor();
    /* PLOGV << "Term list dump: " << *this; */
}

term_list::~term_list() throw()
{
    PLOGD << "Destructing term_list at " << this ;
}

bool term_list::exists(const std::string& term) const
{
    PLOGV << "Called...";
    return m_term_list.count(term) != 0;
}

//Stream operator Implementation
std::ostream& operator<<(std::ostream& stream, 
            const term_list& d)
{
    term_list::set::const_iterator cit = d.m_term_list.cbegin();
    for (; cit != d.m_term_list.cend(); cit++) {
        stream << "Term: " << *cit << std::endl;
    }
    return stream;
}

//=============TESTING

void test_term_list_ctor()
{
    
    const char* file_path = "user_data/terms.txt";
    term_list d2(file_path);
    //std::cout << d2 << std::endl;
    PLOGV << "\n" << d2;
}

void test_term_list_lookup()
{
    const char* file_path = "user_data/stopwords.txt";
    /* const char* file_path = "user_data/terms.txt"; */
    term_list tl(file_path);
    std::string term_1 = "the";
    std::string term_2 = "hello";
    bool check_1 = tl.exists(term_1);
    bool check_2 = tl.exists(term_2);
    PLOGV << "Checking `" << term_1 << "` - exists: " << check_1;
    PLOGV << "Checking `" << term_2 << "` - exists: " << check_2;
    //change termlist file by hand 
    //make this friend and - count on member 
    //check c-tor 
}


} //dictionary
} //text_scorer
} //instigate

