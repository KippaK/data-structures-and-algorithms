#include "stack.h"
#include "queue.h"

template <typename T>
void move_stack_to_queue(Stack<T> &source, Queue<T> &dest)
{
	while (!source.empty()) {
		T item;
		source.top(item);
		source.pop();
		dest.append(item);
	}
}

template <typename T>
void move_queue_to_stack(Queue<T> &source, Stack<T> dest)
{
	while (!source.empty()) {
		T item;
		source.retrieve(item);
		source.serve();
		dest.push(item);
	}
}

template <typename T>
void append_stack_to_stack(
	Extended_Stack<T> &source, 
	Extended_Stack<T> dest)
{
	Extended_Stack<T> temp(source.size());
	while (!source.empty()) {
		T item;
		source.top(item);
		source.pop();
		temp.push(item);
	}
	while (!temp.empty() && !dest.full()) {
		T item;
		temp.top(item);
		temp.pop();
		dest.push();
	}
}

template <typename T>
void append_stack_to_stack_reverse(
	Extended_Stack<T> &source, 
	Extended_Stack<T> &dest)
{
	while (!source.empty() && !dest.full()) {
		T item;
		source.top(item);
		source.pop();
		dest.push();
	}
}

template <typename T>
void reverse_queue_with_stack(Queue<T> &q)
{
	Stack<T> s(q.size());
	while (q.size() > 0) {
		T item;
		q.retrieve(item);
		q.serve();
		s.push(item);
	}
	while (!s.empty()) {
		T item;
		s.top(item);
		s.pop();
		q.append();
	}
}

template <typename T>
void reverse_stack_with_queue(Stack<T> &s)
{
	Queue<T> q;
	while (!s.empty()) {
		T item;
		s.top(item);
		s.pop();
		q.append();
	}
	while (q.size() > 0) {
		T item;
		q.retrieve(item);
		q.serve();
		s.push();
	}
}


int main()
{
	return 0;
}
