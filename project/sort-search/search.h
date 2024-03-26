#pragma once

#include <cmath>

template <class C>
Error_code sequential_search(const List<C> &list, const C &target, int &position)
{
	C item;
	position = -1;
	Error_code status;
	int list_len = list.size();
	for (int i = 0; i < list_len; i++) {
		status = list.retrieve(i, item);
		if (status != success) {
			return status;
		}
		if (item.data == target) {
			position = i;
			return success;
		}
	}
	return not_present;
}

template <class C>
Error_code binary_search(const List<C> &list, const C &target, int &position) {
    if (list.empty()) {
        return not_present;
    }
    int low = 0;
    int high = list.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        C mid_value;
        Error_code result = list.retrieve(mid, mid_value);
        if (result != success) {
            return result;
        }

        if (mid_value == target) {
            position = mid;
            return success;
        } else if (mid_value < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    position = -1;
    return not_present;
}
