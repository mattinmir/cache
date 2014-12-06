#ifndef MEM_SIM_EXCEPTIONS_HPP
#define MEM_SIM_EXCEPTIONS_HPP

typedef enum _sim_error
{
	Success = 0,

	//Errors with the input syntax
	Error_InvalidRequest = 0x100,
	Error_AddressOutOfRange = 0x101,
	Error_DataExceedsMemoryWidth = 0x102,
	Error_IteratorExceedsContainerSize = 0x103
	


}sim_error;

#endif // !MEM_SIM_EXCEPTIONS_HPP
