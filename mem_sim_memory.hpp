#ifndef MEM_SIM_MEMORY_HPP
#define MEM_SIM_MEMORY_HPP

#include "mem_sim_exceptions.hpp"
#include <vector>
#include <stdint.h>

class memory
{
public:
	memory(
		unsigned long long int addr_bits // Size of the memory is 2^addr_bits == 1 << addr_bits
		);
	
	sim_error read(
		const unsigned long long int address, // Starting byte address of read
		std::vector<uint8_t> &data // Variable to store read output in
		) const;

	sim_error write(
		const unsigned long long int address, // Starting address of write
		const std::vector<uint8_t> &data // Data to write to memory - program will write as many bytes as there are in data
		);


private:
	std::vector<uint8_t> mem;
};

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
#endif // !MEM_SIM_MEMORY_HPP