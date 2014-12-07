#ifndef MEM_SIM_EXCEPTIONS_HPP
#define MEM_SIM_EXCEPTIONS_HPP

typedef enum _sim_error
{
	Success = 0,

	Error_InvalidRequest = 0x100,
	Error_AddressOutOfRange = 0x101,
	Error_DataExceedsMemoryWidth = 0x102,
	Error_IndexExceedsContainerSize = 0x103,
	Error_InvalidCacheParameters = 0x104,
	
	CacheMiss = 0x200

}sim_error;

#endif // !MEM_SIM_EXCEPTIONS_HPP
