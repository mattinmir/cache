#include <iostream>
#include <string>
#include <stdint.h>
#include "mem_sim_exceptions.hpp"
#include "mem_sim_cache.hpp"
#include <cstdlib>
#include <cmath>

#define DEBUG_LEVEL 0

using namespace std;

int main(int argc, char* argv[])
{
	unsigned long long int address_bits = atoi(argv[1]); 
	unsigned long long int bytes_per_word = atoi(argv[2]);
	unsigned long long int words_per_block = atoi(argv[3]);
	unsigned long long int blocks_per_set = atoi(argv[4]);
	unsigned long long int sets_per_cache = atoi(argv[5]);
	unsigned long long int cycles_per_hit = atoi(argv[6]);
	unsigned long long int cycles_per_read_block = atoi(argv[7]);
	unsigned long long int cycles_per_write_block = atoi(argv[8]);

	cache c(address_bits, bytes_per_word, words_per_block, blocks_per_set, sets_per_cache, cycles_per_hit, cycles_per_read_block, cycles_per_write_block);

	unsigned long long int address;
	unsigned long long int time;
	string hitmiss;
	string data;
	string cmd;
	sim_error error = Success;
	bool finished = false;
	while (!finished)
	{
		address = 0;
		time = 0;
		data = "";
		hitmiss = "";

		cin >> cmd;

		if (cmd == "end")
			finished = true;

		else if (cmd == "read-req")
		{
			cin >> address;

			vector<unsigned long long int> data_vector(words_per_block);
			error = c.read(address, data_vector, time, hitmiss);
			unsigned long long int word_index = (address >> (unsigned long long int)log2(bytes_per_word)) % words_per_block;
			data = to_string(data_vector[word_index]);

			if (!error)
				cout << "read-ack " << address << " " << hitmiss << " " << time << " " << data << endl;
		}			
		else if (cmd == "write-req")
		{
			cin >> address >> data;
			vector<unsigned long long int> data_vector = { stoull(data, nullptr, 16) };
			error = c.write(address, data_vector, time, hitmiss);

			if (!error)
				cout << "write-ack " << address << " " << hitmiss << " " << time << endl;
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