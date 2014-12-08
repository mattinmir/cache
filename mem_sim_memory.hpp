#ifndef MEM_SIM_MEMORY_HPP
#define MEM_SIM_MEMORY_HPP

#include <vector>
#include "mem_sim_exceptions.hpp"
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

	sim_error reset(); // Set all locations to 0

private:
	std::vector<uint8_t> mem;
};


#endif // !MEM_SIM_MEMORY_HPP