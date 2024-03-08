#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

unsigned int gcd_a(unsigned int x, unsigned int y) 
{
	for (unsigned int i = min(x, y); i > 1; i--) {
		if (x % i == 0 && y % i == 0) {
			return i;
		}
	}
	return 1;
}

unsigned int gcd_b(unsigned int x, unsigned int y) 
{
	if (y == 0) { return x; }
	return gcd_b(y, x%y);
}

unsigned int gcd_c(unsigned int x, unsigned int y)
{
	unsigned int tmp;
	while (y != 0) {
		tmp = y;
		y = x % y;
		x = tmp;
	}
	return x;
}

unsigned int gcd(
	unsigned int x, 
	unsigned int y, 
	unsigned int (*gcd_fn)(unsigned int, unsigned int))
{
	return gcd_fn(x, y);	
}

int main()
{
	vector<unsigned int (*)(unsigned int, unsigned int)> gcd_fn = {
		gcd_a,
		gcd_b,
		gcd_c
	};
	vector<vector<unsigned int>> nums = {
		{ 8, 12 },
		{ 9, 18 },
		{ 16, 25 }
	};
	for (int i = 0; i < gcd_fn.size(); i++) {
		cout << char(int('a') + i) << ')' << endl;
		for (int j = 0; j < nums.size(); j++) {
			cout	<< "GCD of " 
					<< nums[j][0] 
					<< " and " 
					<< nums[j][1] 
					<< " is " 
					<< gcd(nums[j][0], nums[j][1], gcd_fn[i])
					<< endl;
		}
		cout << endl;
	}
}
/*
gcd_a Implementation:
Advantages:

    Simplicity: 
		The algorithm is straightforward and easy to understand.
    
	No Recursion Overhead: 
		Unlike the recursive approach, there is no risk of stack overflow for large inputs.

Disadvantages:

    Inefficiency: 
		The algorithm has a time complexity of O(min(x, y)), which can be inefficient for 
		large inputs. It iterates through all possible divisors, which is unnecessary.

    Not Optimal: 
		This implementation may not be optimal in terms of performance 
		compared to more efficient algorithms for calculating the GCD.

gcd_b Implementation:
Advantages:

    Recursion: 
		It uses a concise recursive approach that directly 
		reflects the mathematical definition of the GCD.

Disadvantages:

    Recursion Overhead: 
		The recursive approach may lead to a stack 
		overflow for large inputs due to the function call stack.
    Slower for Some Cases: 
		Recursive calls may have more overhead compared to the iterative approach.

gcd_c Implementation:
Advantages:

    Iterative: 
		It uses an iterative approach, avoiding the 
		recursion overhead and potential stack overflow issues.
    Efficiency: 
		This implementation has better efficiency 
		in terms of time and space complexity compared to gcd_a.

Disadvantages:

    Complexity: 
		While it's more efficient than gcd_a, it might be a bit less 
		intuitive to understand due to the loop structure.

*/
