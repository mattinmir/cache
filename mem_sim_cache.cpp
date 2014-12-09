#include "mem_sim_cache.hpp"
#include "mem_sim_set.hpp"
#include "mem_sim_exceptions.hpp"
#include "mem_sim_utils.hpp"
#include <cmath>
#include <vector>

cache::cache(
	const unsigned long long int imemory_size,
	const unsigned long long int iword_size,
	const unsigned long long int iblock_size,
	const unsigned long long int iset_size,
	const unsigned long long int icache_size,
	const unsigned long long int ihit_time,
	const unsigned long long int iread_time,
	const unsigned long long int iwrite_time
	) : 
	word_size(iword_size),
	block_size(iblock_size),
	set_size(iset_size),
	cache_size(icache_size),
	hit_time(ihit_time), 
	read_time(iread_time), 
	write_time(iwrite_time), 
	mem(memory(imemory_size)),
	byte_index_size(log2(iword_size)), 
	word_index_size(log2(iblock_size)),
	set_index_size(log2(icache_size)), 
	tag_size(imemory_size - (byte_index_size + word_index_size + set_index_size))
{
	sets.assign(icache_size, set(iword_size, iblock_size, iset_size));
}

sim_error cache::read(const unsigned long long int address, std::vector<unsigned long long int> &data, unsigned long long int &time)
{
	/*
					 set_index_size (bits)
	                  <----------->
				 ___________________________________________
				|     |           |            |            |
	address:	| Tag | Set_Index | Word_index | Byte_index |
				|_____|___________|____________|____________|

	*/

	// pow(2, index_size) - 1 gives a binary number of size index_size bits, with each digit 1. This is shifted up to the correct position and used as a bitmask to extract the relevant field. That is shifted back down to get the value of that field
	unsigned long long int set_index = (address & (unsigned long long int)(pow(2, set_index_size) - 1) << (byte_index_size + word_index_size)) >> (byte_index_size + word_index_size); 
	unsigned long long int tag = (address & (unsigned long long int)(pow(2, tag_size) - 1) << (byte_index_size + word_index_size + set_index_size)) >> (byte_index_size + word_index_size + set_index_size);
	
	sim_error error = sets[set_index].read(tag, data);

	if (error == CacheMiss)
	{
		error = Success;

		std::vector<unsigned long long int> old_block(block_size);
		std::vector<uint8_t> new_block_bytes(word_size * block_size);
		unsigned long long int old_block_tag;
		bool flush_needed;
		

		if (!error)
			error = mem.read(address, new_block_bytes);

		if (!error)
			error = sets[set_index].replace_LRU_block(bytes_to_words(new_block_bytes, word_size), old_block, old_block_tag, flush_needed);

		if (!error && flush_needed)
			// old_block_tag * block_size * word_size reconstitutes the old block's address in memory, because the tag == block address
			error = mem.write((old_block_tag * block_size * word_size), words_to_bytes(old_block, word_size));
	}
	
	return error;
}

sim_error cache::write(const unsigned long long int address, const  std::vector<unsigned long long int> &data, unsigned long long int &time)
{
	return Success;
}

sim_error cache::flush(unsigned long long int &time)
{
	return Success;
}

sim_error cache::debug(unsigned long long int debug_level)
{
	return Success;
}
