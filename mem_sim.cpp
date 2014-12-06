#include <iostream>
#include <string>
#include "exceptions.hpp"
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

	bool finished = false;
	string cmd;
	while (!finished)
	{
		unsigned int address = 0;
		unsigned int data = 0;

		cin >> cmd;

		if (cmd.empty())
			finished = true;

		else if (cmd == "read-req")
		{
			
		}			
		else if (cmd == "write-req")
		{
			cin >> address >> data;
			
		}
			
		else if (cmd == "flush-req")
			;
		else if (cmd == "debug-req")
			;
		else 
			return Error_InvalidRequest; // For invalid input
	}

	return 0;
}