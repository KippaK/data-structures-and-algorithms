// tehtava.cpp

#include "stack.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

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

Error_code reverse_stack(Extended_Stack<char> &stack) { 
   Error_code err = success;
   Extended_Stack<char> new_stack(stack.size());
   while (!stack.empty()) {
      err = item_stack_to_stack(stack, new_stack);
   }
   stack = new_stack;
   return err;
}

Error_code user_input_to_stack(Extended_Stack<char> &stack) 
{
   char c;
   Error_code err = success;
   while(cin.get(c)) {
      err = stack.push(c);
   }
   return err;
}

int main()
{
   Error_code err = success;
   Extended_Stack<char> s(STACK_SIZE);
   err = reverse_stack(s);
}
