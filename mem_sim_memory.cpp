#include "mem_sim_memory.hpp"
#include "mem_sim_exceptions.hpp"
#include <stdint.h>

memory::memory(unsigned long long int addr_bits)
{
	mem.assign(1 << addr_bits, 0);
}

sim_error memory::read(const unsigned long long int address, std::vector<uint8_t> &data) const
{
	if (address > mem.size())
		return Error_AddressOutOfRange;
	if (address + data.size() > mem.size())
		return Error_IndexExceedsContainerSize;

	for (unsigned long long int i = address, j = 0; i < address + data.size(); i++, j++)
		data[j] = mem[i];

	return Success;
}

sim_error memory::write(const unsigned long long int address, const std::vector<uint8_t> &data)
{
	if (address > mem.size())
		return Error_AddressOutOfRange;
	if (address + data.size() > mem.size())
		return Error_IndexExceedsContainerSize;

	for (unsigned long long int i = address, j = 0; i < address + data.size(); i++, j++)
		mem[i] = data[j];

	return Success;
}