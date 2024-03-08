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

	Error_code append(T &n);
	Error_code serve();
	Error_code retrieve(T &n) const;
	Error_code serve_and_retrieve(T &n);

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
Error_code Queue<T>::append(T &n)
{
	if (tail == nullptr && head == nullptr) {
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
	return success;
}

template <typename T>
Error_code Queue<T>::serve()
{
	if (len == 0) {
		return underflow;
	}
	Queue_node<T> *old_head = head;
	head = head->next;
	old_head->next = nullptr;
	delete old_head;
	len--;
	return success;
}

template <typename T>
Error_code Queue<T>::retrieve(T &n) const
{
	if (len == 0) {
		return underflow;		
	}
	n = head->data;
	return success;
}

template <typename T>
Error_code Queue<T>::serve_and_retrieve(T &n)
{
	Error_code i = success;
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
