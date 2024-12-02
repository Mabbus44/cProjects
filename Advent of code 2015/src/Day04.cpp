#include "Day04.h"

Day04::Day04()
{
  //ctor
}

Day04::~Day04()
{
  //dtor
}

void Day04::part1(std::string filename){
  std::string input = "bgvyzdsv";
  int i=0;
  bool done=false;
  while(!done){
    std::string hashMe = input + std::to_string(i);
    std::string hashed = hashMe;
    int zeroes = 0;
    for(char c: hashed){
      if(c=='0')
        zeroes++;
      else
        break;
      if(zeroes == 5){
        done=true;
        break;
      }
    }
    i++;
  }
  std::cout << "part 1: " << i-1 << std::endl;
}

void Day04::part2(std::string filename){
  std::cout << "part 2: " << std::endl;
}
