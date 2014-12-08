#include "cache.hpp"

class output
{
public:
	output(cache cache);

	void read(
		unsigned long long int set_index,
		bool hit,
		unsigned long long int time,
		unsigned long long int data
		);

	void write(
		unsigned long long int set_index,
		bool hit,
		unsigned long long int time
		);

	void flush(
		unsigned long long int time
		);

	void debug(
		unsigned long long int debug_level
		);

private:
	cache cache;
};