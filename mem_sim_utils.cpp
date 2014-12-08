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
	

	for (unsigned long long int i = 0; i < words.size(); i++)
	{
		for (unsigned long long int j = i * word_size; j < (i * word_size) + word_size; j++)
			bytes[j] = (words[i] >> (i * 8)) & (1 << 8);
	}
	
	return bytes;
}

vector<unsigned long long int> bytes_to_words(const vector<uint8_t> bytes, unsigned long long int word_size)
{
	vector<unsigned long long int> words(bytes.size() / word_size);

	for (unsigned long long int i = 0; i < words.size(); i++)
	{
		for (unsigned long long int j = i * word_size; j < (i * word_size) + word_size; j++)
			words[i] |= (unsigned long long int)bytes[j] << (i * 8);
	}
}