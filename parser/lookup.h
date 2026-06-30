/*
 * SPDX-FileCopyrightText: 2026 f3rhd 
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>   

#include "../aliases.h"
#include "../cpu/instruction.h"

class lookup_t {

public:
    lookup_t() = default;
    static reg_id_t                                         reg_id(const std::string &reg_string_id);
    static std::string                                      reg_name(const reg_id_t reg_id);
    static load_instruction_t::LOAD_INSTRUCTION_TYPE        load_type(const std::string &str);
    static store_instruction_t::STORE_INSTRUCTION_TYPE      store_type(const std::string &str);
    static alu_instruction_t::ALU_INSTRUCTION_TYPE          alui_type(const std::string &str);
    static alu_instruction_t::ALU_INSTRUCTION_TYPE          alur_type(const std::string &str);
    static branch_instruction_t::BRANCH_INSTRUCTION_TYPE    branch_type(const std::string &str);
    static jump_instruction_t::JUMP_INSTRUCTION_TYPE        jump_type(const std::string &str);
    static bool                                             is_imm(const std::string &str);
    static bool                                             is_pseudo(const std::string &str);

private:
    static const std::unordered_map<std::string, reg_id_t>                                              _str_to_id_registers;
    static const std::unordered_map<reg_id_t, std::string>                                              _id_to_str_registers;
    static const std::unordered_map<std::string,load_instruction_t::LOAD_INSTRUCTION_TYPE>              _load_instructions;
    static const std::unordered_map<std::string,store_instruction_t::STORE_INSTRUCTION_TYPE>            _store_instructions;
    static const std::unordered_map<std::string,alu_instruction_t::ALU_INSTRUCTION_TYPE>                _alui_instructions;
    static const std::unordered_map<std::string,alu_instruction_t::ALU_INSTRUCTION_TYPE>                _alur_instructions;
    static const std::unordered_map<std::string,branch_instruction_t::BRANCH_INSTRUCTION_TYPE>          _branch_instructions;
    static const std::unordered_map<std::string,jump_instruction_t::JUMP_INSTRUCTION_TYPE>              _jump_instructions;
    static const std::unordered_set<std::string>                                                        _pseudo_ops;
};