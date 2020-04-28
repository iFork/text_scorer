#include "dictionary.hpp"

#include <plog/Log.h>

#include <string>
#include <fstream>
#include <cassert>

// DEV TEMPO
#include <iostream>

namespace instigate {
namespace text_scorer {
namespace dictionary {



/*
dictionary::dictionary() throw() // : m_dirname("db/users"), m_filename("")
{	
    std::cout << "In dict ctor \n";
    score_matrix::score_matrix sm1 = score_matrix::score_matrix(1);
    std::cout << "score matrix in dic is :" << sm1 << std::endl;
    //m_term_score.insert(std::make_pair("test", sm1));
    m_term_score.emplace("test", sm1);
    std::cout << "in dic test key is :" << m_term_score["test"] << std::endl;
}
*/

//TODO: file parsing 
void print_stream_state(std::istream& steam);
dictionary::dictionary(const char* user_file_path, size_t seed) throw()
                                            //TODO: remove throw(), will throw
{
    PLOGD << "Constructing dictionary at " << this 
        << " with random score matrices from " 
        << user_file_path << " file with starting seed = " << seed;
    assert(NULL != user_file_path);
    std::ifstream file;
    std::string term;
    file.open(user_file_path);
    if(!file.is_open()){
        //TODO: EXCEPTION
        std::cout << "file is not opened \n";
    }
    while (std::getline(file, term)){ 
        //TODO: catch seed++ overflow and/or initial seed being close to limit
        //skip white space ???
        //file >> std::ws;
        
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
}

dictionary::~dictionary() throw()
{
    PLOGD << "Destructing dictionary at " << this ;
}

/*
void dictionary::write_data(const char* file_name, 
        const std::string& data) throw()
{
    assert(NULL != file_name);
    assert("" != data);
    std::ofstream file;
    file.open(file_name);
    assert(!file.fail());
    file << data;
    file.close();
    assert(!file.fail());
}
*/

//Accessors Implementation
std::ostream& operator<<(std::ostream& stream, 
            const dictionary& d)
{
    dictionary::map::const_iterator cit = d.m_term_score.cbegin();
    for (; cit != d.m_term_score.cend(); cit++) {
        stream << "Key: " << cit->first; 
        stream << "; Value: " << cit->second; 
        stream << std::endl;
    }
    return stream;
}

//================DEBUG

void print_stream_state(std::istream& stream)
{
    if(stream.good()) {
        std::cout << "stream state is good \n";
    }
    if(stream.bad()) {
        std::cout << "stream state is bad \n";
    }
    if(stream.fail()) {
        std::cout << "stream state is fail \n";
    }
    if(stream.eof()) {
        std::cout << "stream state is eof \n";
    }
}

//=============TESTING

void test_dictionary_ctor()
{
    
    const char* file_path = "user_data/terms.txt";
    dictionary d2(file_path, 1);
    //std::cout << d2 << std::endl;
    PLOGV << "\n" << d2;
}

//////////////////

/*
std::string dictionary::read_data(const char* file_name) throw()
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
dictionary::pars_data(const std::string& data)
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

