

#include "scoring_info.hpp"

#include <plog/Log.h>


namespace instigate {
namespace text_scorer {
namespace app {


bool scoring_info::operator<(const scoring_info& rhs) const
{
    return *term_span_p < *(rhs.term_span_p);
}

//Stream operator Implementation
std::ostream& operator<<(std::ostream& stream, 
            const scoring_info& si) 
{
    stream << "Scoring info: " << *si.term_span_p
           << ", bounced: " << si.bounced
           << ", score_matrix: " << *si.term_score_p;
    return stream;
}

//=====TESTING
void test_scoring_info_less_than()
{
    scoring_info si_1;
    dictionary::span sp_1;
    sp_1.start = 0;
    sp_1.end = 1;
    si_1.term_span_p = &sp_1;
    scoring_info si_2;
    dictionary::span sp_2;
    sp_2.start = 0;
    sp_2.end = 2;
    si_2.term_span_p = &sp_2;
    assert(si_1 < si_2);
    scoring_info si_3;
    dictionary::span sp_3;
    sp_3.start = 1;
    sp_3.end = 2;
    si_3.term_span_p = &sp_3;
    assert(si_1 < si_3);
    PLOGV << "Comparing scoring_infos: passed";
}

} //app
} //text_scorer
} //instigate

