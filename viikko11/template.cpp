#include <iostream>
#include <vector>

using namespace std;

unsigned int recurse_e1(unsigned int n)
{
	if (n == 0) { return 0; }
	if (n % 2 == 0) { return recurse_e1(n / 2); }
	return 1 + recurse_e1(n - 1);
}

unsigned int recurse_e2(unsigned int n)
{
	if (n < 2) { return n; }
	if (n % 2 == 0) { return recurse_e2(n / 2); }
	return recurse_e2((n + 1) / 2) + recurse_e2((n - 1) / 2);
}

int main()
{
	vector<unsigned int (*)(unsigned int)> recurse = {
		recurse_e1,
		recurse_e2
	};
	vector<vector<unsigned int>> nums = {
		{ 1, 2, 3, 99, 100, 128 },
		{ 1, 2, 3, 4, 5, 6 }
	};
	
	for (int i = 0; i < recurse.size(); i++) {
		cout << 'E' << i+1 << endl;
		for (int j = 0; j < nums[i].size(); j++) {
			cout << char(int('a')+j) << ". f(" << nums[i][j] << ") = " << recurse[i](nums[i][j]) << endl;
		}
		cout << endl;
	}
	return 0;
}
