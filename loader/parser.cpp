#include "parser.h"
#include <iostream>

void parser_t::parse_progam(const std::string& src) {
    std::ifstream file(src);
    if (!file.is_open()) {
        std::cout << "File path " << src << " doesn't exist.\n";
        exit(EXIT_FAILURE);
    }
    std::string line_raw;
    while (std::getline(file, line_raw)) {
        tokenize_line_text(line_raw);
        parse_line();
    }
    file.close();
}

void parser_t::parse_line() {
}
void parser_t::tokenize_line_text(const std::string& line_raw) {

    _line_tokens.clear();
    size_t comment_pos = line_raw.find('#');
    std::string line = (comment_pos != std::string::npos) ? line_raw.substr(0, comment_pos) : line_raw;
    if (line == line_raw) {
        comment_pos = line_raw.find(';');
        line = (comment_pos != std::string::npos) ? line_raw.substr(0, comment_pos) : line_raw;
    }
    size_t i = 0;
    while (i < line.size()) {
        char ch = line[i];

        // Skip whitespace
        if (std::isspace(static_cast<unsigned char>(ch))) {
            ++i;
            continue;
        }

        // Handle single-char _line_tokens
        if (ch == ',' || ch == '(' || ch == ')') {
            TOKEN_TYPE type;
            if (ch == ',') type = TOKEN_TYPE::COMMA;
            else if (ch == '(') type = TOKEN_TYPE::LPAREN;
            else type = TOKEN_TYPE::RPAREN;

            _line_tokens.emplace_back(std::string(1, ch), type);
            ++i;
            continue;
        }

        // Match [a-zA-Z0-9_.:-]+
        size_t start = i;
        while (i < line.size() && (std::isalnum(static_cast<unsigned char>(line[i])) || line[i] == '_' || line[i] == '.' || line[i] == '-' || line[i] == ':')) {
            ++i;
        }

        if (start == i)
            continue;

        std::string token = line.substr(start, i - start);

        // Handle label: `label:`
        if (!token.empty() && token.back() == ':') {
            _line_tokens.emplace_back(token.substr(0, token.length() - 1), TOKEN_TYPE::LABEL);
            continue;
        }

        if(lookup_t::load_type(token) != load_instruction_t::LOAD_INSTRUCTION_TYPE::UNKNOWN){
            _line_tokens.emplace_back(token, TOKEN_TYPE::LOAD_OPERATION);
        } else if(lookup_t::store_type(token) != store_instruction_t::STORE_INSTRUCTION_TYPE::UNKNOWN) {
            _line_tokens.emplace_back(token, TOKEN_TYPE::STORE_OPERATION);
        } else if(lookup_t::alui_type(token) != alu_instruction_t::ALU_INSTRUCTION_TYPE::UNKNOWN) {
            _line_tokens.emplace_back(token, TOKEN_TYPE::ALU_OPERATION_I);
        } else if(lookup_t::alur_type(token) != alu_instruction_t::ALU_INSTRUCTION_TYPE::UNKNOWN) {
            _line_tokens.emplace_back(token, TOKEN_TYPE::ALU_OPERATION_R);
        } else if(lookup_t::branch_type(token) != branch_instruction_t::BRANCH_INSTRUCTION_TYPE::UNKNOWN) {
            _line_tokens.emplace_back(token, TOKEN_TYPE::BRANCH_OPERATION);
        } else if(lookup_t::jump_type(token) != jump_instruction_t::JUMP_INSTRUCTION_TYPE::UNKNOWN) {
            _line_tokens.emplace_back(token, TOKEN_TYPE::JUMP_OPERATION);
        } else if(token == "lui") {
            _line_tokens.emplace_back(token, TOKEN_TYPE::LOAD_UPPER);
        } else if(token == "auipc") {
            _line_tokens.emplace_back(token, TOKEN_TYPE::AUIPC);
        } else if(lookup_t::is_imm(token)) {
            _line_tokens.emplace_back(token, TOKEN_TYPE::IMMEDIATE);
        }
        else {
            _line_tokens.emplace_back(token, TOKEN_TYPE::IDENTIFIER);
        }
    }
}

