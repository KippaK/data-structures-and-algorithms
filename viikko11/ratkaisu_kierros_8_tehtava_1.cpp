#include <iostream>
using namespace std;

#define NUMS_COUNT 6

unsigned int recurse(unsigned int n)
{
	if (n == 0) { return 0; }
	if (n % 2 == 0) { return recurse(n / 2); }
	return 1 + recurse(n - 1);
}

void print_recurse(unsigned int n)
{
	cout << "f(" << n << ") = " << recurse(n) << endl;
}

int main()
{
	unsigned int nums[NUMS_COUNT] = { 1, 2, 3, 99, 100, 128 };
	
	for (int i = 0; i < NUMS_COUNT; i++) {
		cout << char(int('a') + i) << ". ";
		print_recurse(nums[i]);
	}
	return 0;
}
