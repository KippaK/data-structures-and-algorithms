#pragma once

#include "list.h"
#include <cmath>

template <class C>
Error_code insertion_sort(List<C> &list)
{
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
            if (item_i < item_j) {
                j--;
            } else {
                break;
            }
        }
        status = list.remove(i, item_i);
        if (status != success) { return status; }
        status = list.insert(j + 1, item_i);
        if (status != success) { return status; }
    }
    return status;
}

template <class C>
void insertion_sort(List<C> &list, Error_code &status)
{
	status = insertion_sort(list);
}

template <class C>
static Error_code bubble_sort_single_pass(List<C> &list, bool &sorted)
{
	Error_code status = success;
	C current, next;
	for (int i = 0; i < list.size() - 1; i++) {
		status = list.retrieve(i, current);
		if (status != success) { return status; }
		status = list.retrieve(i + 1, next);
		if (status != success) { return status; }
		if (current > next) {
			sorted = false;
			list.replace(i, next);
			list.replace(i + 1, current);
		}
	}
	return success;
}

template <class C>
Error_code bubble_sort(List<C> &list)
{
	Error_code status = success;
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		status = bubble_sort_single_pass(list, sorted);
		if (status != success) {
			return status;
		}
	}
	return success;
}

template <class C>
void bubble_sort(List<C> &list, Error_code &status)
{
	status = bubble_sort(list);
}

template <class C>
static int partition(List<C> &list, int low, int high) {
    C pivot;
    list.retrieve(low, pivot);
    int left = low + 1;
    int right = high;
    
    while (left <= right) {
        C left_item, right_item;
        list.retrieve(left, left_item);
        list.retrieve(right, right_item);
        if (left_item <= pivot) {
            left++;
        } else if (right_item > pivot) {
            right--;
        } else {
            list.replace(left, right_item);
            list.replace(right, left_item);
            left++;
            right--;
        }
    }
    list.replace(low, list.set_position(right)->data);
    list.replace(right, pivot);

    return right;
}

template <class C>
static void quicksort_helper(List<C> &list, int low, int high) {
    if (low < high) {
        int pivot_index = partition(list, low, high);
        quicksort_helper(list, low, pivot_index - 1);
        quicksort_helper(list, pivot_index + 1, high);
    }
}

template <class C>
Error_code quicksort(List<C> &list)
{
	if (list.empty()) {
        return fail;
    }
    int size = list.size();
    quicksort_helper(list, 0, size - 1);
    return success;
}

template <class C>
void quicksort(List<C> &list, Error_code &status)
{
	status = quicksort(list);
}

template <class C>
static void heapify(List<C> &list, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && list.retrieve(left)->data > list.retrieve(largest)->data) {
        largest = left;
	}
    if (right < n && list.retrieve(right)->data > list.retrieve(largest)->data) {
        largest = right;
	}
    if (largest != i) {
        C temp;
        list.retrieve(i, temp);
        list.replace(i, list.retrieve(largest)->data);
        list.replace(largest, temp);

        heapify(list, n, largest);
    }
}

template <class C>
Error_code heapsort(List<C> &list)
{
    int n = list.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(list, n, i);

    for (int i = n - 1; i > 0; i--) {
        C temp;
        list.retrieve(0, temp);
        list.replace(0, list.retrieve(i)->data);
        list.replace(i, temp);

        heapify(list, i, 0);
    }
    return success;
}

template <class C>
void heapsort(List<C> &list, Error_code &status)
{
	status = heapsort(list);
}
