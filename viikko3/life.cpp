#include "life.h"

Life::Life()
{
   row = 20;
   col = 60;
   grid = new int[row*col];
}

Life::Life(int aRow, int aCol)
{
   row = aRow;
   col = aCol;
   grid = new int[row*col];
}

void Life::initialize()
{
   for (int y = 0; y < row; y++) {
      for (int x = 0; x < col; x++) {
         grid[y*col+x] = 0;
      }
   }
   cout << "List the coordinates for living cells." << endl;
   cout << "Terminate the list with special pair -1 -1" << endl;
   int x, y;
   cin >> y >> x;

   while (y != -1 || x != -1) {
      if (y > 0 && y < row) {
         if (x > 0 && x < col) {
            grid[y*col+x] = 1;
         }
         else {
            cout << "Column " << x << " is out of range." << endl;
         }
      }
      else {
         cout << "Row " << y << " is out of range." << endl;
      }
      cin >> y >> x;
   }
}

void Life::print()
{
   system("clear");
   cout << "The current Life configuration is:" << endl;
   for (int y = 0; y < row; y++) {
      for (int x = 0; x < col; x++) {
         if (grid[y*col+x] == 1) {
            cout << '*';
         }
         else {
            cout << ' ';
         }
      }
      cout << endl;
   }
   cout << endl;
}

int Life::neighbor_count(int y, int x)
{
   int count = 0;
   for (int i = y - 1; i < y + 2; i++) {
      for (int j = x - 1; j < x + 2; j++) {
         if (i < 0 || i == row || j < 0 || j == col) {
            continue;
         }
         count += grid[i*col+j];  
      }
   }
   count -= grid[y*col+x];
   return count;
}

void Life::update()
{
   int *new_grid = new int[col*row];
   for (int y = 0; y < row; y++) {
      for (int x = 0; x < col; x++) {
         switch (neighbor_count(y, x)) {
            case 2:
               new_grid[y*col+x] = grid[y*col+x];
               break;
            case 3:
               new_grid[y*col+x] = 1;
               break;
            default:
               new_grid[y*col+x] = 0;

         }
      }
   }
   delete grid;
   grid = new_grid;
   return;
}

void Life::instructions()
{
   cout << "Welcome to Conway's game of Life." << endl;
   cout << "Each cell of a grid can either be occupied by organism or not" << endl;
   cout << "The occuied cells change from generation to generation" << endl;
   cout << "according to the number of neighboring cell which are alive" << endl;
}
