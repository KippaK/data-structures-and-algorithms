#include "stack.h"

template <typename T>
Error_code Stack<T>::push(const T &item) {
   Error_code outcome = success;
   if (count >= maxstack)
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
}

