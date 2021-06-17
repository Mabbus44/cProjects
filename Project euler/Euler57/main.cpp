#include <iostream>
#include "Number.h"

using namespace std;

int main(int argc, char **argv) {
  Number d, n, lastD, lastN, two;
  int count;
  count=0;
  lastN=1;
  lastD=2;
  two=2;
  for(int i=2; i<=1000; i++){
    n=lastD;
    d=two*lastD+lastN;
    lastD=d;
    lastN=n;
    n=n+d;
    if(n.getDigitCount()>d.getDigitCount())
      count ++;
  }
  cout << count;
  return 0;
}
