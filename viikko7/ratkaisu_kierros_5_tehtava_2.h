#pragma once

#include "queue_node.h"
#include "utility.h"

template<typename T>
class Queue{
public:
	Queue();
	~Queue();
	
	size_t size() const;
	bool empty() const;
	void clear();

	int append(T &n);
	int serve();
	int retrieve(T &n) const;
	int serve_and_retrieve(T &n);

private:
	size_t len;
	Queue_node<T> *head;
	Queue_node<T> *tail;
};

template <typename T>
size_t Queue<T>::size() const
{
	return len;
}

template <typename T>
bool Queue<T>::empty() const
{
	return (len == 0);
}

template <typename T>
void Queue<T>::clear()
{
	len = 0;
	delete head;
	head = nullptr;
	tail = nullptr;
}


template <typename T>
int Queue<T>::append(T &n)
{
	if (tail == nullptr) {
		tail = new Queue_node<T>(n);
		head = tail;
	}
	else {
		tail->next = new Queue_node<T>(n);
	}
	len++;
	if (tail->next != nullptr) {
		tail = tail->next;
	}
	return 0;
}

template <typename T>
int Queue<T>::serve()
{
	if (len == 0) {
		return 1;
	}
	Queue_node<T> *old_head = head;
	head = head->next;
	old_head->next = nullptr;
	delete old_head;
	len--;
	return 0;
}

template <typename T>
int Queue<T>::retrieve(T &n) const
{
	if (head->data == NULL) {
		return 1;		
	}
	n = head->data;
	return 0;
}

template <typename T>
int Queue<T>::serve_and_retrieve(T &n)
{
	int i = 0;
	i = retrieve(n);
	i += serve();
	return i;
}

template <typename T>
Queue<T>::Queue() 
{
	head = nullptr;
	tail = nullptr;
	len = 0;
}

template <typename T>
Queue<T>::~Queue() {
	if (head != nullptr) {
		delete head;
	}
}
