#pragma once

#include "random.h"
#include "list.h"

#include <cstddef>

template <typename T>
Error_code sorted_two_n_minus_one(size_t n, List<T> &list)
{
	list.clear();
	Error_code status = success;
	for (size_t i = 1; i <= n; i++) {
		status = list.push_back(T(n*2-1));
		if (status != success) {
			return status;
		}
	}
	return success;
}

template <typename T>
Error_code sorted_two_n(size_t n, List<T> &list)
{
	list.clear();
	Error_code status = success;
	for (size_t i = 1; i <= n; i++) {
		status = list.push_back(T(n*2));
		if (status != success) {
			return status;
		}
	}
	return success;
}
