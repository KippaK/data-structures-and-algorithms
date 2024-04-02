#pragma once

#include "list.h"
#include "timer.h"
#include "sort.h"
#include "search.h"

template <class C>
void print_list(const List<C> &list)
{
	Error_code status = success;
	C item;
	int list_len = list.size();
	if (list_len < 1) { return; }
	status = list.retrieve(0, item);
	if (status != success) { return; }
	std::cout << item;
	for (int i = 1; i < list_len; i++) {
		status = list.retrieve(i, item);
		if (status != success) { return; }
		std::cout << ", " << item;
	}
	std::cout << std::endl;
}

template <class C>
clock_t sort_list_time(
	const List<C> list,
	Error_code (*func)(List<C> &))
{
	Error_code status = success;
	Timer timer;
	status = (*func)(list);
	clock_t elapsed_time = timer.clock_cycles_elapsed();
	if (status != success) {
		return -1;
	}
	return elapsed_time;
}

template <class C>
clock_t sorted_search_time(
	const List<C> sorted_list,
	const C &target,
	int &position,
	Error_code (*func)(const List<C>&, const C&, int&),
	Error_code &status)
{
	status = success;
	Timer timer;
	status = func(sorted_list, target, position);
	clock_t elapsed_time = timer.clock_cycles_elapsed();
	if (status == success || status == entry_found) {
		return elapsed_time;
	}
	return -1;
}
