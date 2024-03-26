#pragma once

#include "utility.h"

template <class C>
struct Node {
	C entry;
	Node<C> *next;

	Node();
	Node(C, Node<C> *link_next = nullptr);
};

template <class C>
Node<C>::Node()
{
	next = nullptr;
}

template <class C>
Node<C>::Node (C data, Node<C> *link_next)
{
	entry = data;
	next = link_next;
}

template <class C>
class List {
public:
	List();
	int size() const;
	bool full() const;
	bool empty() const;
	void clear();
	void traverse(void (*visit)(C &));
	Error_code retrieve(int position, C &x) const;
	Error_code replace(int position, const C &x);
	Error_code remove(int position, C &x);
	Error_code insert(int position, const C &x);
	Error_code push_back(const C &x);

	~List();
	List(const List<C> &copy);
	void operator =(const List<C> &copy);
protected:
	int count;
	Node<C> *head;

	Node<C> *set_position(int position) const;
};

template <class C>
List<C>::List()
{
	count = 0;
	head = NULL;
}
 
template <class C>
void List<C>::clear()
{
	Node<C> *p, *q;

	for (p = head; p; p = q) {
		q = p->next;
		delete p;
	}
	count = 0;
	head = NULL;
}
 
template <class C>
int List<C>::size() const
{
	return count;
}
 
template <class C>
bool List<C>::empty() const
{
	return count <= 0;
}
 
template <class C>
bool List<C>::full() const
{
	return false;
}
 
template <class C>
void List<C>::traverse(void (*visit)(C &))
{
	Node<C> *q;

	for (q = head; q; q = q->next) {
		(*visit)(q->entry);
	}
}
 
template <class C>
Error_code List<C>::insert(int position, const C &x)
{
	if (position < 0 || position > count) {
		return utility_range_error;
	}
	Node<C> *new_node, *previous, *following;
	if (position > 0) {
		previous = set_position(position - 1);
		following = previous->next;
	}
	else {
		following = head;
	}
	new_node = new Node<C>(x, following);
	if (new_node == NULL) {
		return overflow;
	}
	if (position == 0) {
		head = new_node;
	}
	else {
	previous->next = new_node;
	}
	count++;
	return success;
}

template <class C>
Error_code List<C>::push_back(const C &x)
{
	Node<C> *current = head;
	while (current->next != nullptr) {
		current = current->next;
	}
	current->next = new Node<C>(x, nullptr);
	count++;
	return success;
}
 
template <class C>
Error_code List<C>::retrieve(int position, C &x) const
{
	Node<C> *current;
	if (position < 0 || position >= count) {
		return utility_range_error;
	}
	current = set_position(position);
	x = current->entry;
	return success;
}
 
template <class C>
Error_code List<C>::replace(int position, const C &x)
{
	Node<C> *current;
	if (position < 0 || position >= count) {
		return utility_range_error;
	}
	current = set_position(position);
	current->entry = x;
	return success;
}
 
template <class C>
Error_code List<C>::remove(int position, C &x)
{
	Node<C> *prior, *current;
	if (count == 0) {
		return fail;
	}
	if (position < 0 || position >= count) {
		return utility_range_error;
	}
	if (position > 0) {
		prior = set_position(position - 1);
		current = prior->next;
		prior->next = current->next;
	}
	else {
		current = head;
		head = head->next;
	}
	x = current->entry;
	delete current;
	count--;
	return success;
}
 
template <class C>
Node<C> *List<C>::set_position(int position) const
{
	Node<C> *q = head;
	for (int i = 0; i < position; i++) {
		q = q->next;
	}
	return q;
}
 
template <class C>
List<C>::~List()
{
	clear();
}
 
template <class C>
List<C>::List(const List<C> &copy)
{
	count = copy.count;
	Node<C> *new_node, *old_node = copy.head;

	if (old_node == NULL) {
		head = NULL;
	}
	else {
		new_node = head = new Node<C>(old_node->entry);
		while (old_node->next != NULL) {
			old_node = old_node->next;
			new_node->next = new Node<C>(old_node->entry);
			new_node = new_node->next;
		}
	}
}
 
template <class C>
void List<C>::operator =(const List<C> &copy)
{
	List new_copy(copy);
	clear();
	count = new_copy.count;
	head = new_copy.head;
	new_copy.count = 0;
	new_copy.head = NULL;
}
