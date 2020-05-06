
#include "scorer.hpp"

#include <plog/Log.h>

#include <string>

namespace instigate {
namespace text_scorer {
namespace app {


scorer::scorer(const std::string& sentence):
    m_sentence(sentence),
    m_stubs(sentence)
{
    //TODO: CHECK
}

} //app
} //text_scorer
} //instigate

