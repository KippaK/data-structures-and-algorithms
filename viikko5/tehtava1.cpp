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

Error_code move_stack_to_stack(
   Extended_Stack<char> &old_s,
   Extended_Stack<char> &new_s)
{
   Error_code err = success;
   while (!old_s.empty()) {
      err = item_stack_to_stack(old_s, new_s);
   }
   return err;
}


Error_code reverse_stack_print(Extended_Stack<char> &stack) {
   Error_code err = success;
   
   Extended_Stack<char> temp_stack_1(stack);
   Extended_Stack<char> temp_stack_2(stack);
   temp_stack_1.clear();
   temp_stack_2.clear();
   
   err = move_stack_to_stack(stack, temp_stack_1);
   err = move_stack_to_stack(temp_stack_1, temp_stack_2);
   err = move_stack_to_stack(temp_stack_2, stack);
   
   return err;
}

Error_code reverse_stack(Extended_Stack<char> &stack) { 
   Error_code err = success;
   Extended_Stack<char> new_stack(stack);
   new_stack.clear();
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
   cout << "Enter a string: ";
   while(cin.get(c)) {
      if (c == ENDLINE_CHAR) { break; }
      err = stack.push(c);
      cout << "pushed to stack: " << (int)c << endl;
   }
   return err;
}

Error_code is_palindrome(Extended_Stack<char> &stack)
{
   Error_code err = success;
   
   Extended_Stack<char> stack_cpy(stack);
   Extended_Stack<char> stack_rev(stack);


   return err;
}

int main()
{
   Error_code err = success;
   Extended_Stack<char> s(STACK_SIZE);
   for (;;) {
      err = user_input_to_stack(s);
      err = reverse_stack_print(s);
   }
   return 0;
}
