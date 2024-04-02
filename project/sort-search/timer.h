#pragma once

#include <time.h>

class Timer{
public:
	Timer();
	double elapsed_time();
	clock_t clock_cycles_elapsed();
	void reset();
private:
	clock_t start_time;
};
