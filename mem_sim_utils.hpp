#ifndef MEM_SIM_UTILS_HPP
#define MEM_SIM_UTILS_HPP
#include <string>

std::string dec2bin(unsigned int n)
{
	std::string result;

	do result.push_back('0' + (n & 1));
	while (n >>= 1);

	reverse(result.begin(), result.end());
	return result;
}

#endif // !MEM_SIM_UTILS_HPP
