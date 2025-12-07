#include "../aliases.h"
#include <ostream>
#pragma  once
class CPU {

public:
	CPU();
	void 			execute();
	void 			reset();
	bool 			halt() const;
	void			d_cache_commit(memory_addr_t mem_addr, data_t data);
	void			reg_file_commit(const reg_id_t& reg_id, data_t data);
	data_t			d_cache_read(memory_addr_t addr);
	data_t			reg_file_read(const reg_id_t& reg_id);
	void			jump_to_label(label_id_t label_);
	void			update_pc(memory_addr_t next_pc_val);
	void			load_program(program_t&& program_);
	void			log(std::ostream& os);
	memory_addr_t	get_pc() const;
private:
	bool _halt = false;
	memory_addr_t _pc = 0; // program counter
	program_t _program;
	d_cache_t _d_cache;
	reg_file_t _reg_file;
};