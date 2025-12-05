#include "instruction.h"
void load_instruction_t::execute(CPU& cpu) {
    // get the base register value
    data_t base_reg_val = cpu.reg_file_read(base_reg);
    // calculate the addr
    memory_addr_t addr = base_reg_val._unsigned + offset;
    // read from addr
    data_t read_val = cpu.d_cache_read(addr); // this is the val that is going to be stored at destination register

    switch(type) {
        case LOAD_INSTRUCTION_TYPE::LB: 
            read_val._signed &= (0x000000000000000F);
            break;
        case LOAD_INSTRUCTION_TYPE::LH:
            read_val._signed &= (0x00000000FFFFFFFF);
            break;
        case LOAD_INSTRUCTION_TYPE::LBU:
            read_val._unsigned &= (0x000000000000000F);
            break;
        case LOAD_INSTRUCTION_TYPE::LHU:
            read_val._unsigned &= (0x00000000FFFFFFFF);
            break;
        case LOAD_INSTRUCTION_TYPE::LW:
            break;
    }
    cpu.reg_file_commit(dest_src_reg, read_val);
}

void store_instruction_t::execute(CPU& cpu) {
    // get the source val
    data_t source_reg_val = cpu.reg_file_read(dest_src_reg);
    // calculate the addr
    data_t base_reg_val = cpu.reg_file_read(base_reg);
    memory_addr_t addr = base_reg_val._unsigned + offset;

    data_t commit_val = source_reg_val;
    switch(type) {
        case STORE_INSTRUCTION_TYPE::SB:
            commit_val._unsigned &= (0x000000000000000F);
        case STORE_INSTRUCTION_TYPE::SH:
            commit_val._unsigned &= (0x00000000FFFFFFFF);
            break;
        case STORE_INSTRUCTION_TYPE::SW:
            break;
    }
    cpu.d_cache_commit(addr, commit_val);
}
