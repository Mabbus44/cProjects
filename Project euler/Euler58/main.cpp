#include "/home/rasmsus/c++ projects/PrimeList/primelist.h"

#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  int64_t num=1;                //Number being tested in spiral
  int count=1;          //Number of numbers that have been tested
  int primeCount=0;     //Number of tested numbers that where primes
  int side=0;           //Lenght of side of square - 1
  int i;
  PrimeList n;
  int64_t maxVal=2000000000;    //Max values to check
  int64_t outputCount=1;        //Number of times status have been outputted +1
  double primePart;     //Percentage of numbers that have been primes
  
  while(num<maxVal && !(primeCount>0 && (count-1)/primeCount>=10)){
    side+=2;
    for(i=0; i<4; i++){
      num+=side;
      count++;
      if(n.isPrime(num))
        primeCount++;
      if(num>(maxVal/10*outputCount))
      {
        outputCount++;
        primePart = (double)primeCount / (double)count * 100;
        cout << "Num: " << num << endl;
        cout << "Tested numbers: " << count << endl;
        cout << "Primecount: " << primeCount << endl;
        cout << "PrimePart: " << primePart << endl;
        cout << "Side: " << side << endl;
        cout << endl;
      }
    }
  }
  primePart = (double)primeCount / (double)count * 100;
  cout << "Num: " << num << endl;
  cout << "Tested numbers: " << count << endl;
  cout << "Primecount: " << primeCount << endl;
  cout << "PrimePart: " << primePart << endl;
  cout << "Side: " << side << endl;
  cout << endl;
  n.outputBiggesTest();
  return 0;
}

