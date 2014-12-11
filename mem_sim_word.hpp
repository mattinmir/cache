#ifndef MEM_SIM_WORD_HPP
#define MEM_SIM_WORD_HPP

#include "mem_sim_exceptions.hpp"
#include "mem_sim_utils.hpp"
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


private:
	unsigned long long int word_size; // No. of bytes/word
	std::vector<uint8_t> bytes;
};

word::word(const unsigned long long int iword_size) : word_size(iword_size)
{
	bytes.assign(iword_size, 0);
}

sim_error word::read(unsigned long long int &data) const
{
	std::vector<unsigned long long int> temp = bytes_to_words(bytes, word_size);
	data = temp[0];

	return Success;
}

sim_error word::write(const unsigned long long int &data)
{
	std::vector<unsigned long long int> temp = { data };
	bytes = words_to_bytes(temp, word_size);

	return Success;
}

#endif // !MEM_SIM_WORD_HPP
