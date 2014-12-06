#include "mem_sim_set.hpp"
#include "mem_sim_block.hpp"
#include "mem_sim_exceptions.hpp"

set::set(const unsigned int iword_size, const unsigned int iblock_size, const unsigned int iset_size) : set_size(iset_size)
{
	blocks.assign(iset_size, block(iword_size, iblock_size));
}