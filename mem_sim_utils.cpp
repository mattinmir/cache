#include "mem_sim_utils.hpp"
#include <string>
#include <vector>
#include <stdint.h>


using namespace std;

string dec2bin(unsigned long long int n)
{
	string result;

	do result.push_back('0' + (n & 1));
	while (n >>= 1);

	reverse(result.begin(), result.end());
	return result;
}

vector<uint8_t> words_to_bytes(const vector<unsigned long long int> words, unsigned long long int word_size)
{
	vector<uint8_t> bytes(words.size() * word_size);

	// For each word in the vector
	for (unsigned long long int i = 0; i < words.size(); i++)
	{
		// For each byte we want to produce from the current word in the vector
		for (unsigned long long int j = i * word_size; j < (i * word_size) + word_size; j++)
			// Find the correct byte of the word by shifting right by 8 bits * that byte's position in the word and extract with a bitmask.
			// e.g. to get the 2nd byte (position 1) of the word, shift the word 1 byte to the right then AND with 0xFF to extract it
			bytes[j] = (uint8_t)(words[i] >> (8 * (word_size - 1 - (j % word_size))) & 0xFF); 
	}

	return bytes;
}

vector<unsigned long long int> bytes_to_words(const vector<uint8_t> bytes, unsigned long long int word_size)
{
	vector<unsigned long long int> words(bytes.size() / word_size);

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