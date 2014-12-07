#ifndef MEM_SIM_SET_HPP
#define MEM_SIM_SET_HPP

#include "mem_sim_exceptions.hpp"
#include <vector>
#include "mem_sim_block.hpp"



class set
{
public:
	set(
		const unsigned int iword_size, // No. of bytes/word
		const unsigned int iblock_size, // No. of words/block
		const unsigned int iset_size // No. of blocks/set
		);

	sim_error read(
		const unsigned int tag, // Tag data of required block
		std::vector<unsigned int> &data // Variable to store read output in
		) const;

	sim_error write(
		const unsigned int tag, // Starting block_index of write
		const std::vector<unsigned int> &data // Data to write to memory - program will write as many words as there are in data
		);

	sim_error reset(); // Set all locations to 0

	sim_error replace_LRU_block(
		const std::vector<unsigned int> new_block, // New block to be written into cache
		std::vector<unsigned int> &old_block, // Return old block value so cache can write it back to memory
		bool &flush_old_block
		);

	unsigned int get_set_size() const;

private:
	unsigned int set_size;
	std::vector<block> blocks; 
};

#endif // !MEM_SIM_SET_HPP
