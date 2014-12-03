#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <vector>
#include "exceptions.hpp"

class memory
{
public:
	memory(
		unsigned int addr_bits, // Size of the memory is 1 << addr_bits
		unsigned int word_length // Number of bits in each word i.e. in each element of vector
		);
	
	sim_error read(
		unsigned int address, // Starting byte address of read
		unsigned int &data, // Variable to store read output in
		unsigned int size // Number of bytes to read
		);

	sim_error write(
		unsigned int address, // Starting address of write
		unsigned int &data // Data to write to memory - program will write as many bytes as there are in data
		);

	sim_error reset(); // Set all locations to 0

private:
	std::vector<unsigned int> mem;
	unsigned int size;
};


#endif