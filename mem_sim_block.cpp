#include "mem_sim_block.hpp"
#include "mem_sim_word.hpp"
#include "mem_sim_exceptions.hpp"

block::block(const unsigned int iword_size, const unsigned int iblock_size) : block_size(iblock_size), meta({ 0, 0, 0 })
{
	words.assign(iblock_size, word(iword_size));
}