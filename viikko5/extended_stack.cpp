#include "stack.h"

template <typename T>
Error_code Extended_Stack<T>::push(T item) {
   Error_code outcome = success;
   if (count >= maxstack)
      outcome = overflow;
   else
      entry[count++] = item;
   return outcome;
}

template <typename T>
Error_code Extended_Stack<T>::pop() {
   Error_code outcome = success;
   if (count == 0)
      outcome = underflow;
   else
      --count;
   return outcome;
}

template <typename T>
Error_code Extended_Stack<T>::top(T &item) const {
   Error_code outcome = success;
   if (count == 0)
      outcome = underflow;
   else
      item = entry[count - 1];
   return outcome;
}

template <typename T>
bool Extended_Stack<T>::empty() const {
   return (count == 0);
}

template <typename T>
bool Extended_Stack<T>::full() const {
   return (count == maxstack);
}

template <typename T>
void Extended_Stack<T>::clear() {
   count = 0;
}

template <typename T>
int Extended_Stack<T>::size() const {
   return count;
}

template <typename T>
Extended_Stack<T>::Extended_Stack() {
   count = 0;
}
