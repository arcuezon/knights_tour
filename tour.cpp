#include "tour.h"

tour::tour()
{
  //ctor
}

tour::tour(int row, int col)///Constructor sets starting square to 1 and sets curRow and curCol
{//INPUT SHOULD NOT BE ARRAY INDEX (i.e. 1 to 8)
  board[row - 1][col - 1] = 1;
  curCol = col - 1;
  curRow = row - 1;
  cout << "Starting position: " << curRow << " " << curCol << endl;
}

tour::~tour()
{
  //dtor
}

void tour::start()///Starter function that takes care of user input and calls the other functions
{
  input://Input for starting position
  cout << "Enter the starting position of the knight"
       << "(Row by Column) separated by a space: ";
  cin >> curRow >> curCol;

  if(curRow < 1 || curCol < 1 || curRow > 8 || curCol > 8)//Checking if input is valid
  {
    cout << "ERROR: Invalid starting position entered.\n \n";
    goto input;
  }

  curRow--; curCol--;//Converting to array indexing
  board[curRow][curCol] = 1;//Setting first square

  cout << "\nStarting Board:";//Print starting board
  printBoard();

  input2:
  cout << "\nDisplay options:\n1 - DISPLAY SOLUTION\n2 - "
       << "DISPLAY EACH STEP\nInput number of choice: ";
  int choice = 0;
  cin >> choice;

  if(choice < 1 || choice > 2)//Checking if input is valid
  {
    cout << "ERROR: Invalid number entered.\n";
    goto input2;
  }

  switch(choice)//Switch to handle the user choice
  {
  case 1://Display solution
    solveTour();
    cout << "\nSOLUTION:\n";
    printBoard();
    break;

  case 2://Display each step
    cout << "\nPress enter to display the succeeding steps.\n";
    solveTourDisplay();
    break;
  }

  char print;
  cout << "Would you like to save the solved tour to a file? (Y/N): ";
  cin >> print;

  switch(print)
  {
  case 'Y':
    cout << "\nSaved solved tour to 'solvedTour.txt'\n";
    saveToFile();
    break;

  case 'N':
    return;
    break;
  }

}

void tour::saveToFile()
{
  fstream output;
  output.open("solvedTour.txt", std::fstream::out);

  for(int row = 0; row < 8; row++)//Row for loop
  {
    for(int col = 0; col < 8; col++)//Column for loop
    {
      output << setw(5) << board[row][col];
    }
    output << endl << endl;
  }

  output.close();
}

void tour::printBoard()///Print function for chess board
{
  cout << endl;
  for(int row = 0; row < 8; row++)//Row for loop
  {
    for(int col = 0; col < 8; col++)//Column for loop
    {
      cout << setw(5) << board[row][col];
    }
    cout << endl << endl;
  }
}

bool tour::chkEmpty(int cRow, int cCol)///Check if a square is empty
{
  if(board[cRow][cCol] == 0)
  {
    return true;//Return true if square is empty or 0
  }

  else
  {
    return false;//Return false otherwise
  }
}

bool tour::chkValid(int cRow, int cCol)///Check if square is within bounds
{
  if(cRow >= 0 && cCol >= 0 && cRow < 8 && cCol < 8)
  {
    return true;
  }

  else
  {
    return false;
  }
}

int tour::cntPosMove(const int row, const int col)///Counts possible moves from current square
{//USE ARRAY INDEXING (0-7)
  int count = 0;//Possible moves count
  int trow, tcol;//Temporary variables

  for(int n = 0; n < 8; n++)//Iterate through all possible moves
  {
    trow = row + posRow[n];//Move Row
    tcol = col + posCol[n];//Move column

    if(chkValid(trow, tcol) && chkEmpty(trow, tcol))//Check if move is valid
    {
      count++;//If valid then add to count
    }

  }
  return count;
}

int tour::findLeast() ///Returns least moves possible for next
{                    ///squares or optimal n from the current square
  int row, col;
  row = curRow;
  col = curCol;

  int moves = 9;

  for(int n = 0; n < 8; n++)
  {
    //Debugging:
    //cout << n << ": " << cntPosMove(row += posRow[n], col += posCol[n]) << endl;

    if(cntPosMove(row + posRow[n], col + posCol[n]) < moves &&
       chkEmpty(row + posRow[n], col + posCol[n]) &&
       chkValid(row + posRow[n], col + posCol[n]))
    {
      //Debugging:
      //cout << "Possible: " << n << ": " << cntPosMove(row + posRow[n], col + posCol[n]) << endl;
      moves = (cntPosMove(row + posRow[n], col + posCol[n]));
    }
  }

  return moves;
}

bool tour::solveTour()///Solve tour using Warnsdorff's algorithm and backtracking
{
  if(moveNo == 64)//If move number is 64 then done
  {
    return true;
  }

  int leastMoves = findLeast();//Setting least moves to the
                               //least possible moves from the current square

  for(int n = 0; n < 8; n++)//Tries all possible moves
  {
    int newRow = curRow + posRow[n];
    int newCol = curCol + posCol[n];

    if(!chkValid(newRow, newCol)
      || !chkEmpty(newRow, newCol)
      || cntPosMove(newRow, newCol) != leastMoves)
    {//Applying Warnsdorff's algorithm and only move if empty and valid and satisfies heuristic
      continue;//If not satisfied then next n in loop
    }

    board[newRow][newCol] = moveNo + 1;//Moving to possible square
    curRow = newRow;//Setting current square to the new square
    curCol = newCol;
    moveNo++;//Incrementing move number


    if(solveTour())//Recursively calling function
    {
      return true;
    }

    else//If recursion fails
    {
      curRow -= posRow[n];//Move back
      curCol -= posCol[n];
      moveNo--;//Set to previous move
      board[newRow][newCol] = 0;//Removing knight from square
    }
  }
  return false;//If a move is not found return false to trigger backtracking
}

bool tour::solveTourDisplay()///Difference from above function is to display each move
{
  if(moveNo == 64)
  {
    return true;
  }

  int leastMoves = findLeast();

  for(int n = 0; n < 8; n++)
  {
    int newRow = curRow + posRow[n];
    int newCol = curCol + posCol[n];

    if(!chkValid(newRow, newCol)
      || !chkEmpty(newRow, newCol)
      || cntPosMove(newRow, newCol) != leastMoves)
    {
      continue;
    }

    board[newRow][newCol] = moveNo + 1;
    curRow = newRow;
    curCol = newCol;
    moveNo++;

    //Code to display each step
    getline(cin, in);//Wait for user input before displaying
    if(moveNo != 64)
    {
      cout << "\nMove: " << moveNo << endl;
    }
    else//If move == 64 then solved
    {
      cout << "SOLUTION:\n";
    }
    printBoard();

    if(solveTourDisplay())
    {
      return true;
    }

    else
    {

      //Informing the user of the backtracking performed
      cout << endl << "BACKTRACK:\n";
      cout << "Move number: " << moveNo << endl;
      cout << newRow + 1 << "x" << newCol + 1 << " = 0\n";

      curRow -= posRow[n];
      curCol -= posCol[n];
      moveNo--;
      board[newRow][newCol] = 0;
    }
  }
  return false;
}
