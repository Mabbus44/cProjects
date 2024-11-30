#include "Day02.h"

Day02::Day02()
{
  //ctor
}

Day02::~Day02()
{
  //dtor
}

void Day02::part1(std::string filename){
  InputLoader inputLoader(filename);
  std::vector<std::vector<int>> input = inputLoader.toVectorInt2d({"x"});
  int totArea = 0;
  for(std::vector<int>& row: input){
    int s1 = row[0]*row[1];
    int s2 = row[1]*row[2];
    int s3 = row[2]*row[0];
    int minVal = std::min(s1, s2);
    minVal = std::min(minVal, s3);
    int area = s1*2+s2*2+s3*2+minVal;
    totArea = totArea + area;
  }
  std::cout << "part 1: " << totArea << std::endl;
}

void Day02::part2(std::string filename){
  InputLoader inputLoader(filename);
  std::vector<std::vector<int>> input = inputLoader.toVectorInt2d({"x"});
  int totLen = 0;
  for(std::vector<int>& row: input){
    if(row[1] > row[2])
      std::swap(row[1], row[2]);
    if(row[0] > row[1])
      std::swap(row[0], row[1]);
    if(row[1] > row[2])
      std::swap(row[1], row[2]);
    int volume = row[0]*row[1]*row[2];
    int len = row[0]*2 + row[1]*2;
    totLen = totLen+volume+len;
  }
  std::cout << "part 2: " << totLen<< std::endl;
}
