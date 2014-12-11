#ifndef MEM_SIM_BLOCK_HPP
#define MEM_SIM_BLOCK_HPP

#include "mem_sim_exceptions.hpp"
#include "mem_sim_word.hpp"
#include <vector>


class block
{
public:
	block(
		const unsigned long long int iword_size, // No. of bytes/word
		const unsigned long long int iblock_size // No. of words/block
		);

	sim_error read(
		std::vector<unsigned long long int> &data // Variable to store read output in
		);

	sim_error write(
		const std::vector<unsigned long long int> &data,
		unsigned long long int itag
		);


	bool is_valid() const;

	bool is_dirty() const;

	unsigned long long int get_tag() const;

	unsigned long long int get_age() const;

	void set_valid(bool new_valid);

	void set_dirty(bool new_dirty);

	void set_tag(unsigned long long int new_tag);


private:
	bool valid;
	bool dirty;
	unsigned long long int tag;
	unsigned long long int age;
	unsigned long long int block_size;
	std::vector<word> words; 

};

#endif // !MEM_SIM_BLOCK_HPP
