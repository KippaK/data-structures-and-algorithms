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
