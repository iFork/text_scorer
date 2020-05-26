
#include "score_matrix.hpp"
#include <algorithm>


namespace instigate {
namespace text_scorer {
namespace score_matrix {


//TODO: move int o C-tor
/*
  Now we can define a function that simulates an ordinary
  six-sided die.
*/
//int roll_die() {
//    /*<< __mt19937 produces integers in the range [0, 2[sup 32]-1].
//        However, we want numbers in the range [1, 6].  The distribution
//        __uniform_int_distribution performs this transformation.
//        [warning Contrary to common C++ usage __uniform_int_distribution
//        does not take a /half-open range/.  Instead it takes a /closed range/.
//        Given the parameters 1 and 6, __uniform_int_distribution
//        can produce any of the values 1, 2, 3, 4, 5, or 6.]
//    >>*/
//    boost::random::uniform_int_distribution<> dist(1, 6);
//    /*<< A distribution is a function object.  We generate a random
//        number by calling `dist` with the generator.
//    >>*/
//    return dist(gen);
//}
//]

//score_matrix_randomizer Implementation

rng_t score_matrix_randomizer::m_gen;
    //LESSONS_LEARNED: define staic member, no initialization () needed
    
score_matrix_randomizer::score_matrix_randomizer(int seed)
{
    m_gen.seed(seed);
    block_32_1 = m_gen(); 
    block_32_2 = m_gen(); 
    block_32_3 = m_gen(); 
    block_4 = m_gen(); 
}

//score_matrix Implementation

score_matrix::score_matrix()
{
}

score_matrix::score_matrix(int num):
    m_matrix(num)
{
}


score_matrix::score_matrix(const score_matrix_randomizer& smr):
    m_matrix(smr.block_4)
{
    // TODO : test 
    #ifdef DEBUG_VERBOSE
        std::cout << "score matrix c-tor w/ randomizer" << std::endl;
        std::cout << "baseline     " << m_matrix << std::endl;
    #endif //DEBUG_VERBOSE
    std::bitset<N_ELEMENTS> tempo(smr.block_32_1);
    #ifdef DEBUG_VERBOSE
        std::cout << "tempo 1      " << tempo << std::endl;
    #endif //DEBUG_VERBOSE
    m_matrix <<= 32; //will be biased as shifts first set bit ???
    #ifdef DEBUG_VERBOSE
        std::cout << "1st 32 shift " << m_matrix << std::endl;
    #endif //DEBUG_VERBOSE
    m_matrix |= tempo;
    #ifdef DEBUG_VERBOSE
        std::cout << "1st OR join  " << m_matrix << std::endl;
    #endif //DEBUG_VERBOSE
    m_matrix <<= 32; 
    #ifdef DEBUG_VERBOSE
        std::cout << "2nd 32 shift " << m_matrix << std::endl;
    #endif //DEBUG_VERBOSE
    tempo = std::bitset<N_ELEMENTS>(smr.block_32_2); 
    #ifdef DEBUG_VERBOSE
        std::cout << "tempo 2      " << tempo << std::endl;
    #endif //DEBUG_VERBOSE
    m_matrix |= tempo;
    #ifdef DEBUG_VERBOSE
        std::cout << "2nd OR join  " << m_matrix << std::endl;
    #endif //DEBUG_VERBOSE
    m_matrix <<= 32; 
    #ifdef DEBUG_VERBOSE
        std::cout << "3rd 32 shift " << m_matrix << std::endl;
    #endif //DEBUG_VERBOSE
    tempo = std::bitset<N_ELEMENTS>(smr.block_32_3); 
    #ifdef DEBUG_VERBOSE
        std::cout << "tempo 3      " << tempo << std::endl;
    #endif //DEBUG_VERBOSE
    m_matrix |= tempo;
    #ifdef DEBUG_VERBOSE
        std::cout << "3rd OR join  " << m_matrix << std::endl;
    #endif //DEBUG_VERBOSE
}

score_matrix::score_matrix(const score_matrix& sm):
        m_matrix(sm.m_matrix)
{
}

score_matrix& score_matrix::operator=(const score_matrix& rhs)
{
    //TODO: DISCUSS: assuming bitset copy assignment is safe
    //otherwise - use copy-swap idiom
    m_matrix = rhs.m_matrix;
    return *this;
}

//Accessors Implementation
std::bitset<score_matrix::N_ELEMENTS>::reference score_matrix::operator()
    (size_t row, size_t col)
{
    assert(N_ROWS > row);
    assert(N_COLUMNS > col);
    return m_matrix[row * N_ROWS + col];
}

bool score_matrix::operator()(size_t row, size_t col) const
{
    assert(N_ROWS > row);
    assert(N_COLUMNS > col);
    return m_matrix[row * N_ROWS + col];
}

score_matrix score_matrix::operator+(const score_matrix& rhs) const
{
    score_matrix result(*this);
    result += rhs;
    return result;
}

score_matrix& score_matrix::operator+=(const score_matrix& rhs)
{
    m_matrix |= rhs.m_matrix;
    return *this;
}

bool score_matrix::operator==(const score_matrix& rhs) const
{
    return m_matrix == rhs.m_matrix;
}

bool score_matrix::operator!=(const score_matrix& rhs) const
{
    return m_matrix != rhs.m_matrix;
}

//Friends Implementation
std::ostream& operator<<(std::ostream& stream, 
            const score_matrix& sm)
{
    stream << sm.m_matrix;
    return stream;
}


//=============TESTING=

void test_score_matrix_subscripting()
{
    score_matrix sm2(2);
    assert(sm2(0,0) == 0);
    assert(sm2(0,1) == 1);
    sm2(0,0) = 1;
    assert(sm2(0,0) == 1);
    assert(sm2(0,2) != 1);
}

void test_score_matrix_equality()
{
    score_matrix sm1(1);
    score_matrix sm2(2);
    score_matrix smtwo(2);
    assert(sm1 != sm2);
    assert(sm2 == smtwo);
}

void test_score_matrix_addition()
{
    score_matrix sm1(1);
    score_matrix sm2(2);
    score_matrix sm3(3);
    assert(sm1 != sm3);
    assert(sm2 != sm3);
    assert((sm1 + sm2) == sm3);
}

void test_radom_num_gen() 
{
    
    rng_t m_gen;
    assert(0 == rng_t::min());
    assert(0xffffffff == rng_t::max()); //32 bits
    std::cout << rng_t::min() << std::endl;
    std::cout << rng_t::max() << std::endl;
}

void test_score_matrix_randomizer_ctor()
{
    std::cout << "score matrix randomizer \n";
    score_matrix_randomizer smr1(1);
    std::cout << "smr with seed = 1: \n";
    std::cout << smr1.block_32_1 << " " << smr1.block_32_2 << " " << 
        smr1.block_32_3 << " " << (int)smr1.block_4 << std::endl;

    score_matrix_randomizer smr2(2);
    std::cout << "smr with seed = 2: \n";
    std::cout << smr2.block_32_1 << " " << smr2.block_32_2 << " " << 
        smr2.block_32_3 << " " << (int)smr2.block_4 << std::endl;

    score_matrix_randomizer smr42(42);
    std::cout << "smr with seed = 42: \n";
    std::cout << smr42.block_32_1 << " " << smr42.block_32_2 << " " << 
        smr42.block_32_3 << " " << (int)smr42.block_4 << std::endl;
}

void test_score_matrix_ctor()
{
    score_matrix sm1(1);
    std::cout << sm1 << std::endl;
    score_matrix sm2(2);
    std::cout << sm2 << std::endl;

    score_matrix_randomizer smr1(1);
    score_matrix sm3(smr1);
    std::cout << sm3 << std::endl;
    score_matrix_randomizer smr42(42);
    score_matrix sm4(smr42);
    std::cout << sm4 << std::endl;
}

} //score_matrix
} //text_scorer
} //instigate

