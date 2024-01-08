#pragma once

#include <iostream>
using namespace std;

class Life {

public:
	Life();
	Life(int aRow, int aCol);
	void initialize();
	void print();
	void update();
	void instructions();

private:
	int neighbor_count(int x, int y);

private:
	int *grid = NULL;
	int row, col;
};
