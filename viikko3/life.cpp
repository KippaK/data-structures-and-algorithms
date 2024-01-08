#include "life.h"

Life::Life() 
{
    maxrow = 20;
    maxcol = 60;
}

Life::Life(int aMaxRow, int aMaxCol)
{
    maxrow = aMaxRow;
    maxcol = aMaxCol;
}

void Life::initialize() {
    int row, col;
    for (row = 0; row <= maxrow + 1; row++)
        for (col = 0; col <= maxcol + 1; col++)
            grid[row][col] = 0;
    cout << "List the coordinates for living cells." << endl;
    cout << "Terminate the list with the special pair -1 -1" << endl;
    cin >> row >> col;

    while (row != -1 || col != -1) {
        if (row >= 1 && row <= maxrow)
            if (col >= 1 && col <= maxcol)
                grid[row][col] = 1;
            else
                cout << "Column " << col << " is out of range." << endl;
        else
            cout << "Row " << row << " is out of range." << endl;
        cin >> row >> col;
    }
}

void Life::print() {
    int row, col;
    cout << "\nThe current Life configuration is:" << endl;
    for (row = 1; row <= maxrow; row++) {
        for (col = 1; col <= maxcol; col++)
            if (grid[row][col] == 1)
                cout << '*';
            else
                cout << ' ';
        cout << endl;
    }
    cout << endl;
}

int Life::neighbor_count(int row, int col) {
    int i, j;
    int count = 0;
    for (i = row - 1; i <= row + 1; i++)
        for (j = col - 1; j <= col + 1; j++)
            count += grid[i][j];  // Increase the count if the neighbor is alive.
    count -= grid[row][col]; // Reduce count, since the cell is not its own neighbor.
    return count;
}

void Life::update() {
    int row, col;
    int new_grid[maxrow + 2][maxcol + 2];

    for (row = 1; row <= maxrow; row++)
        for (col = 1; col <= maxcol; col++)
            switch (neighbor_count(row, col)) {
                case 2:
                    new_grid[row][col] = grid[row][col];  // Status stays the same.
                    break;
                case 3:
                    new_grid[row][col] = 1;                // Cell is now alive.
                    break;
                default:
                    new_grid[row][col] = 0;                // Cell is now dead.
            }

    for (row = 1; row <= maxrow; row++)
        for (col = 1; col <= maxcol; col++)
            grid[row][col] = new_grid[row][col];
}

void instructions() {
    cout << "Welcome to Conway's game of Life." << endl;
    cout << "This game uses a grid of size "
         << 20 << " by " << 60 << " in which" << endl;
    cout << "each cell can either be occupied by an organism or not." << endl;
    cout << "The occupied cells change from generation to generation" << endl;
    cout << "according to the number of neighboring cells which are alive." << endl;
}

bool user_says_yes() {
    int c;
    bool initial_response = true;

    do {  // Loop until an appropriate input is received.
        if (initial_response)
            cout << " (y,n)? " << flush;
        else
            cout << "Respond with either y or n: " << flush;

        do { // Ignore white space.
            c = cin.get();
        } while (c == '\n' || c == ' ' || c == '\t');
        initial_response = false;
    } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
    return (c == 'y' || c == 'Y');
}

