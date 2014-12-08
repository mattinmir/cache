#include "mem_sim_block.hpp"
#include "mem_sim_word.hpp"
#include "mem_sim_exceptions.hpp"

block::block(const unsigned long long int iword_size, const unsigned long long int iblock_size) : block_size(iblock_size), valid(0), dirty(0), tag(0), age(0)
{
	words.assign(iblock_size, word(iword_size));
}

sim_error block::read(std::vector<unsigned long long int> &data) const
{
	sim_error error = Success;
	for (unsigned long long int i = 0; i < words.size(); i++)
	{
		error = words[i].read(data[i]);
		if (error)
			return error;
	}
		
	return Success;
}

sim_error block::write(const std::vector<unsigned long long int> &data)
{
	sim_error error = Success;
	for (unsigned long long int i = 0; i < words.size(); i++)
	{
		error = words[i].write(data[i]);
		if (error)
			return error;
	}

	return Success;
}

bool block::is_valid() const
{
	return valid;
}

bool block::is_dirty() const
{
	return dirty;
}

unsigned long long int block::get_tag() const
{
	return tag;
}

unsigned long long int block::get_age() const
{
	return age;
}