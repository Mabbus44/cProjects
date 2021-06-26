#include <iostream>
#include <stdint.h>

int main(int argc, char **argv)
{
  int64_t add1=1, add2=1, add3=1;
  int64_t num1=1, num2=1, num3=1;
  for(int64_t i=0; i<10000000000; i++)
  {
    while(num1<i)
    {
      add1+=1;
      num1+=add1;
    }
    while(num2<i)
    {
      add2+=3;
      num2+=add2;
    }
    while(num3<i)
    {
      add3+=4;
      num3+=add3;
    }
    if(num1==i && num2==i && num3==i)
      std::cout << i << std::endl;
  }
  std::cout << "Done" << std::endl;
  return 0;
}
