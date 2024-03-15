#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "linked-list.h"
#include "utility.h"

template <typename T>
Error_code insert_first(T item, List_node<T> *list)
{
	int n = list->insert(item, 0);
	if (n == 0) { return success; }
	return fail;
}



int main() 
{
	return 0;	
}
