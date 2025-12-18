#pragma once
#include "../aliases.h"
class branch_predictor_t {
public:
    virtual void update(branch_instruction_id_t branch_id, bool branch_taken) = 0;
    virtual bool predict(branch_instruction_id_t branch_id) = 0;
    virtual ~branch_predictor_t() = default;
};

class simple_predictor_t : public branch_predictor_t {
public:
    void update(branch_instruction_id_t branch_id, bool branch_taken) override;
    bool predict(branch_instruction_id_t branch_id) override;
    simple_predictor_t() = default;
private:
   branch_history_table_t _bht;
};

// global branch history shift register, adaptive predictor (2bit fsm saturating counter) , global pattern history table
class GAg_predictor_t : public branch_predictor_t {
public:
    void update(branch_instruction_id_t branch_id, bool branch_taken) override;
    bool predict(branch_instruction_id_t branch_id) override;
private:
    uint64_t _branch_shift_register = 0;
    std::unordered_map<uint64_t, branch_history_t> _pattern_history_table;
};
// per branch history shift register per branch instruction, adaptive predictor (2bit fsm saturating counter), global pattern history table
class PAg_predictor_t : public branch_predictor_t {
public:
    void update(branch_instruction_id_t branch_id, bool branch_taken) override;
    bool predict(branch_instruction_id_t branch_id) override;
private:
    std::unordered_map<branch_instruction_id_t, uint64_t> _branch_history_shift_register_table;
    std::unordered_map<uint64_t, branch_history_t> _pattern_history_table;
};

class gshare_predictor_t : public branch_predictor_t {
public:
    void update(branch_instruction_id_t branch_id, bool branch_taken) override;
    bool predict(branch_instruction_id_t branch_id) override;
private:
    uint64_t _branch_shift_register = 0;
    std::unordered_map<uint64_t, branch_history_t> _pattern_history_table;
};