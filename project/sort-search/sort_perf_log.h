#pragma once

#include "list.h"
#include <cmath>

template <class C>
static Error_code list_element_swap(List<C> &list, int pos1, int pos2, unsigned long &swaps, unsigned long &comparisons)
{
	if (pos1 < 0 || pos2 < 2) {
		return utility_range_error;
	}
	int list_len = list.size();
	if (pos1 >= list_len || pos2 >= list_len) {
		return utility_range_error;
	}
	if (pos1 == pos2) {
		success;
	}
	Error_code status = success;
	C item1, item2;
	swaps++;
	status = list.retrieve(pos1, item1);
	if (status != success) { return status; }
	status = list.retrieve(pos2, item2);
	if (status != success) { return status; }
	status = list.replace(pos1, item2);
	if (status != success) { return status; }
	status = list.replace(pos2, item1);
	return status;
}

template <class C>
Error_code insertion_sort(List<C> &list, unsigned long &swaps, unsigned long &comparisons)
{
	swaps = 0;
	comparisons = 0;

    int list_len = list.size();
    C item_i;
    Error_code status = success;
    for (int i = 1; i < list_len; i++) {
        status = list.retrieve(i, item_i);
        if (status != success) { return status; }
        int j = i - 1;
        while (j >= 0) {
            C item_j;
            status = list.retrieve(j, item_j);
            if (status != success) { return status; }
			comparisons++;
            if (item_i < item_j) {
                j--;
            } else {
                break;
            }
        }
		swaps++;
        status = list.remove(i, item_i);
        if (status != success) { return status; }
        status = list.insert(j + 1, item_i);
        if (status != success) { return status; }
    }
    return status;
}

template <class C>
void insertion_sort(List<C> &list, unsigned long &swaps, unsigned long &comparisons, Error_code &status)
{
	status = insertion_sort(list, swaps, comparisons);
}


template <class C>
static Error_code bubble_sort_single_pass(List<C> &list, bool &sorted, unsigned long &swaps, unsigned long &comparisons)
{
	Error_code status = success;
	C current, next;
	for (int i = 0; i < list.size() - 1; i++) {
		status = list.retrieve(i, current);
		if (status != success) { return status; }
		status = list.retrieve(i + 1, next);
		if (status != success) { return status; }
		comparisons++;
		if (current > next) {
			sorted = false;
			list_element_swap(list, i, i + 1, swaps, comparisons);
		}
	}
	return success;
}

template <class C>
Error_code bubble_sort(List<C> &list, unsigned long &swaps, unsigned long &comparisons)
{
	swaps = 0;
	comparisons = 0;
	Error_code status = success;
	int list_len = list.size();
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		status = bubble_sort_single_pass(list, sorted, swaps, comparisons);
		if (status != success) {
			return status;
		}
	}
}


template <class C>
void bubble_sort(List<C> &list, unsigned long &swaps, unsigned long &comparisons, Error_code &status)
{
	status = bubble_sort(list, swaps, comparisons);
}

static template <class C>
int partition(List<C> &list, int low, int high, unsigned long &swaps, unsigned long &comparisons) {
    C pivot;
    list.retrieve(low, pivot);
    int left = low + 1;
    int right = high;
    
    while (left <= right) {
        C left_item, right_item;
        list.retrieve(left, left_item);
        list.retrieve(right, right_item);
        if (left_item <= pivot && comparisons++) {
            left++;
        } else if (right_item > pivot && comparisons++) {
            right--;
        } else {
			swaps++;
            list.replace(left, right_item);
            list.replace(right, left_item);
            left++;
            right--;
        }
    }
	swaps++;
    list.replace(low, list.set_position(right)->data);
    list.replace(right, pivot);

    return right;
}

template <class C>
static void quicksort_helper(List<C> &list, int low, int high, unsigned long &swaps, unsigned long &comparisons) {
	comparisons++;
    if (low < high) {
        int pivot_index = partition(list, low, high, swaps, comparisons);
        quicksort_helper(list, low, pivot_index - 1, swaps, comparisons);
        quicksort_helper(list, pivot_index + 1, high, swaps, comparisons);
    }
}

template <class C>
Error_code quicksort(List<C> &list, unsigned long &swaps, unsigned long &comparisons)
{
	swaps = 0;
	comparisons = 0;
	if (list.empty()) {
        return fail;
    }
    int size = list.size();
    quicksort_helper(list, 0, size - 1, swaps, comparisons);
    return success;
}

template <class C>
void quicksort(List<C> &list, unsigned long &swaps, unsigned long &comparisons, Error_code &status)
{
	status = quicksort(list, swaps, comparisons);
}

template <class C>
static void heapify(List<C> &list, int n, int i, unsigned long &swaps, unsigned long &comparisons)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

	comparisons++;
    if (left < n && list.retrieve(left)->data > list.retrieve(largest)->data) {
        largest = left;
	}
	comparisons++;
    if (right < n && list.retrieve(right)->data > list.retrieve(largest)->data) {
        largest = right;
	}
	comparisons++;
    if (largest != i) {
        C temp;
		swaps++;
        list.retrieve(i, temp);
        list.replace(i, list.retrieve(largest)->data);
        list.replace(largest, temp);

        heapify(list, n, largest, swaps, comparisons);
    }
}

template <class C>
Error_code heapsort(List<C> &list, unsigned long &swaps, unsigned long &comparisons)
{
    int n = list.size();
	swaps = 0;
	comparisons = 0;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(list, n, i, swaps, comparisons);

    for (int i = n - 1; i > 0; i--) {
        C temp;
		swaps++;
        list.retrieve(0, temp);
        list.replace(0, list.retrieve(i)->data);
        list.replace(i, temp);

        heapify(list, i, 0, swaps, comparisons);
    }

    return success;
}

template <class C>
void heapsort(List<C> &list, unsigned long &swaps, unsigned long &comparisons, Error_code &status)
{
	status = heapsort(list, swaps, comparisons);
}
