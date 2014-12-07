#include "mem_sim_memory.hpp"
#include "mem_sim_exceptions.hpp"
#include <stdint.h>

memory::memory(unsigned int addr_bits)
{
	mem.assign(1 << addr_bits, 0);
}

sim_error memory::read(const unsigned int address, std::vector<unsigned int> &data) const
{
	if (address > mem.size())
		return Error_AddressOutOfRange;
	if (address + data.size() > mem.size())
		return Error_IndexExceedsContainerSize;

	for (unsigned int i = address, j = 0; i < data.size(); i++, j++)
		data[j] = mem[i];

	return Success;
}

sim_error memory::write(const unsigned int address, const std::vector<unsigned int> &data)
{
	if (address > mem.size())
		return Error_AddressOutOfRange;
	if (address + data.size() > mem.size())
		return Error_IndexExceedsContainerSize;

	for (unsigned int i = address, j = 0; i < data.size(); i++, j++)
		mem[i] = data[j];

	return Success;
}