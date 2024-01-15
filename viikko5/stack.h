#pragma once
#include "../utility/utility.h"

#define DEFAULT_STACK_SIZE 10

template <typename T>
class Stack {
public:
   Stack();
   Stack(size_t aStack_size);
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
   void clear(); // Reset the stack to be empty.
   bool full() const; // If the stack is full, return true; else return false.
   int size() const; // Return the number of entries in the stack.
};
