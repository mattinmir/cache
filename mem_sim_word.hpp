#ifndef MEM_SIM_WORD_HPP
#define MEM_SIM_WORD_HPP

#include "mem_sim_exceptions.hpp"
#include <vector>
#include <stdint.h>

class word
{
public:
	word(
		const unsigned int iword_size // No. of bytes/word
		);

	sim_error read(
		unsigned int &data // Variable to store read output in
		) const;

	sim_error write(
		const unsigned int &data // Data to write to memory - program will write as many bytes as there are in data
		);

	sim_error reset(); // Set all locations to 0

private:
	unsigned int word_size; // No. of bytes/word
	std::vector<uint8_t> bytes;
};

#endif // !MEM_SIM_WORD_HPP
