#include <iostream>

int main(int argc, char **argv) {
  int decimalIndex;					//what decimalindex we are on
  int digitsInNum;					//digits in digitsInNum
  int num;						//number being added
  int nextCheckpoint;					//next wanted number
  
  num=1;
  digitsInNum=1;
  decimalIndex=1;
  nextCheckpoint=10;
  
  while(nextCheckpoint<=1000000)
  {
    num++;
    if(num==10 || num==100 || num==1000 || num==10000 || num==100000 || num==1000000 || num==10000000)
    {
      digitsInNum++;
      std::cout << std::endl << "num: " << num << std::endl;
      std::cout << "digitsInNum: " << digitsInNum << std::endl;
    }
    decimalIndex+=digitsInNum;
    if(decimalIndex>=nextCheckpoint)
    {
      std::cout << std::endl << "Checkpoint: " << nextCheckpoint << std::endl;
      std::cout << "num: " << num << std::endl;
      std::cout << "decimalIndex: " << decimalIndex << std::endl;
      nextCheckpoint*=10;
    }
  }
  std::cout << "Hello, world!" << std::endl;
    return 0;
}
