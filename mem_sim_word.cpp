#include "mem_sim_word.hpp"
#include "mem_sim_exceptions.hpp"
#include <vector>
#include <stdint.h>


word::word(const unsigned long long int iword_size) : word_size(iword_size)
{
	bytes.assign(iword_size, 0);
}

sim_error word::read(unsigned long long int &data) const
{
	data = 0;
	for (unsigned long long int i = 0; i < bytes.size(); i++)
		data |= (unsigned long long int)bytes[i] << (i * 8);
	
	
	return Success;
}

sim_error word::write(const unsigned long long int &data)
{
	for (unsigned long long int i = 0; i < bytes.size(); i++)
		bytes[i] = (data >> (i * 8)) & (1 << 8);

	return Success;
}

sim_error word::reset()
{
	bytes.assign(word_size, 0);
	return Success;
}