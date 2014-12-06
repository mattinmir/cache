#include "mem_sim_memory.hpp"
#include "mem_sim_exceptions.hpp"
#include <stdint.h>

memory::memory(unsigned int addr_bits)
{
	mem.assign(1 << addr_bits, 0);
}