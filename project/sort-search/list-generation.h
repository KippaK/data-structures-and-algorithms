#pragma once

#include "random.h"
#include "list.h"

#include <cstddef>

template <class C>
Error_code sorted_two_n_minus_one(size_t n, List<C> &list)
{
	list.clear();
	Error_code status = success;
	for (size_t i = 1; i <= n; i++) {
		status = list.push_back(C(i * 2 - 1));
		if (status != success) {
			return status;
		}
	}
	return success;
}

template <class C>
Error_code sorted_two_n(size_t n, List<C> &list)
{
	list.clear();
	Error_code status = success;
	for (size_t i = 1; i <= n; i++) {
		status = list.push_back(C(n * 2));
		if (status != success) { return status; }
	}
	return success;
}

template <class C>
Error_code random_list(List<C> &list, size_t list_size, C max_val)
{
	list.clear();
	Error_code status = success;
	for (size_t i = 1; i <= list_size; i++) {
		status = list.push_back(C((rand() % max_val)));
		if (status != success) { return status; }
	}
	return success;
}
