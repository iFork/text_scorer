

#include "stub_info.hpp"

#include <plog/Log.h>

#include <string>
#include <cassert>


namespace instigate {
namespace text_scorer {
namespace dictionary {


//Stream operator Implementation
std::ostream& operator<<(std::ostream& stream, 
            const span& s) 
{
    stream << "Stub span: start: " << s.start 
       << ", end: " << s.end; 
    return stream;
}

//==========TESTING

void test_stub_info() 
{
    span sp;
    score_matrix::score_matrix sm;
    stub_info si(false, sp, true, sm);
    PLOGV << "stub_info tuple is: " << boost::tuples::set_delimiter(',')
       << si;
    PLOGV << "stub_info has span: " << si.get<tuple_elem_span>();
}

} //dictionary
} //text_scorer
} //instigate

