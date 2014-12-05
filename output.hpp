#include "cache.hpp"

class output
{
public:
	output(cache cache);

	void read(
		unsigned int set_index,
		bool hit,
		unsigned int time,
		unsigned int data
		);

	void write(
		unsigned int set_index,
		bool hit,
		unsigned int time
		);

	void flush(
		unsigned int time
		);

	void debug(
		unsigned int debug_level
		);

private:
	cache cache;
};