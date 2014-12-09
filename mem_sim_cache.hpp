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
		const unsigned long long int imemory_size, // No. of locations in memory
		const unsigned long long int iword_size, // No. of bytes/word
		const unsigned long long int iblock_size, // No. of words/block
		const unsigned long long int iset_size, // No. of blocks/set
		const unsigned long long int icache_size, // No. of sets/cache
		const unsigned long long int ihit_time, // Time in cycles for a cache access (read/write)
		const unsigned long long int iread_time, // Time in cycles for a memory read
		const unsigned long long int iwrite_time // Time in cycles for a memory write
		);

	sim_error read(
		const unsigned long long int address, // Starting byte address of read
		std::vector<unsigned long long int> &data, // Variable to store read output in
		unsigned long long int &time // How many cycles the operation took
		);

	sim_error write(
		const unsigned long long int address, // Starting address of write
		const  std::vector<unsigned long long int> &data, // Data to write to memory - program will write as many bytes as there are in data
		unsigned long long int &time // How many cycles the operation took
		);

	sim_error flush(
		unsigned long long int &time // How many cycles the operation took
		);

	sim_error debug(unsigned long long int debug_level);

	sim_error reset(); // Set all locations to 0


private:
	unsigned long long int word_size;
	unsigned long long int block_size;
	unsigned long long int set_size;
	unsigned long long int cache_size;
	unsigned long long int hit_time;
	unsigned long long int read_time;
	unsigned long long int write_time;
	std::vector<set> sets; 
	memory mem;

	//Sizes in bits of different parts of address
	unsigned long long int byte_index_size;
	unsigned long long int word_index_size;
	unsigned long long int set_index_size;
	unsigned long long int tag_size;
};


#endif // !MEM_SIM_CACHE_HPP
