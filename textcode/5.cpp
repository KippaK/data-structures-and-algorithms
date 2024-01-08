/* Program extracts from Chapter 5 of
   "Data Structures and Program Design in C++"
   by Robert L. Kruse and Alexander J. Ryba
   Copyright (C) 1999 by Prentice-Hall, Inc.  All rights reserved.
   Extracts from this file may be used in the construction of other programs,
   but this code will not compile or execute as given here. */


// Section 5.1:

int factorial(int n)
/*
Pre:  n is a nonnegative integer.
Post: Return the value of the factorial of n.
*/
{
   if (n == 0)
      return 1;
   else
      return n * factorial(n - 1);
}


move(63,1,2,3); //  Move 63 disks from tower 1 to 2 (tower 3 temporary).
cout << "Move disk 64 from tower 1 to tower 3."  << endl;
move(63,2,3,1); //  Move 63 disks from tower 2 to 3 (tower 1 temporary).


const int disks = 64;  // Make this constant much smaller to run program.
void move(int count, int start, int finish, int temp);

/*
Pre:  None.
Post: The simulation of the Towers of Hanoi has terminated.
*/
main()
{
   move(disks, 1, 3, 2);
}


void move(int count, int start, int finish, int temp)
{
   if (count > 0) {
      move(count - 1, start, temp, finish);
      cout << "Move disk " << count << " from " << start
           << " to " << finish << "." << endl;
      move(count - 1, temp, finish, start);
   }
}


move(1, 1, 2, 3); //  Move 1 disk from tower 1 to 2 (using tower 3).
cout << "Move disk 2 from tower 1 to tower 3."  << endl;
move(1, 2, 3, 1); //  Move 1 disk from tower 2 to 3 (using tower 1).


move(0, 1, 3, 2); //  Move 0 disks.
cout << "Move disk 1 from tower 1 to tower 2."  << endl;
move(0, 3, 2, 1); //  Move 0 disks.



// Section 5.2:

void move(int count, int start, int finish, int temp)
/*    move: iterative version
Pre:  Disk count is a valid disk to be moved.
Post: Moves count disks from start to finish using temp for temporary
      storage.
*/
{
   int swap;            //  temporary storage to swap towers
   while (count > 0) {  //  Replace the if statement with a loop.
      move(count - 1, start, temp, finish);  //  first recursive call
      cout << "Move disk " << count << " from " << start
           << " to " << finish << "." << endl;
      count--;  //  Change parameters to mimic the second recursive call.
      swap = start;
      start = temp;
      temp = swap;
   }
}


int factorial(int n)
/*    factorial: recursive version
Pre:  n is a nonnegative integer.
Post: Return the value of the factorial of n.
*/
{
   if (n == 0) return 1;
   else        return n * factorial(n - 1);
}


int factorial(int n)
/*    factorial: iterative version
Pre:  n is a nonnegative integer.
Post: Return the value of the factorial of n.
*/
{
   int count, product = 1;
   for (count = 1; count <= n; count++)
      product *= count;
   return product;
}


int fibonacci(int n)
/*    fibonacci: recursive version
Pre:  The parameter n is a nonnegative integer.
Post: The function returns the nth Fibonacci number.
*/
{
   if (n <= 0)  return 0;
   else if (n == 1)  return 1;
   else              return fibonacci(n - 1) + fibonacci(n - 2);
}


int fibonacci(int n)
/*    fibonacci: iterative version
Pre:  The parameter n is a nonnegative integer.
Post: The function returns the nth Fibonacci number.
*/
{
   int last_but_one;   //  second previous Fibonacci number, F_i-2
   int last_value;     //  previous Fibonacci number, F_i-1
   int current;        //  current Fibonacci number F_i
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



// Section 5.3:

int main()
/*
Pre:  The user enters a valid board size.
Post: All solutions to the n-queens puzzle for the selected
      board size are printed.
Uses: The class Queens and the recursive function solve_from.
*/
{
   int board_size;
   print_information();
   cout << "What is the size of the board? " << flush;
   cin  >> board_size;
   if (board_size < 0 || board_size > max_board)
      cout << "The number must be between 0 and " << max_board << endl;
   else {
      Queens configuration(board_size); //   Initialize empty configuration.
      solve_from(configuration);  //  Find all solutions extending configuration.
   }
}


void solve_from(Queens &configuration)
/*
Pre:  The Queens configuration represents a partially completed
      arrangement of nonattacking queens on a chessboard.
Post: All n-queens solutions that extend the given configuration are printed.
      The configuration is restored to its initial state.
Uses: The class Queens and the function solve_from, recursively.
*/
{
   if (configuration.is_solved()) configuration.print();
   else
      for (int col = 0; col < configuration.board_size; col++)
         if (configuration.unguarded(col)) {
            configuration.insert(col);
            solve_from(configuration);   //   Recursively continue to add queens.
            configuration.remove(col);
         }
}


const int max_board = 30;

class Queens {
public:
   Queens(int size);
   bool is_solved() const;
   void print() const;
   bool unguarded(int col) const;
   void insert(int col);
   void remove(int col);
   int  board_size; //   dimension of board = maximum number of queens
private:
   int  count;      //   current number of queens = first unoccupied row
   bool queen_square[max_board][max_board];
};


void Queens::insert(int col)
/*
Pre:  The square in the first unoccupied row (row count) and column col
      is not guarded by any queen.
Post: A queen has been inserted into the square at row count and column
      col; count has been incremented by 1.
*/
{
   queen_square[count++][col] = true;
}


Queens::Queens(int size)
/*
Post: The Queens object is set up as an empty
      configuration on a chessboard with size squares in each row and column.
*/
{
   board_size = size;
   count = 0;
   for (int row = 0; row < board_size; row++)
      for (int col = 0; col < board_size; col++)
         queen_square[row][col] = false;
}


bool Queens::unguarded(int col) const
/*
Post: Returns true or false according as the square in the first
      unoccupied row (row count) and column col is not guarded by any queen.
*/
{
   int i;
   bool ok = true; //   turns false if we find a queen in column or diagonal

   for (i = 0; ok && i < count; i++)
      ok = !queen_square[i][col];              //   Check upper part of column
   for (i = 1; ok && count - i >= 0 && col - i >= 0; i++)
      ok = !queen_square[count - i][col - i];  //  Check upper-left diagonal
   for (i = 1; ok && count - i >= 0 && col + i < board_size; i++)
      ok = !queen_square[count - i][col + i];  //  Check upper-right diagonal

   return ok;
}


class Queens {
public:
   Queens(int size);
   bool is_solved() const;
   void print() const;
   bool unguarded(int col) const;
   void insert(int col);
   void remove(int col);
   int board_size;
private:
   int  count;
   bool col_free[max_board];
   bool upward_free[2 * max_board - 1];
   bool downward_free[2 * max_board - 1];
   int  queen_in_row[max_board];  //   column number of queen in each row
};


Queens::Queens(int size)
/*
Post: The Queens object is set up as an empty
      configuration on a chessboard with size squares in each row and column.
*/
{
   board_size = size;
   count = 0;
   for (int i = 0; i < board_size; i++) col_free[i] = true;
   for (int j = 0; j < (2 * board_size - 1); j++) upward_free[j] = true;
   for (int k = 0; k < (2 * board_size - 1); k++) downward_free[k] = true;
}


void Queens::insert(int col)
/*
Pre:   The square in the first unoccupied row (row count) and column col
      is not guarded by any queen.
Post: A queen has been inserted into the square at row count and column
      col; count has been incremented by 1.
*/
{
   queen_in_row[count] = col;
   col_free[col] = false;
   upward_free[count + col] = false;
   downward_free[count - col + board_size - 1] = false;
   count++;
}


bool Queens::unguarded(int col) const
/*
Post: Returns true or false according as the square in the first
      unoccupied row (row count) and column col is not guarded by any queen.
*/
{
   return  col_free[col]
           && upward_free[count + col]
           && downward_free[count - col + board_size - 1];
}



// Section 5.4:

class Board {
public:
   Board();                    //  constructor for initialization
   int done()  const;          //  Test whether the game is over.
   void play(Move try_it);
   int evaluate()  const;
   int legal_moves(Stack &moves)  const;
   int worst_case()  const;
   int better(int value, int old_value) const; //  Which parameter does the mover prefer?
   void print()  const;
   void instructions()  const;
/*  Additional methods, functions, and data will depend on
    the game under consideration. */
};


int look_ahead(const Board &game, int depth, Move &recommended)
/*
Pre:  Board game represents a legal game position.
Post: An evaluation of the game, based on looking ahead
      depth moves, is returned.  The best move that can be found
      for the mover is recorded as Move recommended.
Uses: The classes Stack, Board, and Move, together with
      function look_ahead recursively.
*/
{
   if (game.done() || depth == 0)
      return game.evaluate();
   else {
      Stack moves;
      game.legal_moves(moves);
      int value, best_value = game.worst_case();

      while (!moves.empty()) {
         Move try_it, reply;
         moves.top(try_it);
         Board new_game = game;
         new_game.play(try_it);
         value = look_ahead(new_game, depth - 1, reply);
         if (game.better(value, best_value)) { //  try_it is the best move yet found
            best_value = value;
            recommended = try_it;
         }
         moves.pop();
      }
      return best_value;
   }
}


//  class for a tic-tac-toe move
class Move {
public:
   Move();
   Move(int r, int c);
   int row;
   int col;
};


Move::Move()
/*
Post: The Move is initialized to an illegal, default value.
*/
{
   row = 3;
   col = 3;
}


Move::Move(int r, int c)
/*
Post: The Move is initialized to the given coordinates.
*/
{
   row = r;
   col = c;
}


class Board {
public:
   Board();
   bool done() const;
   void print() const;
   void instructions() const;
   bool better(int value, int old_value) const;
   void play(Move try_it);
   int worst_case() const;
   int evaluate() const;
   int legal_moves(Stack &moves) const;
private:
   int squares[3][3];
   int moves_done;
   int the_winner() const;
};


Board::Board()
/*
Post: The Board is initialized as empty.
*/
{
   for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
         squares[i][j] = 0;
   moves_done = 0;
}


void Board::play(Move try_it)
/*
Post: The Move try_it is played on the Board.
*/
{
   squares[try_it.row][try_it.col] = moves_done % 2 + 1;
   moves_done++;
}


int Board::the_winner() const
/*
Post: Return either a value of 0 for a position where neither player has won,
      a value of 1 if the first player has won,
      or a value of 2 if the second player has won.
*/
{
   int i;
   for (i = 0; i < 3; i++)
      if (squares[i][0] && squares[i][0] == squares[i][1]
                        && squares[i][0] == squares[i][2])
            return squares[i][0];

   for (i = 0; i < 3; i++)
      if (squares[0][i] && squares[0][i] == squares[1][i]
                        && squares[0][i] == squares[2][i])
            return squares[0][i];


   if (squares[0][0] && squares[0][0] == squares[1][1]
                     && squares[0][0] == squares[2][2])
            return squares[0][0];

   if (squares[0][2] && squares[0][2] == squares[1][1]
                     && squares[2][0] == squares[0][2])
            return squares[0][2];
   return 0;
}


bool Board::done() const
/*
Post: Return true if the game is over; either because a player has already won
      or because all nine squares have been filled.
*/
{
   return moves_done == 9 || the_winner() > 0;
}


int Board::legal_moves(Stack &moves) const
/*
Post: The parameter Stack moves is set up to contain all
      possible legal moves on the Board.
*/
{
   int count = 0;
   while (!moves.empty()) moves.pop();
   for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
         if (squares[i][j] == 0) {
            Move can_play(i,j);
            moves.push(can_play);
            count++;
         }
   return count;
}


int Board::evaluate() const
/*
Post: Return either a value of 0 for a position where neither player has won,
      a positive value between 1 and 9 if the first player has won,
      or a negative value between -1 and -9 if the second player has won,
*/
{
   int winner = the_winner();
   if (winner == 1) return 10 - moves_done;
   else if (winner == 2) return moves_done - 10;
   else return 0;
}


/*************************************************************************/

