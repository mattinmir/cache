#ifndef MEM_SIM_BLOCK_HPP
#define MEM_SIM_BLOCK_HPP

#include "mem_sim_exceptions.hpp"
#include <vector>
#include "mem_sim_word.hpp"


typedef struct _block_metadata
{
	bool valid;
	bool dirty;
	unsigned int tag;

}block_metadata;

class block
{
public:
	block(
		const unsigned int iword_size, // No. of bytes/word
		const unsigned int iblock_size // No. of words/block
		);

	sim_error read(
		const unsigned int word_index, // Starting word_index of read
		word data[], // Variable to store read output in
		const unsigned int length // Number of words to read
		) const;

	sim_error write(
		const unsigned int word_index, // Starting word_index of write
		word* data[] // Data to write to memory - program will write as many words as there are in data
		);

	sim_error reset(); // Set all locations to 0

private:
	block_metadata meta;
	unsigned int block_size;
	std::vector<word> words; 

};

#endif // !MEM_SIM_BLOCK_HPP
