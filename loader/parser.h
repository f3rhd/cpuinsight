#pragma once

#include <vector>
#include <fstream>

#include "token.h"
#include "lookup.h"
class parser_t {
public:
    parser_t() = default;
    void parse_progam(const std::string& src);
private:
    void tokenize_line_text(const std::string &line_raw);
    void parse_line();
private:
    std::vector<token_t> _line_tokens;
    program_t            _program;
};