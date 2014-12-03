#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

typedef enum _sim_error
{
	Success = 0,

	//Errors with the input syntax
	Error_InvalidRequest = 0x100,
	Error_AddressOutOfRange = 0x101,
	Error_DataExceedsMemoryWidth = 0x102
	


}sim_error;

#endif // !EXCEPTIONS_HPP
