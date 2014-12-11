#ifndef MEM_SIM_UTILS_HPP
#define MEM_SIM_UTILS_HPP
#include <string>
#include <vector>
#include <stdint.h>
#include <stdint.h>

typedef struct _block_data_t
{
	unsigned long long int tag;

	std::vector<uint8_t> data;
}block_data_t;

std::string dec2bin(unsigned long long int n);

std::vector<uint8_t> words_to_bytes(const std::vector<unsigned long long int> words, unsigned long long int word_size);

std::vector<unsigned long long int> bytes_to_words(const std::vector<uint8_t> bytes, unsigned long long int word_size);

#endif // !MEM_SIM_UTILS_HPP
