#include "mem_sim_set.hpp"
#include "mem_sim_block.hpp"
#include "mem_sim_exceptions.hpp"

set::set(const unsigned long long int iword_size, const unsigned long long int iblock_size, const unsigned long long int iset_size) : set_size(iset_size)
{
	blocks.assign(iset_size, block(iword_size, iblock_size));
}

sim_error set::read(const unsigned long long int tag, std::vector<unsigned long long int> &data) 
{
	bool found = false;
	unsigned long long int i;
	for (i = 0; i < blocks.size() && !found; i++)
	{
		if (blocks[i].get_tag() == tag)
		{
			if (blocks[i].is_valid())
				found = true;
		}
	}

	if (!found)
		return CacheMiss;

	sim_error error = blocks[i].read(data);
	return error;
}

sim_error set::write(const unsigned long long int tag, const std::vector<unsigned long long int> &data, const unsigned long long int word_index)
{
	bool found = false;
	unsigned long long int i;
	for (i = 0; i < blocks.size() && !found; i++)
	{
		if (blocks[i].get_tag() == tag)
		{
			if (blocks[i].is_valid())
				found = true;
		}
	}

	if (!found)
		return CacheMiss;
	
	// Input data from user will be 1 word, but we can only write one block at a time, so create a new vector for the block data with the correct word changed to the input
	std::vector <unsigned long long int> new_block_data;
	blocks[i].read(new_block_data);
	new_block_data[word_index] = data[0];

	sim_error error = blocks[i].write(new_block_data);
	return error;
}

unsigned long long int set::get_set_size() const
{
	return set_size;
}

sim_error set::replace_LRU_block(const std::vector<unsigned long long int> new_block, std::vector<unsigned long long int> &old_block, unsigned long long int &old_block_tag, bool &flush_old_block)
{
	sim_error error = Success;
	unsigned long long int lru_index = 0;
	for (unsigned long long int i = 1; i < blocks.size(); i++)

	{
		if (blocks[i].get_age() > blocks[lru_index].get_age())
			lru_index = i;
	}

	if (blocks[lru_index].is_dirty() && blocks[lru_index].is_valid())
	{
		flush_old_block = true;
		error = blocks[lru_index].read(old_block);
		old_block_tag = blocks[lru_index].get_tag();
	}
	else
		flush_old_block = false;

	if (!error)
		error = blocks[lru_index].write(new_block); 

	return error;
}