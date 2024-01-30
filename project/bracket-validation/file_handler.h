#include "stack.h"
#include "file_error.h"

#include <vector>

#include <filesystem>
namespace fs = std::filesystem;



class File_handler {
public:
	File_handler();

private:
	Stack<char> stack;
	std::vector<File_error> errors;
	fs::path file_path;
	size_t col, row;
};
