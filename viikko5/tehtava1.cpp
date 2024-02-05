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
