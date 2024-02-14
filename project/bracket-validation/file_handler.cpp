#include "file_handler.h"

#include <chrono>
#include <sstream>
#include <iomanip>


char File_handler::s_get_second_last()
{
	char top, ret;
	stack.top(top);
	stack.pop();
	stack.top(ret);
	stack.push(top);
	return ret;
}

void File_handler::find_errors()
{
		
}

std::string File_handler::log_errors() const
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	std::stringstream datetime;
	datetime << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	std::string log_file_name = "log_" + datetime.str() + ".log";
	std::fstream log_file(log_file_name, std::fstream::out); 
	

	return log_file_name;
}

File_handler::File_handler()
{
	row = 0;
	col = 0;
}

void File_handler::open_file(const char* file_path)
{
	fs.open(file_path);
}

void File_handler::close_file()
{
	fs.close();
}

