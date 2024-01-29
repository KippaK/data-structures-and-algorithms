#include "stack.h"

#include <string>
using std::string;

#include <filesystem>
namespace fs = std::filesystem;

#include <iostream>
using std::cout;
using std::endl;

typedef struct {
	fs::path i_file;
} Config;

uint64_t get_file_size(char *file_name)
{
	return reinterpret_cast<uint64_t>(fs::file_size(file_name));
}

void print_usage(char *exe_name)
{
	cout << "Invalid usage" << endl;
	cout << "Usage: " << exe_name << " <input_file> [options]" << endl;
}

// returns 0 if arguments are valid
// otherwise returns non-zero value
bool parse_arguments(Config &config, int argc, char** argv)
{
	if (argc < 2) {
		return false;
	}	
	if (argc > 3) {
		return false;
	}
	if (argc == 3 && argv[2][0] != '-') {
		return false;
	}
	
	return true;
}

void print_invalid_syntax(
	char* error, 
	uint row, 
	uint col, 
	char* line)
{
	
}

void ingore_comment()
{}

void ignore_block_comment()
{}

void ignore_string_content()
{}

void ignore_character()
{}

int main(int argc, char** argv)
{
	Config conf;
	if (!parse_arguments(conf, argc, argv)) {
		print_usage(argv[0]);
		return 1;
	}

	

}
