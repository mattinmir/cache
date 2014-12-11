#ifndef MEM_SIM_SET_HPP
#define MEM_SIM_SET_HPP

#include "mem_sim_exceptions.hpp"
#include "mem_sim_cache.hpp"
#include "mem_sim_block.hpp"
#include "mem_sim_utils.hpp"
#include <vector>
#include <string>
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


	sim_error replace_LRU_block(
		const std::vector<unsigned long long int> new_block, // New block to be written into cache
		const unsigned long long int new_block_tag, // Tag of new block to se can set the tag field of the block
		std::vector<unsigned long long int> &old_block, // Return old block value so cache can write it back to memory
		unsigned long long int &old_block_tag, // Tag of old block so we can put it back into memory if needed
		bool &flush_old_block, // If there was a dirty block in the position, we must flush to memory
		std::string access_type // If "read": dirty = false. if "write": dirty = true. Read-misses produce a clean block, whereas write-misses write to it after fetching from memory, dirtying it
		);

	unsigned long long int get_set_size() const;

	sim_error flush(
		std::vector<block_data_t> &block_data, // Holds the tag and byte vectors of blocks to be flushed
		unsigned long long int word_size
		);

private:
	unsigned long long int set_size;
	unsigned long long int block_size;

	std::vector<block> blocks; 
};

set::set(const unsigned long long int iword_size, const unsigned long long int iblock_size, const unsigned long long int iset_size)
: set_size(iset_size), block_size(iblock_size)
{
	blocks.assign(iset_size, block(iword_size, iblock_size));
}

sim_error set::read(const unsigned long long int tag, std::vector<unsigned long long int> &data)
{
	bool found = false;
	unsigned long long int i;

	// Find a valid block with matching tag in the set
	for (i = 0; i < blocks.size() && !found; i++)
	{
		if (blocks[i].get_tag() == tag)
		{
			if (blocks[i].is_valid())
				found = true;
		}
	}
	i -= 1; // Need to -1 because the for loop increments i again after the loop has ended
	if (!found)
		return CacheMiss;

	sim_error error = blocks[i].read(data);
	return error;
}

sim_error set::write(const unsigned long long int tag, const std::vector<unsigned long long int> &data, const unsigned long long int word_index)
{
	bool found = false;
	unsigned long long int i;

	// Find a valid block with matching tag in the set
	for (i = 0; i < blocks.size() && !found; i++)
	{
		if (blocks[i].get_tag() == tag)
		{
			if (blocks[i].is_valid())
				found = true;
		}
	}

	i -= 1; // Need to -1 because the for loop increments i again after the loop has ended

	if (!found)
		return CacheMiss;

	// Input data from user will be 1 word, but we can only write one block at a time, so create a new vector for the block data with the correct word changed to the input
	std::vector <unsigned long long int> new_block_data(block_size);
	blocks[i].read(new_block_data);
	new_block_data[word_index] = data[0];

	sim_error error = blocks[i].write(new_block_data, tag);
	if (!error)
		blocks[i].set_dirty(true);

	return error;
}

unsigned long long int set::get_set_size() const
{
	return set_size;
}

sim_error set::replace_LRU_block(const std::vector<unsigned long long int> new_block, const unsigned long long int new_block_tag, std::vector<unsigned long long int> &old_block, unsigned long long int &old_block_tag, bool &flush_old_block, std::string access_type)
{
	sim_error error = Success;
	unsigned long long int lru_index = 0;

	// First try to find an unused block in the set
	bool found_empty = false;
	for (unsigned long long int i = 0; i < blocks.size() && !found_empty; i++)
	{
		if (!blocks[i].is_valid())
		{
			found_empty = true;
			lru_index = i;
			if (!error)
				error = blocks[lru_index].write(new_block, new_block_tag);
			if (!error)
			{
				blocks[lru_index].set_valid(true);
				blocks[lru_index].set_tag(new_block_tag);
				flush_old_block = false; // No flush needed as old block was invalid
				if (access_type == "write")
					blocks[lru_index].set_dirty(true);
				else if (access_type == "read")
					blocks[lru_index].set_dirty(false);

			}

		}
	}

	// If an unused block is not found, use LRU replacement
	if (!found_empty)
	{
		for (unsigned long long int i = 1; i < blocks.size(); i++)
		{
			if (blocks[i].get_age() > blocks[lru_index].get_age())
				lru_index = i;
		}


		// If the old block was dirty, mark it to be flushed to memory
		if (blocks[lru_index].is_dirty() && blocks[lru_index].is_valid())
		{
			flush_old_block = true;
			error = blocks[lru_index].read(old_block);
			old_block_tag = blocks[lru_index].get_tag();
		}
		else
			flush_old_block = false;

		if (!error)
			error = blocks[lru_index].write(new_block, new_block_tag);

		if (!error)
		{
			blocks[lru_index].set_valid(true);
			blocks[lru_index].set_tag(new_block_tag);
			if (access_type == "write")
				blocks[lru_index].set_dirty(true);
			else if (access_type == "read")
				blocks[lru_index].set_dirty(false);
		}
	}

	return error;
}

sim_error set::flush(std::vector<block_data_t> &block_data, unsigned long long int word_size)
{
	sim_error error;
	block_data = {};
	std::vector<block>::iterator it;
	std::vector<unsigned long long int> data(block_size);
	for (it = blocks.begin(); it != blocks.end(); ++it)
	{
		if (it->is_dirty() && it->is_valid())
		{
			it->read(data);
			block_data.push_back({ it->get_tag(), words_to_bytes(data, word_size) });
			it->set_dirty(false);
		}
	}

	return Success;
}

#endif // !MEM_SIM_SET_HPP
