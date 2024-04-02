#include "timer.h"

Timer::Timer()
{
	start_time = clock();
}
 
double Timer::elapsed_time()
{
	clock_t end_time = clock();
	return ((double) (end_time - start_time)) / ((double) CLOCKS_PER_SEC);
}

clock_t Timer::clock_cycles_elapsed()
{
	clock_t end_time = clock();
	return end_time - start_time;
}
 
void Timer::reset()
{
	start_time = clock();
}
