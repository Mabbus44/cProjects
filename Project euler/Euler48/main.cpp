#include <iostream>
#include <stdint.h>


int main(int argc, char **argv) {
  int64_t sumA, totSum;
  
  totSum=0;
  for(int64_t i=1; i<=1000; i++)
  {
    sumA=i;
    for(int64_t i2=2; i2<=i; i2++)
    {
      sumA*=i;
      sumA=sumA-sumA/10000000000*10000000000;			//max 10 digits
    }
    totSum+=sumA;
    std::cout << i << " : " << sumA << std::endl;
    totSum=totSum-totSum/10000000000*10000000000;			//max 10 digits
  }
  std::cout << "totSum " << totSum << std::endl;
  return 0;
}
