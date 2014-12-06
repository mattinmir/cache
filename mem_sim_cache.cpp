#include "mem_sim_cache.hpp"
#include "mem_sim_set.hpp"
#include "mem_sim_exceptions.hpp"

cache::cache(
	const unsigned int imemory_size,
	const unsigned int iword_size,
	const unsigned int iblock_size,
	const unsigned int iset_size,
	const unsigned int icache_size,
	const unsigned int ihit_time,
	const unsigned int iread_time,
	const unsigned int iwrite_time
	) : cache_size(icache_size), mem(memory(imemory_size))
{
	sets.assign(iset_size, set(iword_size, iblock_size, iset_size));

}