#include "queue.h"

int main()
{
	return 0;
}
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
