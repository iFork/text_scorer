
/**
 * @file
 */

#ifndef TEXT_SCORER_PARSER_PARSER_HPP
#define TEXT_SCORER_PARSER_PARSER_HPP 


#include <vector>
#include <string>


namespace instigate {
namespace text_scorer {
namespace parser {

namespace parsing_policy {
/**
 * Parsing policy setting bits for term_parser.
 */
enum parsing_policy {
    none                    = 1 << 0, //*< No-op.
    assure_tokens_count     = 1 << 1, //*< Throw if number of words/tokens in
                                      //*< the line exceeds maximum.
    turn_to_lower           = 1 << 2, //*< Turn letters to lower case.
    assure_symbols          = 1 << 3, //*< Throw on not allowed token symbols
    failover_delimiter      = 1 << 4, //*< Treat any out-of-specification symbol
                                      //*< as a delimiter.
    make_tokens             = 1 << 5, //*< Split line by white space to push
                                      //*< into tokens' container
    respect_term_delimiters = 1 << 6  //*< Split also by term delimiters.
                                      //*< Add a special symbol to signify 
                                      // term delimiter position.
            //*< E.g. in 'Brave (new) world' parentheses will be replaced with 
            //*< special symbol and pushed back into the tokens container.

};
} //parsing_policy

/**
 * Struct to hold parsing info for current parsing iteration.
 * @remark Call set_up() before using for a line/block of parsing
 * and reset_interims() in the loop at the end of each iteration.
 */
struct parsing_info {
    size_t length; //*< Number of characters in a line to be parsed.
    size_t current_line_number; //*< Number of current line.
    size_t current_position; //*< Current position in line.
    size_t current_token_first; //*< Starting position of the current token in 
    size_t tokens_count; //*< Count of tokens (qualified so far for committing).
                                // a line.
    size_t qualified_token_first; //*< Starting position of a current token in a line 
                         //*< qualified for committing into the tokens' 
                         //*< container.
    size_t qualified_token_last;  //*< End position of a current token in a line 
                         //*< qualified for committing into the tokens' 
                         //*< container.

    bool is_any_delimiter;  //*< Flag indicating whether current char is any 
                            //*< kind of delimiter (i.e. token delimiter or 
                            //*< term delimiter.
    bool is_term_delimiter; //*< Flag indicating whether current char is a 
                            //*< term delimiter.
    
    /**
     * C-tor
     */
    parsing_info();
    /**
     * D-tor
     */
    ~parsing_info() {}
    
    //Helpers
    /**
     * Set up parsing_info to initial values for a given line.
     * @param line String to parse. 
     * @param line_number Sequential number of the line.
     */
    void set_up(const std::string& line, size_t line_number);

    /**
     * Reset interim data of parsing.
     * Clear interim / iteration-level data in a 
     * parsing loop.
     */
    void reset_interims();

private:
    //Special member function not supported
	parsing_info(const parsing_info&);
	parsing_info& operator=(const parsing_info&);
};


/**
 * Manage parsing of words/terms.
 * Both for sentences to be evaluated and terms from dictionary.
 */
class term_parser {

public:

    typedef parsing_policy::parsing_policy parsing_policy_enum;

    /**
     * C-tor.
     * @param policy parsing_policy bits preset. 
     *               Can be chained using bitwise or. 
     * @sa parsing_policy
     * @param token_delimiters String of chars considered as delimiters for
     *                         tokens.
     * @param allowed_token_symbols Symbols allowed to be in a token.
     * @param term_delimiters String of chars considered as delimiters for
     *                        terms.
     * @param term_delimiter_token A special token/symbol to signify term 
     *                             delimiter position (as found during parsing)
     *                             in a tokens' container.
     * @param max_tokens_count Maximum number of tokens in a line to be parsed.
     */
    term_parser(
        parsing_policy_enum policy = parsing_policy::turn_to_lower,
        const std::string& token_delimiters = " .,",
        const std::string& allowed_token_symbols =
                                    "abcdefghijklmnopqrstuvwxyz&-_",
        const std::string& term_delimiters = "!\"#$%'()*,./:;+<=>?[\\]^`{|}~",
        const std::string& term_delimiter_token = "",
        const size_t max_tokens_count = 500);

    /**
     * D-tor
     */
    ~term_parser() {};

    //TODO: check doxygen cross-referencing
    /**
     * Parse input per given parsing_policy.
     * @param line String to parse. As a result it can be modified.
     * @param line_number Sequential number of the line.
     * @param policy parsing_policy bits. This is chained using bitwise or
     * with parsing_policy provided to the parser constructor. 
     * Other parsing_policy bits can be chained here too.
     * @sa parsing_policy
     * @param tokens Pointer to container to hold resulted tokens. 
     * Default is NULL.
     */
    void parse(std::string& line, size_t line_number,
            parsing_policy_enum policy,
            std::vector<std::string>* tokens_p = NULL); 


private:
    
    //Private data members
    parsing_policy_enum m_policy_preset;
    std::string         m_term_delimiters;
    std::string         m_term_delimiter_token;
    std::string         m_token_delimiters;
    std::string         m_allowed_token_symbols;
    size_t              m_max_tokens_count;
    parsing_info        m_pars_info;

    //Private helpers

    //set up m_pars_info for parsing a new line/block in parse()
    void set_up(const std::string& line, size_t line_number);
    
    //reset interim data of parsing.
    void reset_interims();
    
    //TODO: optimization opportunity - add skip logic / strategy for 
    //optimizing specifically on pre-mutate
    //- when only to_lower is needed.
    
    //mutate input before inspecting, if required
    void inline pre_mutate(std::string::iterator it, 
                            parsing_policy_enum policy);

    //inspect current char per parsing_policy 
    void inline inspect(std::string::iterator it, 
                parsing_policy_enum policy);

    //find out what already parsed part has become and process accordingly
    void introspect(const std::string& line,
                    parsing_policy_enum policy,
                    std::vector<std::string>* tokens_p);

    //updating parsing_info fields meant for staging tokenisation 
    //(such as preparing for committing qualified tokens) 
    //and for tracking side effects (such as tokens count).
    void stage();

    //throw if line has as much tokens as m_max_tokens_count
    void assure_tokens_count(const std::string& line);

    //commit token into the given tokens' container if current token 
    //is qualified for committing.
    void commit_token(const std::string& line,
                                std::vector<std::string>* tokens_p);

    //commit term delimiter to signify its position irrespective 
    //if current token is qualified for committing or not
    void commit_term_delimiter(const std::string& term_delimiter_token,
                                    std::vector<std::string>* tokens_p);

    //Special member function not supported
	term_parser(const term_parser&);
	term_parser& operator=(const term_parser&);
};



} //parser
} //text_scorer
} //instigate

#endif //TEXT_SCORER_PARSER_PARSER_HPP
