#include <iostream>
#include <list>
#include "Number.h"

using namespace std;

int main(){
  int k[100];
  int m2 = 2;
  int step = 0;
  k[0] = 2;
  for(int i=1; i<100; i++){
    switch(step){
      case 0:
      case 2:
        k[i] = 1;
        break;
      case 1:
        k[i] = m2;
        m2 += 2;
        break;
    }
    step++;
    if(step>2)
      step = 0;
  }

  Number tp0;
  Number tp1;
  tp1 = k[99];
  Number tp2;
  tp2 = 1;
  for(int i=98; i>=0; i--){
    tp0 = tp1*k[i]+tp2;
    tp2 = tp1;
    tp1 = tp0;
  }
  cout << "sum: " << tp0.digitalSum() << endl;
}
