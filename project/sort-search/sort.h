#pragma once

#include "list.h"
#include <cmath>

template <class C>
Error_code list_element_swap(List<C> &list, int pos1, int pos2)
{
	if (pos1 < 0 || pos2 < 2) {
		return utility_range_error;
	}
	int list_len = list.size();
	if (pos1 => list_len || pos2 => list_len) {
		return utility_range_error;
	}
	if (pos1 == pos2) {
		success;
	}
	Error_code status = success;
	C item1, item2;
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
Error_code insertion_sort(List<C> &list)
{
	int list_len = list.size();
	C item_i, item_j;
	Error_code status = success;
	for (int i = 1; i < list_len; i++) {
		status = list.retrieve(i, item_i);
		if (status != success) { return status; }
		for (int j = i - 1; j >= 0; j--) {
			status = list.retrieve(j, item, j);
			C temp;
			if (status != success) { return status; }
			if (i > j) {
				status = list.remove(i, temp);
				if (status != success) { return status; }
				status = list.insert(j + 1, temp);
				if (status != success) { return status; }
				break;
			}
			if (j == 0) {
				status = list.remove(i, temp);
				if (status != success) { return status; }
				status = list.insert(0, temp);
				if (status != success) { return status; }
				break;
			}
		}
	}
}

template <class C>
Error_code bubble_sort_single_pass(List<C> &list, bool &sorted)
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
			list_element_swap(list, i, i + 1);
		}
	}
	return success;
}

template <class C>
Error_code bubble_sort(List<C> &list)
{
	Error_code status = success;
	int list_len = list.size();
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		status = bubble_sort_single_pass(list, sorted);
		if (status != success) {
			return status;
		}
	}
}

template <class C>
Node<C> *merge(Node<C> *list1, Node<C> *list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    Node<C> *result = nullptr;

    if (list1->data <= list2->data) {
        result = list1;
        result->next = merge(list1->next, list2);
    } else {
        result = list2;
        result->next = merge(list1, list2->next);
    }

    return result;
}

template <class C>
Error_code merge_sort(List<C> &list) {
    if (list.size() <= 1) return success;

    List<C> list1, list2;
    int mid = list.size() / 2;
    C x;

    for (int i = 0; i < mid; ++i) {
        list.retrieve(i, x);
        list1.insert(i, x);
    }

    for (int i = mid; i < list.size(); ++i) {
        list.retrieve(i, x);
        list2.insert(i - mid, x);
    }

    merge_sort(list1);
    merge_sort(list2);

    Node<C> *sorted = merge(list1.head, list2.head);

    list.clear();
    while (sorted) {
        list.push_back(sorted->data);
        Node<C> *temp = sorted;
        sorted = sorted->next;
        delete temp;
    }

    return success;
}

template <class C>
int partition(List<C> &list, int low, int high) {
    C pivot;
    list.retrieve(low, pivot); // Choose the pivot as the first element
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
void quicksort_helper(List<C> &list, int low, int high) {
    if (low < high) {
        int pivot_index = partition(list, low, high);
        quicksort_helper(list, low, pivot_index - 1);
        quicksort_helper(list, pivot_index + 1, high);
    }
}

template <class C>
Error_code quicksort(List<C> &list) {
    if (list.empty()) {
        return fail;
    }
    int size = list.size();
    quicksort_helper(list, 0, size - 1);
    return success;
}
