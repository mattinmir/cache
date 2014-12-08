#ifndef MEM_SIM_BLOCK_HPP
#define MEM_SIM_BLOCK_HPP

#include "mem_sim_exceptions.hpp"
#include <vector>
#include "mem_sim_word.hpp"



class block
{
public:
	block(
		const unsigned long long int iword_size, // No. of bytes/word
		const unsigned long long int iblock_size // No. of words/block
		);

	sim_error read(
		std::vector<unsigned long long int> &data // Variable to store read output in
		) const;

	sim_error write(
		const std::vector<unsigned long long int> &data // Data to write to memory - program will write as many words as there are in data
		);

	sim_error reset(); // Set all locations to 0

	bool is_valid() const;

	bool is_dirty() const;

	unsigned long long int get_tag() const;

	unsigned long long int get_age() const;


private:
	bool valid;
	bool dirty;
	unsigned long long int tag;
	unsigned long long int age;
	unsigned long long int block_size;
	std::vector<word> words; 

};

#endif // !MEM_SIM_BLOCK_HPP
