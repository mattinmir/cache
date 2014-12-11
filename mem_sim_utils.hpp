#ifndef MEM_SIM_UTILS_HPP
#define MEM_SIM_UTILS_HPP

#include <string>
#include <vector>
#include <stdint.h>


typedef struct _block_data_t
{
	unsigned long long int tag;

	std::vector<uint8_t> data;
}block_data_t;

std::string dec2bin(unsigned long long int n);

std::vector<uint8_t> words_to_bytes(const std::vector<unsigned long long int> words, unsigned long long int word_size);

std::vector<unsigned long long int> bytes_to_words(const std::vector<uint8_t> bytes, unsigned long long int word_size);


std::vector<uint8_t> words_to_bytes(const std::vector<unsigned long long int> words, unsigned long long int word_size)
{
	std::vector<uint8_t> bytes(words.size() * word_size);

	// For each word in the std::vector
	for (unsigned long long int i = 0; i < words.size(); i++)
	{
		// For each byte we want to produce from the current word in the std::vector
		for (unsigned long long int j = i * word_size; j < (i * word_size) + word_size; j++)
			// Find the correct byte of the word by shifting right by 8 bits * that byte's position in the word and extract with a bitmask.
			// e.g. to get the 2nd byte (position 1) of the word, shift the word 1 byte to the right then AND with 0xFF to extract it
			bytes[j] = (uint8_t)(words[i] >> (8 * (j % word_size)) & 0xFF);
	}

	return bytes;
}

std::vector<unsigned long long int> bytes_to_words(const std::vector<uint8_t> bytes, unsigned long long int word_size)
{
	std::vector<unsigned long long int> words(bytes.size() / word_size);

	// For each word we want to produce from the bytes
	for (unsigned long long int i = 0; i < words.size(); i++)
	{
		// For each byte that will be in the current word
		for (unsigned long long int j = i * word_size; j < (i * word_size) + word_size; j++)
			// Shift the byte up by 8 bits * its position in the word and OR that with the word to add it on
			words[i] |= (unsigned long long int)bytes[j] << ((j % word_size) * 8);
	}

	return words;
}
#endif // !MEM_SIM_UTILS_HPP
