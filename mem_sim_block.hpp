#ifndef MEM_SIM_BLOCK_HPP
#define MEM_SIM_BLOCK_HPP

#include "mem_sim_exceptions.hpp"
#include "mem_sim_word.hpp"
#include <vector>


class block
{
public:
	block(
		const unsigned long long int iword_size, // No. of bytes/word
		const unsigned long long int iblock_size // No. of words/block
		);

	sim_error read(
		std::vector<unsigned long long int> &data // Variable to store read output in
		);

	sim_error write(
		const std::vector<unsigned long long int> &data,
		unsigned long long int itag
		);


	bool is_valid() const;

	bool is_dirty() const;

	unsigned long long int get_tag() const;

	unsigned long long int get_age() const;

	void set_valid(bool new_valid);

	void set_dirty(bool new_dirty);

	void set_tag(unsigned long long int new_tag);


private:
	bool valid;
	bool dirty;
	unsigned long long int tag;
	unsigned long long int age;
	unsigned long long int block_size;
	std::vector<word> words; 

};

block::block(const unsigned long long int iword_size, const unsigned long long int iblock_size)
: block_size(iblock_size), valid(0), dirty(0), tag(0), age(0)
{
	words.assign(iblock_size, word(iword_size));
}

sim_error block::read(std::vector<unsigned long long int> &data)
{
	sim_error error = Success;
	for (unsigned long long int i = 0; i < words.size(); i++)
	{
		error = words[i].read(data[i]);
		if (error)
			return error;
	}

	age = 0;

	return Success;
}

sim_error block::write(const std::vector<unsigned long long int> &data, unsigned long long int itag)
{
	sim_error error = Success;
	for (unsigned long long int i = 0; i < words.size(); i++)
	{
		error = words[i].write(data[i]);
		if (error)
			return error;
	}
	tag = itag;

	age = 0;

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

void block::set_valid(bool new_valid)
{
	valid = new_valid;
}

void block::set_dirty(bool new_dirty)
{
	dirty = new_dirty;
}

void block::set_tag(unsigned long long int new_tag)
{
	tag = new_tag;
}


#endif // !MEM_SIM_BLOCK_HPP
