#pragma once

#include "list.h"
#include "timer.h"
#include "sort.h"
#include "sort-perf-log.h"
#include "search.h"

#include <cmath>

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
void print_first_n_items(const List<C> &list, size_t n)
{
	Error_code status = success;
	C item;
	int list_len = std::min((int)n, (int)list.size());
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
	List<C> list,
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
clock_t sort_list_time(
	List<C> list,
	uint32_t &swaps,
	uint32_t &comparisons,
	Error_code (*func)(List<C> &, uint32_t&, uint32_t&))
{
	Error_code status = success;
	Timer timer;
	status = (*func)(list, swaps, comparisons);
	clock_t elapsed_time = timer.clock_cycles_elapsed();
	if (status != success) {
		return -1;
	}
	return elapsed_time;
}

template <class C>
void sort_list_time(
	List<C> list,
	uint32_t &swaps,
	uint32_t &comparisons,
	Error_code (*func)(List<C>&, uint32_t&, uint32_t&),
	clock_t &time)
{
	time = sort_list_time(list, swaps, comparisons, func);
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
