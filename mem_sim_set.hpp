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
		const unsigned int block_index, // Starting block_index of read
		block data[], // Variable to store read output in
		const unsigned int length // Number of blocks to read
		) const;

	sim_error write(
		const unsigned int block_index, // Starting block_index of write
		block data[] // Data to write to memory - program will write as many words as there are in data
		);

	sim_error reset(); // Set all locations to 0

private:
	unsigned int set_size;
	std::vector<block> blocks; 
};

#endif // !MEM_SIM_SET_HPP
