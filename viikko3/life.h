#ifndef LIFE_H
#define LIFE_H

#include <iostream>
using namespace std;

void instructions();
bool user_says_yes();

class Life {
public:
    Life();
    Life(int aMaxRow, int aMaxCol);
    void initialize();
    void print();
    void update();

private:
    int grid[20 + 2][60 + 2];  // allows for two extra rows and columns
    int neighbor_count(int row, int col);
    int maxrow, maxcol;
};

#endif // LIFE_H

