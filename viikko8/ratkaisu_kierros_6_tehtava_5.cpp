#pragma once

#include "utility.h"
#include "linked_stack_node.h"
#include <cstddef>

template <typename T>
class Linked_Stack {
public:
	Linked_Stack();

	bool empty() const;
	void clear();
	size_t size() const;

	Error_code pop();
	Error_code top(T &item) const;
	Error_code pop_top(T &item);
	Error_code push(const T &item);

private:
	size_t count;
	Linked_Stack_Node<T> *head;
};

template <typename T>
Linked_Stack<T>::Linked_Stack()
{
	count = 0;
	head = nullptr;
}

template <typename T>
bool Linked_Stack<T>::empty() const
{
	return (count == 0);
}

template <typename T>
void Linked_Stack<T>::clear()
{
	delete head;
	head = nullptr;
	count = 0;
}

template <typename T>
size_t Linked_Stack<T>::size() const
{
	return count;
}

template <typename T>
Error_code Linked_Stack<T>::pop()
{
	if (count == 0) { return underflow; }
	Linked_Stack_Node<T> *old_head = head;
	head = head->next;
	old_head->next = nullptr;
	delete old_head;
	count--;
	return success;
}

template <typename T>
Error_code Linked_Stack<T>::top(T &item) const
{
	if (count == 0) { return underflow; }
	
	item = head->data;
	return success;
}

template <typename T>
Error_code Linked_Stack<T>::pop_top(T &item)
{
	if (count == 0) { return underflow; }

	item = head->data;
	pop();
	count--;
}

template <typename T>
Error_code Linked_Stack<T>::push(const T &item)
{
	if (count == 0) {
		head = new Linked_Stack_Node<T>(item);
		count++;
		return success;
	}
	Linked_Stack_Node<T> *new_head = new Linked_Stack_Node<T>(item, head);
	head = new_head;
	count++;
	return success;
}
