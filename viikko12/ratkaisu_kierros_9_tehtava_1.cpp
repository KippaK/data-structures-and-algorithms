#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "linked-list.h"
#include "utility.h"

template <typename T>
Error_code insert_first(T item, List_node<T> *list)
{
	int n = list->insert(item, 0);
	if (n == 0) { return success; }
	return fail;
}

template <typename T>
Error_code remove_first(T &item, List_node<T> *list)
{
	int n = list->pop(item, 0);
	if (n == 0) { return success; }
	return fail;
}

template <typename T>
Error_code insert_last(T item, List_node<T> *list)
{
	int n = list->push_back(item);
	if (n == 0) { return success; }
	return fail;
}

template <typename T>
Error_code remove_last(T &item, List_node<T> *list)
{
	int n = list->pop_back(item);
	if (n == 0) { return success; }
	return fail;
}

template <typename T>
Error_code median_list(T &item, List_node<T> *list)
{
	size_t list_size = list->size();
	size_t median = list_size / 2;
	int n = list->at(median, item);
	if (n == 0) { return success; }
	return fail;
}

template <typename T>
Error_code interchange(size_t pos1, size_t pos2, List_node<T> *list)
{
	T item1, item2;
	int n = list->at(pos1, item1);
	if (n != 0) { return fail; }
	n = list->pop(pos2, item2);
	if (n != 0) { return fail; }
	n = list->insert(pos2, item1);
	if (n != 0) { return fail; }
	n = list->pop(pos1, item1);
	if (n != 0) { return fail; }
	n = list->insert(pos1, item2);
	if (n != 0) { return fail; }
	return success;
}

template <typename T>
Error_code reverse_traverse_list(List_node<T> *list)
{
	size_t list_size = list->size();
	T item;
	int n;
	for (size_t i = list_size - 1; i >= 0; i--) {
		n = list->at(i, item);
		if (n != 0) { return fail; }
		cout << item << endl;
	}
	return success;
}

template <typename T>
Error_code copy(List_node<T> *dest, List_node<T> *source)
{
	T item;
	size_t source_size = source->size();
	int n;
	dest->clear();
	for (size_t i = 0; i < source_size; i++) {
		n = source->at(i, item);
		if (n != 0) { return fail; }
		n = dest->insert(item, i);
		if (n != 0) { return fail; }
	}
	return success;
}

template <typename T>
Error_code join(List_node<T> *list1, List_node<T> *list2)
{
	size_t j = list1->size();
	T item;
	int n;
	for (size_t i = 0; i < j; i++) {
		n = list1->at(i, item);
		if (n != 0) { return fail; }
		n = list2->push_back(item);
		if (n != 0) { return fail; }
	}
	return success;
}

template<typename T>
Error_code reverse(List_node<T> *&head) {
    if (head == nullptr || head->next == nullptr) {
        return success;
    }

    List_node<T> *prev = nullptr;
    List_node<T> *current = head;
    List_node<T> *next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
	return success;
}

template<typename T>
Error_code split(List_node<T> *&source, List_node<T> *&oddlist, List_node<T> *&evenlist) {
    if (source == nullptr) {
        return success;;
    }
    List_node<T> *source_current = source;
    List_node<T> *oddlist_current = nullptr;
    List_node<T> *evenlist_current = nullptr;
    bool is_odd = true;
    while (source_current != nullptr) {
        if (is_odd) {
            if (oddlist == nullptr) {
                oddlist = new List_node<T>(source_current->data);
                oddlist_current = oddlist;
            } else {
                oddlist_current->next = new List_node<T>(source_current->data);
                oddlist_current = oddlist_current->next;
            }
        } else {
            if (evenlist == nullptr) {
                evenlist = new List_node<T>(source_current->data);
                evenlist_current = evenlist;
            } else {
                evenlist_current->next = new List_node<T>(source_current->data);
                evenlist_current = evenlist_current->next;
            }
        }
        is_odd = !is_odd;
        source_current = source_current->next;
    }
    delete source;
    source = nullptr;
	return success;
}



int main() 
{
	return 0;	
}
