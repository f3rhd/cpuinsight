#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "../instruction/instruction.h"

union data_t {
	uint64_t _unsigned;
	int64_t  _signed;
};
using memory_addr_t = uint64_t;
using reg_id_t = std::string;
using i_cache_t = std::vector<instruction_t>;
using d_cache_t = std::unordered_map<memory_addr_t, data_t>;
using reg_file_t = std::unordered_map<reg_id_t, data_t>;

