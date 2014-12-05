#ifndef CACHE_HPP
#define CACHE_HPP

#include "mem_sim_memory.hpp"
#include "exceptions.hpp"


class cache
{
public:
	cache(
		const unsigned int blocksize // No. of sets/cache
		);

	sim_error read(
		const unsigned int block_index, // Starting set_index of read
		unsigned int &data, // Variable to store read output in
		const unsigned int length // Number of sets to read
		) const;

	sim_error write(
		const unsigned int set_index, // Starting set_index of write
		const unsigned int &data // Data to write to memory - program will write as many words as there are in data
		);

	sim_error reset(); // Set all locations to 0

private:
	std::vector<set> sets; // Resize appropriately with vector::resize
};


class set
{
public:
	set(
		const unsigned int blocksize // No. of blocks/set
		);

	sim_error read(
		const unsigned int block_index, // Starting block_index of read
		unsigned int &data, // Variable to store read output in
		const unsigned int length // Number of blocks to read
		) const;

	sim_error write(
		const unsigned int block_index, // Starting block_index of write
		const unsigned int &data // Data to write to memory - program will write as many words as there are in data
		);

	sim_error reset(); // Set all locations to 0

private:
	std::vector<block> blocks; // Resize appropriately with vector::resize
};

class block
{
public:
	block(
		const unsigned int blocksize // No. of words/block
		);

	sim_error read(
		const unsigned int word_index, // Starting word_index of read
		unsigned int &data, // Variable to store read output in
		const unsigned int length // Number of words to read
		) const;

	sim_error write(
		const unsigned int word_index, // Starting word_index of write
		const unsigned int &data // Data to write to memory - program will write as many words as there are in data
		);

	sim_error reset(); // Set all locations to 0

private:
	std::vector<word> words; // Resize appropriately with vector::resize

};

class word
{
public:
	word(
		const unsigned int wordsize // No. of bytes/word
		);

	sim_error read(
		const unsigned int byte_index, // Starting byte_index of read
		unsigned int &data, // Variable to store read output in
		const unsigned int length // Number of bytes to read
		) const;

	sim_error write(
		const unsigned int byte_index, // Starting byte_index of write
		const unsigned int &data // Data to write to memory - program will write as many bytes as there are in data
		);

	sim_error reset(); // Set all locations to 0

private:
	std::vector<unsigned int> bytes; // Resize appropriately with vector::resize
};


#endif // !CACHE_HPP
