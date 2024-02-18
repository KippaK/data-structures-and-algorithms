#pragma once

#include <cstddef>

template <typename T>
class Linked_Stack_Node {
public:
	Linked_Stack_Node();
	Linked_Stack_Node(T &aData);
	Linked_Stack_Node(T &aData, Linked_Stack_Node<T>* aNext);
	~Linked_Stack_Node();

public:
	T data;
	Linked_Stack_Node<T>* next;
};

template <typename T>
Linked_Stack_Node<T>::Linked_Stack_Node()
{
	next = nullptr;
	data = NULL;
}

template <typename T>
Linked_Stack_Node<T>::Linked_Stack_Node(T &aData)
{
	next = nullptr;
	data = aData;
}

template <typename T>
Linked_Stack_Node<T>::Linked_Stack_Node(T &aData, Linked_Stack_Node<T>* aNext)
{
	next = aNext;
	data = aData;
}

template <typename T>
Linked_Stack_Node<T>::~Linked_Stack_Node() 
{
	if (next != nullptr) {
		delete next;
	}
}	
