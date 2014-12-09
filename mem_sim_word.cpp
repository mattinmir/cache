#include "mem_sim_word.hpp"
#include "mem_sim_exceptions.hpp"
#include "mem_sim_utils.hpp"
#include <vector>
#include <stdint.h>


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

sim_error word::reset()
{
	bytes.assign(word_size, 0);
	return Success;
}