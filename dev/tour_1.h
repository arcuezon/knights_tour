#ifndef TOUR_H
#define TOUR_H

#include<iostream>
#include<iomanip>
#include<fstream>

using namespace std;

class tour
{
  public:
    tour();
    tour(int x, int y);
    ~tour();
    void printBoard();
    ///Function to print the chessboard
    int cntPosMove(int row, int col);
    ///Function to count the number of possible moves from a square
    bool chkValid(int cRow, int cCol);
    ///Function to check if a square/move is valid and within bounds
    bool chkEmpty(int cRow, int cCol);
    ///Function to check if a square is empty
    int findLeast();
    ///Function that returns the number of possible moves from adjacent squares
    ///or squares that the knight can move to using chkValid, chkEmpty, and cntPosMove
    bool solveTour();
    ///Function to solve a tour using Warnsdorff's algorithm and backtracking
    bool solveTourDisplay();
    ///Same as solveTour but displays each step of the solution
    void start();
    ///Starter function that handles user input and calls the solveTour functions
    void saveToFile();
    ///Function to save a solved tour to a text file

  protected:

  private:
    int board[8][8] = {{0}};
    ///Array for the 8x8 chessboard with all squares set to 0

    const int posRow[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    const int posCol[8] = {1, -1, -2, 2, -2, 2, 1, -1};
    /**
    These are the possible moves of a knight.
    These will be added to the square. The arrays are a pair and work together
    so the index number has to be the same for both when moving a knight.
    **/

    int curRow = 0;///Current row
    int curCol = 0;///Current column
    int moveNo = 1;///Current move number
    string in;///Utility variable for user prompt
};

#endif // TOUR_H
