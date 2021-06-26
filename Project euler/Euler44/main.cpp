#include <iostream>

#ifndef PENTCOUNT
#define PENTCOUNT 6000
#endif

int main(int argc, char **argv)
{
  int pentNum[PENTCOUNT];			//pentagon numbers
  int add;					//number to add for next pentagon number
  int pentCount;				//Number of pentagon numbers
  int pentNumA, pentNumB, pentNumC;		//Pentagon number A B and C for testing
  int pentSum;					//Sum or difference of two pentagon numbers
  int minDiff=999999999;					//Min diff between pentagon numbers that fulfill the requirements
  bool isPentNum;				//If checked number is pentagon number
  
  pentNum[0] = 1;
  pentCount = 1;
  add=1;
  
  while(pentCount < PENTCOUNT)
  {
    add+=3;
    pentNum[pentCount]=pentNum[pentCount-1]+add;
    pentCount++;
  }
  
  pentNumA=0;
  pentNumB=0;
  pentNumC=0;
  while(pentNumA<PENTCOUNT && pentNumB<PENTCOUNT && pentNumC<PENTCOUNT)						//Go thourgh all pentagon numbers
  {
    std::cout << "A: " << pentNumA << std::endl;
    pentNumB=0;
    while(pentNumB<=pentNumA && pentNumB<PENTCOUNT && pentNumC<PENTCOUNT)			//Add/substract with all pentagon numbers smaller or equal
    {
      pentSum=pentNum[pentNumA]-pentNum[pentNumB];			//substract numbers
      pentNumC=0;
      while(pentNumC < PENTCOUNT && pentNum[pentNumC] < pentSum)	//Check if result is pentagon number
	pentNumC++;
      if(pentNum[pentNumC]==pentSum)
      {
	isPentNum=true;
//	std::cout << "Sum: " << pentNum[pentNumA] << " - " << pentNum[pentNumB] << " = " << pentSum << ", " << pentNum[pentNumC] << std::endl;
      }
      else
	isPentNum=false;
      pentSum=pentNum[pentNumA]+pentNum[pentNumB];			//Add numbers
      pentNumC=0;
      while(pentNumC < PENTCOUNT && pentNum[pentNumC] < pentSum)	//Check if result is pentagon number
	pentNumC++;
//      if(pentNum[pentNumC]==pentSum)
//	std::cout << "Sum: " << pentNum[pentNumA] << " + " << pentNum[pentNumB] << " = " << pentSum << ", " << pentNum[pentNumC] << std::endl;
      if(isPentNum && pentNum[pentNumC]==pentSum)
      {
	std::cout << "FOUND ONE!!!!!: " << pentNum[pentNumA] << " - " << pentNum[pentNumB] << std::endl;
	if(pentNum[pentNumA]-pentNum[pentNumB]<minDiff)
	{
	  minDiff = pentNum[pentNumA] - pentNum[pentNumB];
	  std::cout << "New smallest diff: " << pentNum[pentNumA] << " - " << pentNum[pentNumB] << " = " << minDiff << std::endl;
	}
      }
      pentNumB++;
    }
    pentNumA++;
  }
  std::cout << "Ran out of Penagon numbers " << pentNum[PENTCOUNT-1] << std::endl;
  return 0;
}
