// stack.h

#pragma once
#include "../utility/utility.h"

#define DEFAULT_STACK_SIZE 10

template <typename T>
class Stack {
public:
   Stack();
   Stack(size_t aStack_size);
   Stack(Stack &aStack);
   ~Stack();
   bool empty() const;
   Error_code pop();
   Error_code top(T &item) const;
   Error_code push(const T &item);

protected:
   int count;
   size_t stack_size;
   T *entry = NULL;
};

template <typename T>
class Extended_Stack : public Stack<T> {
public:
   Extended_Stack();
   Extended_Stack(size_t aStack_size);
   Extended_Stack(Extended_Stack &stack);
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
Stack<T>::Stack(Stack &aStack)
{
   count = aStack.count;
   stack_size = aStack.stack_size;
   entry = new T[stack_size];
   memcpy(aStack.entry, entry, stack_size * sizeof(T));
}

template <typename T>
Stack<T>::~Stack()
{
   if (entry != NULL) {
      delete[] entry;
      entry = NULL;
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
Extended_Stack<T>::Extended_Stack(Extended_Stack &stack) : Stack<T>(stack)
{
}

template <typename T>
Extended_Stack<T>::~Extended_Stack() {
   if (Stack<T>::entry != NULL) {
      delete[] Stack<T>::entry;
      Stack<T>::entry = NULL;
   }
}

