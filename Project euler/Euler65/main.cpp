#include <iostream>
#include <list>
#include "PrimeList.h"
#include "Fraction.h"

using namespace std;

int main()
{
  __int64* ek = new __int64 [100];
  PrimeList p(1000000);
  for(int iterations = 30; iterations<40; iterations++){
  __int64 k = 2;
  int i=1;
  ek[0] = 2;
  while(i<100){
    ek[i] = 1;
    i++;
    if(i<100)
      ek[i] = k;
    k+=2;
    i++;
    if(i<100)
      ek[i] = 1;
    i++;
  }
  Fraction f1(&p, ek[iterations-1], 1);
  Fraction f2(&p, 1, 1);
  for(i=iterations-2; i>=0; i--){
    f1.invert();
    f2.setInteger(ek[i]);
    f1 = f1+f2;
    f1.eliminate();
  }
  f1.print();
  }
  return 0;
}
