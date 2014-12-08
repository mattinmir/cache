#include "mem_sim_set.hpp"
#include "mem_sim_block.hpp"
#include "mem_sim_exceptions.hpp"

set::set(const unsigned long long int iword_size, const unsigned long long int iblock_size, const unsigned long long int iset_size) : set_size(iset_size)
{
	blocks.assign(iset_size, block(iword_size, iblock_size));
}

sim_error set::read(const unsigned long long int tag, std::vector<unsigned long long int> &data) const
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

sim_error set::write(const unsigned long long int tag, const std::vector<unsigned long long int> &data)
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

	sim_error error = blocks[i].write(data);
	return error;
}

unsigned long long int set::get_set_size() const
{
	return set_size;
}

sim_error set::replace_LRU_block(const std::vector<unsigned long long int> new_block, std::vector<unsigned long long int> &old_block, bool &flush_old_block)
{
	sim_error error = Success;
	unsigned long long int lru_index = 0;
	for (unsigned long long int i = 1; i < blocks.size(); i++)

	{
		if (blocks[i].get_age() > blocks[lru_index].get_age())
			lru_index = i;
	}

	if (blocks[lru_index].is_dirty())
	{
		flush_old_block = true;
		error = blocks[lru_index].read(old_block);
	}
	else
		flush_old_block = false;

	if (!error)
		error = blocks[lru_index].write(new_block); 

	return error;
}