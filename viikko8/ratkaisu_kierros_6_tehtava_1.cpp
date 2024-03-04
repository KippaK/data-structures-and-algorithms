// tehtava.cpp

#include "stack.h"

#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;

#define ENDLINE_CHAR 10

const size_t STACK_SIZE = 256;


Error_code item_stack_to_stack(
   Extended_Stack<char> &old_s, 
   Extended_Stack<char> &new_s)
{
   Error_code err = success;
   char ch;
   err = old_s.top(ch);
   err = new_s.push(ch);
   err = old_s.pop();
   return err;
}

Error_code print_stack(Extended_Stack<char> stack) {
   Error_code err = success;
   while (!stack.empty()) {
      char ch;
      err = stack.top(ch);
      cout << ch;
      err = stack.pop();
   }
   cout << endl;
   return err;
}

Error_code reverse_stack(Extended_Stack<char> &stack) {
   Error_code err = success;
   Extended_Stack<char> stack_cpy(stack);
   Extended_Stack<char> temp_stack(stack);
   stack.clear();
  
   while (!temp_stack.empty()) {
      err = item_stack_to_stack(temp_stack, stack);
   }


   return err;
}

Error_code user_input_to_stack(Extended_Stack<char> &stack) 
{
   char c;
   Error_code err = success;
   cout << "Enter a string: ";
   while(cin.get(c)) {
      if (c == ENDLINE_CHAR) { break; }
      err = stack.push(c);
   }
   return err;
}

bool is_palindrome(Extended_Stack<char> stack)
{
   Extended_Stack<char> stack_cpy(stack);
   Extended_Stack<char> stack_rev(stack);
   reverse_stack(stack_rev);
   
   while (!stack_cpy.empty()) {
      char c1, c2;
      stack_cpy.top(c1);
      stack_rev.top(c2);
      if (c1 != c2) { return false;}
      stack_cpy.pop();
      stack_rev.pop();
   }
   return true;
}

int main()
{
   Error_code err = success;
   Extended_Stack<char> s(STACK_SIZE);
   for (;;) {
      s.clear();
      err = user_input_to_stack(s);
      if (is_palindrome(s)) {
         cout << "Palindrome found" << endl;
      }
      err = print_stack(s);
      err = reverse_stack(s);
   }
   return 0;
}
#pragma once

#include "utility.h"
#include "linked_stack_node.h"
#include <cstddef>

template <typename T>
class Linked_Stack {
public:
	Linked_Stack();

	bool empty() const;
	void clear();
	size_t size() const;

	Error_code pop();
	Error_code top(T &item) const;
	Error_code pop_top(T &item);
	Error_code push(const T &item);

private:
	size_t count;
	Linked_Stack_Node<T> *head;
};

template <typename T>
Linked_Stack<T>::Linked_Stack()
{
	count = 0;
	head = nullptr;
}

template <typename T>
bool Linked_Stack<T>::empty() const
{
	return (count == 0);
}

template <typename T>
void Linked_Stack<T>::clear()
{
	delete head;
	head = nullptr;
	count = 0;
}

template <typename T>
size_t Linked_Stack<T>::size() const
{
	return count;
}

template <typename T>
Error_code Linked_Stack<T>::pop()
{
	if (count == 0) { return underflow; }
	Linked_Stack_Node<T> *old_head = head;
	head = head->next;
	old_head->next = nullptr;
	delete old_head;
	count--;
	return success;
}

template <typename T>
Error_code Linked_Stack<T>::top(T &item) const
{
	if (count == 0) { return underflow; }
	
	item = head->data;
	return success;
}

template <typename T>
Error_code Linked_Stack<T>::pop_top(T &item)
{
	if (count == 0) { return underflow; }

	item = head->data;
	pop();
	count--;
}

template <typename T>
Error_code Linked_Stack<T>::push(const T &item)
{
	if (count == 0) {
		head = new Linked_Stack_Node<T>(item);
		count++;
		return success;
	}
	Linked_Stack_Node<T> *new_head = new Linked_Stack_Node<T>(item, head);
	head = new_head;
	count++;
	return success;
}
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

