#include <iostream>
#include "Number.h"

using namespace std;

int main(int argc, char **argv) {
  Number a, b, maxA;
  int digitSum, maxDigitSum=0, maxi, maxi2;
  for(int i=1; i<100; i++){
    for(int i2=1; i2<100; i2++){
      a=i;
      b=i;
      for(int i3=1; i3<i2; i3++){
	a=a*b;
      }
      digitSum=a.digitalSum();
      if(digitSum>maxDigitSum){
	maxA=a;
	maxi=i;
	maxi2=i2;
	maxDigitSum=digitSum;
	cout << maxi << "^" << maxi2 << "=";
	maxA.outputNumber();
	cout << endl;
	cout << "Digitsum: " << maxDigitSum << endl << endl;
      }
    }
  }
  cout << maxi << "^" << maxi2 << "=";
  maxA.outputNumber();
  cout << endl;
  cout << "Digitsum: " << maxDigitSum << endl << endl;
  return 0;
}
