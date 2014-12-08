#ifndef MEM_SIM_WORD_HPP
#define MEM_SIM_WORD_HPP

#include "mem_sim_exceptions.hpp"
#include <vector>
#include <stdint.h>

class word
{
public:
	word(
		const unsigned long long int iword_size // No. of bytes/word
		);

	sim_error read(
		unsigned long long int &data // Variable to store read output in
		) const;

	sim_error write(
		const unsigned long long int &data // Data to write to memory - program will write as many bytes as there are in data
		);

	sim_error reset(); // Set all locations to 0

private:
	unsigned long long int word_size; // No. of bytes/word
	std::vector<uint8_t> bytes;
};

#endif // !MEM_SIM_WORD_HPP
