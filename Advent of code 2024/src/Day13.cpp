#include "Day13.h"

Day13::Day13()
{
  //ctor
}

Day13::~Day13()
{
  //dtor
}

void Day13::part1(std::string filename){
  InputLoader input(filename);
  std::vector<std::vector<int>> inputNumbers = input.toVectorInt2d({"Button A: X+",", Y+", "Button B: X+", "Prize: X=", ", Y="});
  int sum = 0;
  for(int row=0; row<(int)inputNumbers.size(); row+=4){
    int tokenCount = 0;
    int ax = inputNumbers[row][0];
    int ay = inputNumbers[row][1];
    int bx = inputNumbers[row+1][0];
    int by = inputNumbers[row+1][1];
    int goalx = inputNumbers[row+2][0];
    int goaly = inputNumbers[row+2][1];
    int bCount = 0;
    int aCount = 0;
    while(tokenCount == 0 && aCount <= 100){
      // Increase B until reaching goal
      while(bCount < 100 && (aCount*ax+bCount*bx < goalx || aCount*ay+bCount*by < goaly))
        bCount++;
      if(aCount*ax+bCount*bx == goalx && aCount*ay+bCount*by == goaly)
        tokenCount = 3*aCount + bCount;
      //Increase a and try again if goal was not hit.
      aCount++;
      bCount=0;
    }
    sum+=tokenCount;
  }
  std::cout << "part 1: " << sum << std::endl;
}

void Day13::part2(std::string filename){
  std::cout << "part 2: " << std::endl;
}
