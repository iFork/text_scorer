
//DEV includes
#include <iostream>

#include "dictionary/dictionary.hpp"

#include "score_matrix/score_matrix.hpp"

#include "boost/unordered_map.hpp"

#define DEBUG_VERBOSE

using namespace instigate::text_scorer;

int main(int argc, char* argv[])
{
    std::cout << "Hi \n";
    
//    dictionary::dictionary d;
//    d.say_hi();

    dictionary::test_dictionary_ctor();
    

    score_matrix::test_radom_num_gen();

    score_matrix::test_score_matrix_ctor();
    score_matrix::test_score_matrix_randomizer_ctor();

    score_matrix::test_score_matrix_subscripting();
    score_matrix::test_score_matrix_equality();
    score_matrix::test_score_matrix_addition();
    return 0;

}
