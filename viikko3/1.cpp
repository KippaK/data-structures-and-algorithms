/* Program extracts from Chapter 1 of
   "Data Structures and Program Design in C++"
   by Robert L. Kruse and Alexander J. Ryba
   Copyright (C) 1999 by Prentice-Hall, Inc.  All rights reserved.
   Extracts from this file may be used in the construction of other programs,
   but this code will not compile or execute as given here. */


// Section 1.2:

#include "utility.h"
#include "life.h"

int main()  //  Program to play Conway's game of Life.
/*
Pre:  The user supplies an initial configuration of living cells.
Post: The program prints a sequence of pictures showing the changes in
      the configuration of living cells according to the rules for
      the game of Life.
Uses: The class Life and its methods initialize(), print(), and update().
      The functions  instructions(),  user_says_yes().
*/

{
   Life configuration;
   instructions();
   configuration.initialize();
   configuration.print();
   cout << "Continue viewing new generations? " << endl;
   while (user_says_yes()) {
      configuration.update();
      configuration.print();
      cout << "Continue viewing new generations? " << endl;
   }
}


#include <iostream>
using namespace std;

#include "utility.h"


// Section 1.3:

do {
   study();
} while (TV.in_hock());
if (!sleepy) play();
else nap();


class a {  //  a deck of cards
   int X; thing Y1[52];  /*  X is the location of the top card in the deck.
   Y1 lists the cards. */  
   public: 
   a();
   void Shuffle(); //  Shuffle randomly arranges the cards.
   thing d(); //  deals the top card off the deck
}
                 ;


int a[n][n], i, j;

for (i = 0; i < n; i++) {
  for (j = 0; j < n; j++) {
     a[i][j] = ((i + 1) / (j + 1)) * ((j + 1) / (i + 1));
   }
}

void does_something(int &first, int &second)
{
  first = second - first;
  second = second - first;
  first = second + first;
}


int calculate(int apple, int orange)
{
   int peach,lemon;
   peach = 0;
   lemon = 0;
   if (apple < orange) { 
      peach = orange; 
   }
   else if (orange <= apple) {
      peach = apple; 
   }
   else { 
      peach = 17;
      lemon = 19;
   }
   return(peach);
}


float figure (vector vector1)
{ 
   int loop1,loop4; 
   float loop2,loop3;
   loop1 = 0; 
   loop2 = vector1[loop1]; 
   loop3 = 0.0;
   loop4 = loop1; 
   for (loop4 = 0; loop4<max; loop4++) { 
      loop1 = loop1 + 1;
      loop2 = vector1[loop1 - 1];
      loop3 = loop2 + loop3;
   } 
   loop1 = loop1 - 1;
   loop2 = loop1 + 1;
   return (loop2 = loop3/loop2); 
}


int question(int &a17, int &stuff)
{ 
   int another, yetanother, stillonemore;
   another = yetanother; 
   stillonemore = a17;
   yetanother = stuff; 
   another = stillonemore;
   a17 = yetanother; 
   stillonemore = yetanother;
   stuff = another; 
   another = yetanother;
   yetanother = stuff;
}


int mystery(int apple, int orange, int peach)
{ if (apple > orange) if (apple > peach) if
(peach > orange) return(peach); else if (apple < orange)
return(apple); else return(orange); else return(apple); else
if (peach > apple) if (peach > orange) return(orange); else
return(peach); else return(apple);}


if (x < z) if (x < y) if (y < z) c = 1; else c = 2; else
  if (y < z) c = 3; else c = 4; else if (x < y)
  if (x < z) c = 5; else c = 6; else if (y < z) c = 7; else
  if (z < x) if (z < y) c = 8; else c = 9; else c = 10;


float function fcn(float stuff)
{ float april, tim, tiny, shadow, tom, tam, square; int flag;
tim = stuff;  tam = stuff;  tiny = 0.00001;
if (stuff != 0) do {shadow = tim + tim; square = tim * tim;
tom = (shadow + stuff/square); april = tom / 3.0;
if (april*april * april - tam > -tiny) if (april*april*april - tam
     < tiny) flag = 1; else flag = 0; else flag = 0;
if (flag == 0) tim = april; else tim = tam;} while (flag != 1);
if (stuff == 0) return(stuff); else return(april); }



// Section 1.4:

void instructions() { }
bool user_says_yes() { return(true);}


typedef int bool;
const bool false = 0;
const bool true = 1;


class Life {
public:
   void initialize();
   void print();
   void update();
};


void Life::initialize() {}
void Life::print() {}
void Life::update() {}


const int maxrow = 20, maxcol = 60;    //  grid dimensions

class Life {
public:
   void initialize();
   void print();
   void update();
private:
   int grid[maxrow + 2][maxcol + 2];  //  allows for two extra rows and columns
   int neighbor_count(int row, int col);
};


int Life::neighbor_count(int row, int col)
/*
Pre:  The Life object contains a configuration, and the coordinates
      row and col define a cell inside its hedge.
Post: The number of living neighbors of the specified cell is returned.
*/

{
   int i, j;
   int count = 0;
   for (i = row - 1; i <= row + 1; i++)
      for (j = col - 1; j <= col + 1; j++)
         count += grid[i][j];  //  Increase the count if neighbor is alive.
   count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
   return count;
}

void Life::update()
/*
Pre:  The Life object contains a configuration.
Post: The Life object contains the next generation of configuration.
*/

{
   int row, col;
   int new_grid[maxrow + 2][maxcol + 2];

   for (row = 1; row <= maxrow; row++)
      for (col = 1; col <= maxcol; col++)
         switch (neighbor_count(row, col)) {
         case 2:
            new_grid[row][col] = grid[row][col];  //  Status stays the same.
            break;
         case 3:
            new_grid[row][col] = 1;                //  Cell is now alive.
            break;
         default:
            new_grid[row][col] = 0;                //  Cell is now dead.
         }

   for (row = 1; row <= maxrow; row++)
      for (col = 1; col <= maxcol; col++)
         grid[row][col] = new_grid[row][col];
}


void instructions()
/*
Pre:  None.
Post: Instructions for using the Life program have been printed.
*/

{
   cout << "Welcome to Conway's game of Life." << endl;
   cout << "This game uses a grid of size "
        << maxrow << " by " << maxcol << " in which" << endl;
   cout << "each cell can either be occupied by an organism or not." << endl;
   cout << "The occupied cells change from generation to generation" << endl;
   cout << "according to the number of neighboring cells which are alive."
        << endl;
}


void Life::initialize()
/*
Pre:  None.
Post: The Life object contains a configuration specified by the user.
*/

{
   int row, col;
   for (row = 0; row <= maxrow+1; row++)
      for (col = 0; col <= maxcol+1; col++)
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


void Life::print()
/*
Pre:  The Life object contains a configuration.
Post: The configuration is written for the user.
*/

{
   int row, col;
   cout << "\nThe current Life configuration is:" <<endl;
   for (row = 1; row <= maxrow; row++) {
      for (col = 1; col <= maxcol; col++)
         if (grid[row][col] == 1) cout << '*';
         else cout << ' ';
      cout << endl;
   }
   cout << endl;
}


bool user_says_yes()
{
   int c;
   bool initial_response = true;

   do {  //  Loop until an appropriate input is received.
      if (initial_response)
         cout << " (y,n)? " << flush;

      else
         cout << "Respond with either y or n: " << flush;

      do { //  Ignore white space.
         c = cin.get();
      } while (c == '\n' || c ==' ' || c == '\t');
      initial_response = false;
   } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
   return (c == 'y' || c == 'Y');
}


int main () //   driver for neighbor_count()
/*
Pre:  None.
Post: Verifies that the method neighbor_count() returns the correct values.
Uses: The class Life and its method initialize().
*/

{
   Life configuration;
   configuration.initialize();
   for (row = 1; row <= maxrow; row++){
      for (col = 1; col <= maxrow; col++)
          cout << configuration.neighbor_count(row,col) << " ";
      cout << endl;
   }
}


configuration.initialize();
configuration.print();


if (a < b) if (c > d) x = 1; else if (c == d) x = 2;
else x = 3; else if (a == b) x = 4; else if (c == d) x = 5;
else x = 6;

/*************************************************************************/

