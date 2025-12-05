#include "../common/aliases.h"
#include "../cpu/cpu.h"
class CPU;
struct instruction_t {
    virtual void execute(CPU &cpu) = 0;
    virtual ~instruction_t() = default;
};
struct memory_instruction_t : instruction_t {
    reg_id_t dest_src_reg;
    reg_id_t base_reg;
    offset_t offset;
    void execute(CPU &cpu) override = 0;
    memory_instruction_t(const reg_id_t& dest_reg_, const reg_id_t& base_reg_, offset_t offset_) : 
                        dest_src_reg(dest_reg_),
                        base_reg(base_reg_),
                        offset(offset_) {}
};
struct load_instruction_t : memory_instruction_t {
    enum class LOAD_INSTRUCTION_TYPE
    {
        LB,
        LH,
        LW,
        LBU,
        LHU,
    } type;
    void execute(CPU &cpu) override;
    load_instruction_t(const reg_id_t& dest_reg_, const reg_id_t& base_reg_, offset_t offset_,LOAD_INSTRUCTION_TYPE type_) : 
                        memory_instruction_t(dest_reg_,base_reg_,offset_), type(type_) {}
};
struct store_instruction_t : memory_instruction_t {
    enum class STORE_INSTRUCTION_TYPE
    {
        SB,
        SH,
        SW
    } type;
    void execute(CPU &cpu) override;
    store_instruction_t(const reg_id_t& dest_reg_, const reg_id_t& base_reg_, offset_t offset_,STORE_INSTRUCTION_TYPE type_) : 
                        memory_instruction_t(dest_reg_,base_reg_,offset_), type(type_) {}
};