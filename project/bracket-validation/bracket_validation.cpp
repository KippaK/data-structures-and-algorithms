#include "file_handler.h"

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

void print_usage(char *exe_name)
{
	cout << "Invalid usage" << endl;
	cout << "Usage: " << exe_name << " <input_file> [options]" << endl;
}

int main(int argc, char** argv)
{
	File_handler f;
	f.open_file("queue.txt");

	return 0;
}
