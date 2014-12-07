#include "mem_sim_word.hpp"
#include "mem_sim_exceptions.hpp"
#include <vector>
#include <stdint.h>


word::word(const unsigned int iword_size) : word_size(iword_size)
{
	bytes.assign(iword_size, 0);
}

sim_error word::read(unsigned int &data) const
{
	data = 0;
	for (unsigned int i = 0; i < bytes.size(); i++)
		data |= bytes[i] << (i * 8);
	
	
	return Success;
}

sim_error word::write(const unsigned int &data)
{
	for (unsigned int i = 0; i < bytes.size(); i++)
		bytes[i] = data >> (i * 8);

	return Success;
}

sim_error word::reset()
{
	bytes.assign(word_size, 0);
	return Success;
}