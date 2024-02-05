// stack.h

#pragma once
#include "../utility/utility.h"

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
   void clear(); // Reset the stack to be empty.
   bool full() const; // If the stack is full, return true; else return false.
   int size() const; // Return the number of entries in the stack.
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

#include "stack.h"

#include <chrono>
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

#include <iostream>
using std::cout;
using std::endl;

#include <string.h>

template <typename T>
Error_code copy_stack_a(Stack<T> &dest, Stack<T> &source)
{
	dest = source;
	return success;
}

template <typename T>
Error_code copy_stack_b(Extended_Stack<T> &dest, Extended_Stack<T> &source)
{
	Error_code outcome = success;
	Extended_Stack<T> temp(source.size());
	for (;;) {
		if (source.empty()) {
			break;
		}
		T item;
		outcome = source.top(item);
		outcome = source.pop();
		outcome = temp.push(item);
	}
	for (;;) {
		if (temp.empty()) {
			break;
		}
		if (dest.full()) {
			outcome = overflow;
			break;
		}
		T item;
		outcome = temp.top(item);
		outcome = temp.pop();
		outcome = dest.push(item);
	}
	return outcome;
}

template <typename T>
Error_code copy_stack_c(Stack<T> &dest, Stack<T> &source)
{
	if (dest.entry != nullptr) {
		delete dest.entry;
		dest.entry = nullptr;
	}
	dest.entry = new T[source.stack_size];
	memcpy(
		dest.entry, 
		source.entry, 
		source.stack_size * sizeof(T)
	);
	return success;
}

template <typename T>
void measure_execution_time(
	Error_code (*cpy_func)(Stack<T> &, Stack<T> &), 
	Stack<T> &dest,
	Stack<T> &source)
{
	auto start_time = std::chrono::high_resolution_clock::now();
	Error_code result = cpy_func(dest, source);
	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(end_time - start_time);

	if (result == success) {
		cout << "Execution time: " << duration.count() << " nanoseconds" << endl;
	}
	else {
		cout << "Error is cpy_func" << endl;
	}
}

template <typename T>
void measure_execution_time(
	Error_code (*cpy_func)(Extended_Stack<T> &, Extended_Stack<T> &), 
	Extended_Stack<T> &dest,
	Extended_Stack<T> &source)
{
	auto start_time = std::chrono::high_resolution_clock::now();
	Error_code result = cpy_func(dest, source);
	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(end_time - start_time);

	if (result == success) {
		cout << "Execution time: " << duration.count() << " nanoseconds" << endl;
	}
	else {
		cout << "Error is cpy_func" << endl;
	}
}

int main()
{
	Extended_Stack<int> s1, s2;
	for (int i = 0; i < 10; i++) {
		s1.push(i);
	}
	cout << "Method A ";
	measure_execution_time(copy_stack_a, s2, s1);
	s2.clear();
	cout << "Method B ";
	measure_execution_time(copy_stack_b, s2, s1);
	s2.clear();
	cout << "Method C ";
	measure_execution_time(copy_stack_c, s2, s1);

	cout << "Simply using an assignment statement causes double free" << endl;
	cout << "Meaning method A is not a valid solution" << endl;
	return 0;
}
