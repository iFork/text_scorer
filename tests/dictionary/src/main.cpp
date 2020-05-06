
//DEV includes
#include <iostream>

#include "dictionary/term_dictionary.hpp"

using namespace instigate::text_scorer;

int main()
{
    std::cout << "Hi \n";
    
    dictionary::dictionary d;
    d.say_hi();

//FIXME: move to test func
    typedef boost::unordered_map<std::string, int> map;
    map x;
    x["one"] = 1;
    x["two"] = 2;
    x["three"] = 3;

    assert(x.at("one") == 1);
    assert(x.find("missing") == x.end());

    map::const_iterator cit = x.cbegin();
    for (; cit != x.cend(); cit++) {
        std::cout << "Key: " << cit->first; 
        std::cout << "; Value: " << cit->second; 
        std::cout << std::endl;
    }

    std::cout << "<< on d \n";
    std::cout << d << std::endl;

    return 0;

}
