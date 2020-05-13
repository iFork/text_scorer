

#include "stub_info.hpp"

#include <plog/Log.h>

#include <string>
#include <cassert>


namespace instigate {
namespace text_scorer {
namespace dictionary {

size_t span::length() const
{
    assert(end > start);
    return end - start;
}

bool span::has_overlap_with(const span& other_span) const
{
    PLOGD << "Called...";
    return (other_span.start < end
            && other_span.end > start);
}

bool span::is_longer_than(const span& other_span) const
{
    PLOGD << "Called...";
    return length() > other_span.length();
}

bool span::operator<(const span& rhs) const
{
    if(start == rhs.start) {
        return end < rhs.end;
    }
    return start < rhs.start;
}

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

void test_span_less_than()
{
    span sp_1;
    sp_1.start = 0;
    sp_1.end = 1;
    span sp_2;
    sp_2.start = 0;
    sp_2.end = 2;
    assert(sp_1 < sp_2);
    PLOGV << "Comparing spans: " << sp_1 << " < " << sp_2;
    span sp_3;
    sp_3.start = 1;
    sp_3.end = 2;
    assert(sp_1 < sp_3);
    PLOGV << "Comparing spans: " << sp_1 << " < " << sp_3;
}

} //dictionary
} //text_scorer
} //instigate

