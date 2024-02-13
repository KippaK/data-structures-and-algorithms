#pragma once

#include "utility.h"
#include <cstddef>

template <typename T>
class Linked_Stack {
public:
	Linked_Stack();
	Linked_Stack(size_t aStack_size);
	Linked_Stack(const Linked_Stack &aStack);
	~Linked_Stack();

	bool empty() const;
	Error_code pop();
	Error_code top(T &item) const;
	Error_code pop_top(T &item);
	Error_code push(const T &item);

protected:
	int count;
	size_t stack_size;
	T *ent
};
