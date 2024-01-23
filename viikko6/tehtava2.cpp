#include "stack.h"

template <typename T>
bool full(Extended_Stack<T> &s)
{
	return s.full();
}

template <typename T>
Error_code pop_top(Stack<T> &s, T &i)
{
	Error_code outcome;
	outcome = s.top(i);
	outcome = s.pop();
	return outcome;
}

template <typename T>
void clear(Stack<T> s)
{
	Error_code err = success;
	while (err == success) {
		err = s.pop();
	}
}

template <typename T>
int size(Extended_Stack<T> s)
{
	return s.size();
}

template <typename T>
void delete_all(Extended_Stack<T> s, T entry)
{
	Extended_Stack<T> temp(s.size());
	Error_code outcome = success;
	while (outcome == success) {
		T i;
		outcome = s.pop_top(s, i);
		temp.push(i);
	}
	outcome = success;
	while (!temp.empty()) {
		T i;
		outcome = temp.top(i);
		if (i != entry) {
			s.push(i);
		}
	}
}

int main()
{
	
}
