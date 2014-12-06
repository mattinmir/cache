#ifndef CACHE_HPP
#define CACHE_HPP

#include "mem_sim_memory.hpp"
#include "exceptions.hpp"
#include <stdint.h>

class cache
{
public:
	cache(
		const unsigned int cache_size, // No. of sets/cache
		const unsigned int hit_time, // Time in cycles for a cache access (read/write)
		const unsigned int read_time, // Time in cycles for a memory read
		const unsigned int write_time // Time in cycles for a memory write
		);

	sim_error read(
		const unsigned int address, // Starting byte address of read
		unsigned int &data, // Variable to store read output in
		const unsigned int length // Number of bytes to read
		) const;

	sim_error write(
		const unsigned int address, // Starting address of write
		const unsigned int &data // Data to write to memory - program will write as many bytes as there are in data
		);

	sim_error reset(); // Set all locations to 0

private:
	std::vector<set> sets; // Resize appropriately with vector::resize
	memory mem;
};


class set
{
public:
	set(
		const unsigned int set_size // No. of blocks/set
		);

	sim_error read(
		const unsigned int block_index, // Starting block_index of read
		block* data[], // Variable to store read output in
		const unsigned int length // Number of blocks to read
		) const;

	sim_error write(
		const unsigned int block_index, // Starting block_index of write
		block* data[] // Data to write to memory - program will write as many words as there are in data
		);

	sim_error reset(); // Set all locations to 0

private:
	std::vector<block> blocks; // Resize appropriately with vector::resize
};

class block
{
public:
	block(
		const unsigned int block_size // No. of words/block
		);

	sim_error read(
		const unsigned int word_index, // Starting word_index of read
		word* data[], // Variable to store read output in
		const unsigned int length // Number of words to read
		) const;

	sim_error write(
		const unsigned int word_index, // Starting word_index of write
		word* data[] // Data to write to memory - program will write as many words as there are in data
		);

	sim_error reset(); // Set all locations to 0

private:
	std::vector<word> words; // Resize appropriately with vector::resize

};

class word
{
public:
	word(
		const unsigned int word_size // No. of bytes/word
		);

	sim_error read(
		const unsigned int byte_index, // Starting byte_index of read
		unsigned int* data[], // Variable to store read output in
		const unsigned int length // Number of bytes to read
		) const;

	sim_error write(
		const unsigned int byte_index, // Starting byte_index of write
		const unsigned int* data[] // Data to write to memory - program will write as many bytes as there are in data
		);

	sim_error reset(); // Set all locations to 0

private:
	std::vector<uint8_t> bytes; // Resize appropriately with vector::resize
};


#endif // !CACHE_HPP
