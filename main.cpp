#include "tour.h"

using namespace std;

void test()///Utility function to test if algorithm works for every possible case
{
  for(int row = 1; row <= 8; row++)
  {
    for(int col = 1; col <= 8; col++)
    {
      tour newI(row, col);
      if(newI.solveTour())
      {
        cout << "SOLVED!\n";
      }
      else
      {
        cout << "FAIL\n";
      }
    }
  }
}

void run()///Utility function to test code without user input
{
  tour test(4, 1);
  test.printBoard();
  test.solveTour();
  test.printBoard();
}

int main()
{
  tour newTour;//Declaring new object
  newTour.start();//Starting the program using starter function
  //test();
  return 0;
}
