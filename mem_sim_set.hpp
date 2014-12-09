#ifndef MEM_SIM_SET_HPP
#define MEM_SIM_SET_HPP

#include "mem_sim_exceptions.hpp"
#include <vector>
#include "mem_sim_block.hpp"



class set
{
public:
	set(
		const unsigned long long int iword_size, // No. of bytes/word
		const unsigned long long int iblock_size, // No. of words/block
		const unsigned long long int iset_size // No. of blocks/set
		);

	sim_error read(
		const unsigned long long int tag, // Tag data of required block
		std::vector<unsigned long long int> &data // Variable to store read output in
		);

	sim_error write(
		const unsigned long long int tag, // Starting block_index of write
		const std::vector<unsigned long long int> &data, // Data to write to memory - program will write as many words as there are in data
		const unsigned long long int word_index
		);

	sim_error reset(); // Set all locations to 0

	sim_error replace_LRU_block(
		const std::vector<unsigned long long int> new_block, // New block to be written into cache
		std::vector<unsigned long long int> &old_block, // Return old block value so cache can write it back to memory
		unsigned long long int &old_block_tag, // Tag of old block so we can put it back into memory if needed
		bool &flush_old_block
		);

	unsigned long long int get_set_size() const;

private:
	unsigned long long int set_size;
	std::vector<block> blocks; 
};

#endif // !MEM_SIM_SET_HPP
