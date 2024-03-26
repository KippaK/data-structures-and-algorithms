#pragma once

#include "list.h"
#include "timer.h"

template <class C>
double sorted_search_time(
	const List<C> sorted_list,
	const C &target,
	int &position,
	Error_code (*func)(const List<C>&, const C&, int&))
{
	Error_code status = success;
	Timer timer;
	status = func(sorted_list, target, position);
	double elapsed_time = timer.elapsed_time;
	if (status != success) {
		return -1;
	}
	return elapsed_time;
}
