

#include "parser.hpp"
#include "exception/parse_error.hpp"

#include <cstddef>
#include <plog/Log.h>

#include <string>
#include <cctype>

#include <cassert>

namespace instigate {
namespace text_scorer {
namespace parser {


parsing_info::parsing_info() 
{
    PLOGD << "Called...";
    current_line_number = 0;
    current_position = 0;
    current_token_first = 0;
    qualified_token_first = 0;
    qualified_token_last = 0;
    tokens_count = 0;
    length = 0;
    is_any_delimiter = false;
    is_term_delimiter = false;
}

void parsing_info::set_up(const std::string& line, size_t line_number)
{
    PLOGD << "Called...";
    current_line_number = line_number;
    length = line.length();
    current_position = 0;
    current_token_first = 0;
    tokens_count = 0;
    qualified_token_first = 0;
    qualified_token_last = 0;
    is_any_delimiter = false;
    is_term_delimiter = false;
}

//TODO: Discuss: shoud I set members (volatiles) of m_pars_info to 
//invalid values as -1 or npos,  e.g. current_position = npos;
//or separate volatile/interim data  - scoped separate from token-scoped part ?
void parsing_info::reset_interims()
{
    PLOGD << "Called...";
    qualified_token_first = 0;
    qualified_token_last = 0;
    is_any_delimiter = false;
    is_term_delimiter = false;
}

term_parser::term_parser(
            parsing_policy_enum policy,
            const std::string& token_delimiters,
            const std::string& allowed_token_symbols,
            const std::string& term_delimiters, 
            const std::string& term_delimiter_token,
            const size_t max_tokens_count):
        m_policy_preset(policy),
        m_term_delimiters(term_delimiters),
        m_term_delimiter_token(term_delimiter_token),
        m_token_delimiters(token_delimiters),
        m_allowed_token_symbols(allowed_token_symbols),
        m_max_tokens_count(max_tokens_count)
{
    PLOGD << "Called...";
}

void term_parser::set_up(const std::string& line, size_t line_number)
{
    PLOGD << "Called...";
    m_pars_info.set_up(line, line_number);
}

void term_parser::reset_interims()
{
    PLOGD << "Called...";
    m_pars_info.reset_interims();
}

void inline term_parser::pre_mutate(std::string::iterator it, 
                        parsing_policy_enum policy)
{
    PLOGD << "Called...";
    if((m_policy_preset | policy) 
            & parsing_policy::turn_to_lower) {
        unsigned char lower = std::tolower(*it);
        *it = lower;
    }
}

void inline term_parser::inspect(std::string::iterator it, 
             parsing_policy_enum policy)
{
    PLOGD << "Called...";
    //check for delimiter
    if(  ((m_policy_preset | policy) & parsing_policy::make_tokens)
       | ((m_policy_preset | policy) & parsing_policy::assure_symbols)
       | ((m_policy_preset | policy) & parsing_policy::assure_tokens_count)
       ) {
        //update_delimiter_flags() / set_delimiter() 
        size_t pos_in_token_delims = m_token_delimiters.find(*it);
        if(pos_in_token_delims != std::string::npos) {
            m_pars_info.is_any_delimiter = true;
        }
        //optimization opportunity - can add skip logic 
        //update_/all/_delimiter_flags()
        size_t pos_in_term_delims = m_term_delimiters.find(*it);
        if(pos_in_term_delims != std::string::npos) {
            m_pars_info.is_any_delimiter = true;
            m_pars_info.is_term_delimiter = true;    
        }
    }
    if((m_policy_preset | policy) & parsing_policy::failover_delimiter) {
        if(!m_pars_info.is_any_delimiter){
            size_t pos_in_allowed = m_allowed_token_symbols.find(*it);
            if(pos_in_allowed == std::string::npos) {
                m_pars_info.is_any_delimiter = true;
            }
        }
    }
    // if failover_delimiter is set, effect of assure_symbols is nullified
    else if((m_policy_preset | policy) & parsing_policy::assure_symbols) {
        //DISCUSS: if !make_tokens 
        //         - Throw even on delimiter or ignore delimiter?
        if(!m_pars_info.is_any_delimiter) {
            size_t pos_in_allowed = m_allowed_token_symbols.find(*it);
            if(pos_in_allowed == std::string::npos) {
                std::string offender(1, *it);
                exception::symbol_out_of_spec e(
                        m_pars_info.current_line_number,
                        m_pars_info.current_position, offender);
                PLOGE << e.what();
                throw e;
            }
        }
    }
}
//TODO: once more - BREAK DOWN inspect() into 
//check_for_delimiters() / inspect_delimiters
//      check_for_term_delim()
//      check_for_token_delim()
//      chek_for_other_delims()
//   assure_symbols();

void term_parser::introspect(const std::string& line,
                parsing_policy_enum policy,
                std::vector<std::string>* tokens_p)
{
    PLOGD << "Called...";
    if(  ((m_policy_preset | policy) & parsing_policy::make_tokens)
       | ((m_policy_preset | policy) & parsing_policy::assure_tokens_count)
       ) {
        stage();
    }
    if((m_policy_preset | policy) & parsing_policy::assure_tokens_count) {
        assure_tokens_count(line);
    }
    if(((m_policy_preset | policy) 
                               & parsing_policy::make_tokens)
       && ((m_policy_preset | policy)  
                               & parsing_policy::respect_term_delimiters)) {
        commit_token(line, tokens_p);
        commit_term_delimiter(m_term_delimiter_token, tokens_p);
    }
    else if((m_policy_preset | policy) & parsing_policy::make_tokens) {
        commit_token(line, tokens_p);
    }
}

void term_parser::stage()
{
    PLOGD << "Called...";
    assert(m_pars_info.current_position < m_pars_info.length);
    //stage token before delimiter, track tokens count
    if(m_pars_info.is_any_delimiter) {
        //treat successive delimiters as a single delimiter, 
        //i.e. trim trailing delimiters
        if(m_pars_info.current_position != m_pars_info.current_token_first) {
            assert(m_pars_info.current_position 
                    > m_pars_info.current_token_first);
            m_pars_info.qualified_token_first = m_pars_info.current_token_first;
            m_pars_info.qualified_token_last = m_pars_info.current_position;
            m_pars_info.current_token_first = m_pars_info.current_position + 1;
            m_pars_info.tokens_count++;
        }
    }
    //stage token at the end of the line/block, but without delimiter
    else if(m_pars_info.current_position == m_pars_info.length - 1) {
        assert(!m_pars_info.is_any_delimiter);
        m_pars_info.qualified_token_first = m_pars_info.current_token_first;
        m_pars_info.qualified_token_last = m_pars_info.current_position + 1;
        m_pars_info.current_token_first = m_pars_info.current_position + 1;
        m_pars_info.tokens_count++;
    }
    m_pars_info.current_position++;
}

void term_parser::assure_tokens_count(const std::string& line)
{
    PLOGD << "Called...";
    assert(m_pars_info.tokens_count <= m_max_tokens_count);
    if(m_pars_info.tokens_count == m_max_tokens_count) {
        std::string offender(line, m_pars_info.qualified_token_first,
                    m_pars_info.qualified_token_last
                    - m_pars_info.qualified_token_first);
        exception::tokens_count_out_of_range e(m_pars_info.tokens_count,
                                        m_pars_info.current_line_number,
                                        m_pars_info.current_position,
                                        offender);
        PLOGE << e.what();
        throw e;
    }
}

void term_parser::commit_token(const std::string& line,
                                std::vector<std::string>* tokens_p)
{
    assert(tokens_p);
    if(m_pars_info.qualified_token_first != m_pars_info.qualified_token_last) {
        assert(m_pars_info.qualified_token_first 
                < m_pars_info.qualified_token_last);
        std::string token(line, m_pars_info.qualified_token_first,
                    m_pars_info.qualified_token_last
                    - m_pars_info.qualified_token_first);
        tokens_p->push_back(token);
    }
}

void term_parser::commit_term_delimiter(const std::string& term_delimiter_token,
                                std::vector<std::string>* tokens_p)
{
    PLOGD << "Called...";
    assert(tokens_p);
    if(m_pars_info.is_term_delimiter) {
        tokens_p->push_back(term_delimiter_token);
    }
}

void term_parser::parse(std::string& line, size_t line_number, 
                        parsing_policy_enum policy,
                        std::vector<std::string>* tokens_p) 
{
    PLOGD << "Called...";
    set_up(line, line_number);
    assert(m_pars_info.length);
    for(std::string::iterator it = line.begin(); it != line.end(); it++) {
        pre_mutate(it, policy);
        inspect(it, policy);
        introspect(line, policy, tokens_p);
        reset_interims();
    }
}

//TODO:  log parsing  Errors

} //parser
} //text_scorer
} //instigate

