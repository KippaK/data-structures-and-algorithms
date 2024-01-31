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
	head = nullptr;
}


template <typename T>
int Queue<T>::append(T &n)
{
	tail->next = new Queue_node(n);
	if (tail->next == nullptr) {
		return 1;
	}
	len++;
	tail = tail->next;
	return 0;
}

template <typename T>
int Queue<T>::serve()
{
	if (len == 0) {
		return 1;
	}
	T *old_head = head;
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
	i = serve();
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
#pragma once

// Tää on turhinta paskaa mitä oon ikinä nähny
// Kirjan kirjottaja unohtuna c++ standardin
// jossa funktio/metodi palauttaa 0 jos se
// suoritetaan onnistuneesti, muuten joku muu arvo

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <time.h>
using namespace std;

enum Error_code {
	success, fail, utility_range_error, underflow, overflow, fatal,
	not_present, duplicate_error, entry_inserted, entry_found,
	internal_error
};

bool user_says_yes();
#include <iostream>
using namespace std;

bool user_says_yes()
{
	int c;
	bool initial_response = true;

	do {  //  Loop until an appropriate input is received.
		if (initial_response)
			cout << " (y,n)? " << flush;

		else
			cout << "Respond with either y or n: " << flush;

		do { //  Ignore white space.
			c = cin.get();
		} while (c == '\n' || c == ' ' || c == '\t');
		initial_response = false;
	} while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
	return (c == 'y' || c == 'Y');
}
