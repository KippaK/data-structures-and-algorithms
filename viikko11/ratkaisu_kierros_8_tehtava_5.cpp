#include <iostream>

using namespace std;

int fibonacciR(int n, int &calls)
{
	calls++;
	if (n <= 0)  return 0;
	else if (n == 1)  return 1;
	else              return fibonacciR(n - 1, calls) + fibonacciR(n - 2, calls);
}


int fibonacciI(int n, int &calls)
{
	calls++;
	int last_but_one;
	int last_value; 
	int current;
	if (n <= 0) return 0;
	else if (n == 1) return 1;
	else {
		last_but_one = 0;
		last_value = 1;
		for (int i = 2; i <= n; i++) {
			current = last_but_one + last_value;
			last_but_one = last_value;
			last_value = current;
		}
	return current;
	}
}

void fibonacci_call(int n_min, int n_max, int (*fib_func)(int, int&))
{
    cout << "n\tFibonacci Calls\tClock Cycles\tCall Tree Depth" << endl;
	for (int n = n_min; n <= n_max; n++) {
		int calls = 0;
		clock_t start_time = clock();
		fib_func(n, calls);
		clock_t end_time = clock();
		int clock_cycles = int(end_time - start_time);
		cout << n << "\t" << calls << "\t\t" << clock_cycles << "\t\t";
		int call_tree_depth = n + 1;
		cout << call_tree_depth << endl;
	}
	return;
}

int main()
{
	cout << "ITERATIVE FIBONACCI" << endl;
	fibonacci_call(0, 10, &fibonacciI);
	cout << endl;
	cout << "RECURSIVE FOBANCCI" << endl;
	fibonacci_call(0, 10, &fibonacciR);

    return 0;
}
