#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include "Number.h"

using namespace std;


int main(int argc, char **argv)
{
  bool isLych;
  Number a, b;
  int iterations, lychCount=0;
  for(int i=1; i<10000; i++){
    a = i;
    isLych = true;
    iterations = 0;
    while(iterations<50 && isLych){
      b = a;
      b.reverseDigits();
      a=a+b;
      if(a.isPalindrom())
	isLych = false;
      iterations++;
    }
    if(isLych){
      lychCount++;
      cout << i << " is lych number" << endl;
    }
  }
  cout << lychCount << " lych numbers" << endl;
  return 0;
}
