#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	bool finished = false;
	string cmd;
	while (!finished)
	{
		cin >> cmd;

		if (cmd.empty())
			finished = true;

		else if (cmd == "read-req")
			cout << "read" << endl;
		else if (cmd == "write-req")
			;
		else if (cmd == "flush-req")
			;
		else if (cmd == "debug-req")
			;
		else 
			return -1; // For invalid input
	}

	return 0;
}