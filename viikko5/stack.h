#pragma once
#include "../utility/utility.h"

const int maxstack = 10;

template <typename T>
class Stack {
public:
   Stack();
   bool empty() const;
   Error_code pop();
   Error_code top(T &item) const;
   Error_code push(const T &item);

private:
   int count;
   T entry[maxstack];
};

template <typename T>
class Extended_Stack {
public:
   Extended_Stack();
   Error_code pop();
   Error_code push(T item);
   Error_code top(T &item) const;
   bool empty() const;
   void clear(); // Reset the stack to be empty.
   bool full() const; // If the stack is full, return true; else return false.
   int size() const; // Return the number of entries in the stack.

private:
   int count;
   T entry[maxstack];
};
