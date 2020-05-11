
/**
 * @file src/score_matrix/score_matrix.hpp
 * @brief 
 * TODO: 
*/

#ifndef TEXT_SCORER_SCORE_MATRIX_HPP
#define TEXT_SCORER_SCORE_MATRIX_HPP

#include "common/defines.hpp"

//#include <string>
#include <bitset>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
//#include "boost/random.hpp"
#include <iostream>


namespace instigate {
namespace text_scorer {
namespace score_matrix {

//TODO: mocve to test
//=============TESTING=
void test_radom_num_gen();
void test_score_matrix_ctor();
void test_score_matrix_randomizer_ctor();
void test_score_matrix_subscripting();
void test_score_matrix_equality();
void test_score_matrix_addition();

/**
* Typedef for random number generator used.
* mt19937 with the default seed is used.
*/
typedef boost::random::mt19937 rng_t;

/**
 * Helper struct used to initialize score matrix with random values, 
 * by passing it to score_matrix c-tor
 */
struct score_matrix_randomizer {
private:
    //Private data members
    //random number generator with default seed
    static rng_t m_gen;
public:
    //Public data members
    //100 bits decomposed into integer types
    //TODO: assert lenght of int ? or use exact width ints from std or boost
    //TODO: How to tie (number of) block w/ the size of score_matrix ? 
    //to make this work w/ x-size bitsets
    unsigned long int block_32_1; 
    unsigned long int block_32_2; 
    unsigned long int block_32_3; 
    unsigned char block_4; //rely on automatic truncation

    //C-tor
    score_matrix_randomizer(int seed);
};

class score_matrix {

//TODO: make macro ? or namespace global ?
public:
    //Public staic constants
    /**
     * Number of columns in score_matrix
     */
    static const size_t N_COLUMNS = 10;
    /**
     * Number of rows in score_matrix
     */
    static const size_t N_ROWS = 10;
    /**
     * Number of elements in score_matrix
     */
    static const size_t N_ELEMENTS = N_COLUMNS * N_ROWS;


private:
    //Private data members
    std::bitset<N_ELEMENTS> m_matrix;

public:
    //C-tors
    /**
     * C-tor - default 
     */
    score_matrix(); //needed for dictionary's map default c-tor

    /**
     * C-tor - setting bits per given integer value.
     * Used for testing.
     */
    score_matrix(int num);

    /**
     * C-tor to initialize matrix with a given bitset.
     * Used in operator+ overload 
     */
    score_matrix(const std::bitset<N_ELEMENTS> bits);

    /**
     * C-tor to initialize matrix with a given initializer / randomizer.
     */
    score_matrix(const score_matrix_randomizer& smr);

    //Special member function not supported
    /**
     * Copy c-tor
     */
	score_matrix(const score_matrix& sm);
        //TODO: NOTE: required by term_dictionary's std::pair constructor
        //-- treace requirement 
    /**
     * Copy assignment operator
     */
    score_matrix& operator=(const score_matrix& rhs);

    //Accessors
    /**
     * Overload operator() to access and set (i,j)-th element of the matrix
     */
    std::bitset<N_ELEMENTS>::reference operator()(size_t row, size_t col);
    /**
     * Overload operator() to access (i,j)-th element of the matrix
     */
    bool operator()(size_t row, size_t col) const;

    //Modifiers
    /**
     * Addition operator overload to perform bitwise OR
     */
    score_matrix operator+(const score_matrix& rhs) const;

    /**
     * Compound addition operator overload to perform bitwise OR
     */
    score_matrix& operator+=(const score_matrix& rhs);

    /**
     * Equality comparison operator overload
     */
    bool operator==(const score_matrix& rhs) const;

    /**
     * Non-equality comparison operator overload
     */
    bool operator!=(const score_matrix& rhs) const;

    /**
     * Output stream insertion operator overload
     */
    friend std::ostream& operator<<(std::ostream& stream, 
            const score_matrix& sm);

};

} //score_matrix
} //text_scorer
} //instigate

#endif //TEXT_SCORER_SCORE_MATRIX_HPP

