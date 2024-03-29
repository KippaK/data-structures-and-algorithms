#pragma once

#include "stack.h"
#include "file_error.h"

#include <vector>
#include <string>
#include <fstream>

class File_handler {
private:
	char s_get_2nd_last();

public:
	File_handler();
	void open_file(const char* file_path);
	void close_file();

	void find_errors();

	std::string log_errors() const;

private:
	Stack<char> stack;
	std::vector<File_error> errors;
	std::fstream fs;
	size_t col, row;
};
