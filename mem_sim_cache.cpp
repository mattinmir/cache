#include "mem_sim_cache.hpp"
#include "mem_sim_set.hpp"
#include "mem_sim_exceptions.hpp"
#include <cmath>
#include <vector>

cache::cache(
	const unsigned int imemory_size,
	const unsigned int iword_size,
	const unsigned int iblock_size,
	const unsigned int iset_size,
	const unsigned int icache_size,
	const unsigned int ihit_time,
	const unsigned int iread_time,
	const unsigned int iwrite_time
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
	block_index_size(log2(iset_size)),
	set_index_size(log2(icache_size)), 
	tag_size(imemory_size - (byte_index_size + word_index_size + block_index_size + set_index_size))
{
	sets.assign(iset_size, set(iword_size, iblock_size, iset_size));
}

sim_error cache::read(const unsigned int address, std::vector<unsigned int> &data, unsigned int &time) const
{
	/*
					 set_index_size (bits)
	                  <----------->
				 __________________________________________________________
				|     |           |             |            |            |
	address:	| Tag | Set_Index | Block_index | Word_index | Byte_index |
				|_____|___________|_____________|____________|____________|

	*/
	unsigned int set_index = (address & (unsigned int)(pow(2, set_index_size) - 1) << (byte_index_size + word_index_size + block_index_size)) >> (byte_index_size + word_index_size + block_index_size);
	unsigned int block_index = (address & (unsigned int)(pow(2, block_index_size) - 1) << (byte_index_size + word_index_size)) >> (byte_index_size + word_index_size);
	unsigned int tag = (address & (unsigned int)(pow(2, tag_size) - 1) << (byte_index_size + word_index_size + block_index_size + set_index_size)) >> (byte_index_size + word_index_size + block_index_size + set_index_size);
	
	sim_error error = sets[set_index].read(tag, data);

	if (error == CacheMiss)
	{
		std::vector<unsigned int> old_block(word_size * block_size);
		std::vector<unsigned int> new_block(word_size * block_size);
		bool flush_needed;

		error = mem.read(address, new_block);

		sets[set_index].replace_LRU_block(new_block, old_block, flush_needed);


	}
	
	return error;
}