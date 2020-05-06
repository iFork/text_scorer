
#include "stub_dictionary.hpp"

#include <plog/Log.h>

#include <string>
#include <cassert>


namespace instigate {
namespace text_scorer {
namespace dictionary {

//C-tor, d-tor Implementation
stub_dictionary::stub_dictionary(const std::string& sentence)
{
    PLOGD << "Constructing stub_dictionary at " << this 
        << " from `" << sentence << "`";
    //assert(//sentence.empty() or length );
       
   //TODO >>>>>>>>>>>>>> 
   //
   //
        //TODO: catch invalid chars in term - terminate or skip ?
        //TODO: make lower case !!

    PLOGV << "stub_dictionary constructed at " << this 
        << " with average load factor of " << m_stub_stub_info.load_factor()
        << " and max load factor of " << m_stub_stub_info.max_load_factor();
}

stub_dictionary::~stub_dictionary() throw()
{
    PLOGD << "Destructing stub_dictionary at " << this ;
}

//Stream operator overload
std::ostream& operator<<(std::ostream& stream, 
            const stub_dictionary& sd)
{
    stub_dictionary::const_iterator cit = sd.cbegin();
    for (; cit != sd.cend(); cit++) {
        stream << "Key: " << cit->first; 
       // stream << "; Value: " << cit->second; 
        stream << std::endl;
    }
    return stream;
}


//=============TESTING

void test_stub_dictionary_ctor()
{
    
    const std::string sentence = "Hello from New York Stock Exchange rooftop";
    stub_dictionary sd(sentence);
    //std::cout << d2 << std::endl;
    //PLOGV << "\n" << sd;

}

} //dictionary
} //text_scorer
} //instigate

