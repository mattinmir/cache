#include <iostream>
#include <string>
#include <stdint.h>
#include "mem_sim_exceptions.hpp"
#include "mem_sim_cache.hpp"

#define DEBUG_LEVEL 0

using namespace std;

int main(int argc, char* argv[])
{
	unsigned int address_bits = *argv[1] - '0'; // - '0' to get the actual digit rather than the ASCII representation
	unsigned int bytes_per_word = *argv[2] - '0';
	unsigned int words_per_block = *argv[3] - '0';
	unsigned int blocks_per_set = *argv[4] - '0';
	unsigned int sets_per_cache = *argv[5] - '0';
	unsigned int cycles_per_hit = *argv[6] - '0';
	unsigned int cycles_per_read_block = *argv[7] - '0';
	unsigned int cycles_per_write_block = *argv[8] - '0';

	//cache c(address_bits, bytes_per_word, words_per_block, blocks_per_set, sets_per_cache, cycles_per_hit, cycles_per_read_block, cycles_per_write_block);

	unsigned int address;
	unsigned int data;
	string cmd;
	sim_error error = Success;
	bool finished = false;
	while (!finished)
	{
		address = 0;
		data = 0;
		cin >> cmd;

		if (cmd.empty())
			finished = true;

		else if (cmd == "read-req")
		{
			cin >> address;
			//error = c.read(address, data, bytes_per_word);
		}			
		else if (cmd == "write-req")
		{
			cin >> address >> data;
			//error = c.write(address, data);
		}
		else if (cmd == "flush-req")
			;
			//c.flush();

		else if (cmd == "debug-req")
			;
			//c.debug(DEBUG_LEVEL);

		else 
			return Error_InvalidRequest; // For invalid input

		if (error)
			return error;
	}

	return 0;
}