#pragma once

#include <cstddef>

template <typename T>
class Queue_node {
public:
	Queue_node();
	Queue_node(T &aData);
	~Queue_node();

public:
	T data;
	Queue_node* next;
};

template <typename T>
Queue_node<T>::Queue_node()
{
	next = nullptr;
	data = NULL;
}

template <typename T>
Queue_node<T>::Queue_node(T &aData)
{
	next = nullptr;
	data = aData;
}

template <typename T>
Queue_node<T>::~Queue_node() 
{
	if (next != nullptr) {
		delete next;
	}
}	
