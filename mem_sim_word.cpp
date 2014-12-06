#include "mem_sim_word.hpp"
#include "mem_sim_exceptions.hpp"
#include <vector>
#include <stdint.h>

word::word(const unsigned int iword_size) : word_size(iword_size)
{
	bytes.assign(iword_size, 0);
}

sim_error word::read(const unsigned int byte_index, unsigned int data[], const unsigned int length) const
{
	if ((byte_index + length) >= word_size)
		return Error_IteratorExceedsContainerSize;
	

	for (int i = byte_index, j = 0; i < (byte_index + length); i++, j++)
		data[j] = bytes[i];

	return Success;
}

sim_error word::reset()
{
	bytes.assign(word_size, 0);
	return Success;
}