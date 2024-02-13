// stack.h

#pragma once
#include "utility.h"

#include <cstring>

#define DEFAULT_STACK_SIZE 10

template <typename T>
class Stack {
public:
	Stack();
   Stack(size_t aStack_size);
	Stack(const Stack &aStack);
	~Stack();
	bool empty() const;
	Error_code pop();
	Error_code top(T &item) const;
	Error_code pop_top(T &item);
	Error_code push(const T &item);

	template <typename U>
	friend Error_code copy_stack_c(Stack<U> &dest, Stack<U> &source);

protected:
   int count;
   size_t stack_size;
   T *entry = nullptr;
};

template <typename T>
class Extended_Stack : public Stack<T> {
public:
   Extended_Stack();
   Extended_Stack(size_t aStack_size);
   Extended_Stack(const Extended_Stack &stack);
   ~Extended_Stack();
   void clear();
   bool full() const;
   int size() const;
};

// stack.cpp

template <typename T>
Error_code Stack<T>::push(const T &item) {
   Error_code outcome = success;
   if (count >= stack_size)
      outcome = overflow;
   else
      entry[count++] = item;
   return outcome;
}

template <typename T>
Error_code Stack<T>::pop() {
   Error_code outcome = success;
   if (count == 0)
      outcome = underflow;
   else
      --count;
   return outcome;
}

template <typename T>
Error_code Stack<T>::top(T &item) const {
   Error_code outcome = success;
   if (count == 0)
      outcome = underflow;
   else
      item = entry[count - 1];
   return outcome;
}

template <typename T>
Error_code Stack<T>::pop_top(T &item)
{
	Error_code outcome = success;
	if (count == 0) {
		outcome = underflow;
	}
	else {
		item = entry[count-1];
	}
	return outcome;
}

template <typename T>
bool Stack<T>::empty() const {
   return (count == 0);
}

template <typename T>
Stack<T>::Stack() {
   count = 0;
   stack_size = DEFAULT_STACK_SIZE;
   entry = new T[stack_size];
}

template <typename T>
Stack<T>::Stack(size_t aStack_size)
{
   count = 0;
   stack_size = aStack_size;
   entry = new T[stack_size];
}

template <typename T>
Stack<T>::Stack(const Stack &aStack)
{
   count = aStack.count;
   stack_size = aStack.stack_size;
   entry = new T[stack_size];
   memcpy(entry, aStack.entry, stack_size * sizeof(T));
}

template <typename T>
Stack<T>::~Stack()
{
   if (entry != nullptr) {
      delete[] entry;
      entry = nullptr;
   }
}
// extended_stack.cpp

template <typename T>
bool Extended_Stack<T>::full() const {
   return (Stack<T>::count == Stack<T>::stack_size);
}

template <typename T>
void Extended_Stack<T>::clear() {
   Stack<T>::count = 0;
}

template <typename T>
int Extended_Stack<T>::size() const {
   return Stack<T>::count;
}

template <typename T>
Extended_Stack<T>::Extended_Stack() : Stack<T>() 
{
}

template <typename T>
Extended_Stack<T>::Extended_Stack(size_t aStack_size) : Stack<T>(aStack_size) 
{
}

template <typename T>
Extended_Stack<T>::Extended_Stack(const Extended_Stack &stack) : Stack<T>(stack)
{
}

template <typename T>
Extended_Stack<T>::~Extended_Stack() {
   if (Stack<T>::entry != nullptr) {
      delete[] Stack<T>::entry;
      Stack<T>::entry = nullptr;
   }
}

