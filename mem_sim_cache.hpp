#ifndef MEM_SIM_CACHE_HPP
#define MEM_SIM_CACHE_HPP

#include "mem_sim_memory.hpp"
#include "mem_sim_exceptions.hpp"
#include <stdint.h>
#include "mem_sim_set.hpp"


class cache 
{
public:
	cache(
		const unsigned int imemory_size, // No. of locations in memory
		const unsigned int iword_size, // No. of bytes/word
		const unsigned int iblock_size, // No. of words/block
		const unsigned int iset_size, // No. of blocks/set
		const unsigned int icache_size, // No. of sets/cache
		const unsigned int ihit_time, // Time in cycles for a cache access (read/write)
		const unsigned int iread_time, // Time in cycles for a memory read
		const unsigned int iwrite_time // Time in cycles for a memory write
		);

	sim_error read(
		const unsigned int address, // Starting byte address of read
		std::vector<unsigned int> &data, // Variable to store read output in
		unsigned int &time // How many cycles the operation took
		) const;

	sim_error write(
		const unsigned int address, // Starting address of write
		const  std::vector<unsigned int> &data, // Data to write to memory - program will write as many bytes as there are in data
		unsigned int &time // How many cycles the operation took
		);

	sim_error flush(
		unsigned int &time // How many cycles the operation took
		);

	sim_error debug(unsigned int debug_level);

	sim_error reset(); // Set all locations to 0

private:
	unsigned int word_size;
	unsigned int block_size;
	unsigned int set_size;
	unsigned int cache_size;
	unsigned int hit_time;
	unsigned int read_time;
	unsigned int write_time;
	std::vector<set> sets; 
	memory mem;

	//Sizes in bits of different parts of address
	unsigned int byte_index_size;
	unsigned int word_index_size;
	unsigned int block_index_size;
	unsigned int set_index_size;
	unsigned int tag_size;
};


#endif // !MEM_SIM_CACHE_HPP
