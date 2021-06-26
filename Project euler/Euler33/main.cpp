#include <iostream>

void eliminate(int* numerator, int* denominator);

int main(int argc, char **argv) {
    int numerator;
    int denominator;
    int i;
    int num1, num2, den1, den2;
    
    for(numerator=10;numerator<100;numerator++)
    {
      for(i=1; i<10; i++)
      {
	denominator=(numerator%10)*10+i;
	num1=numerator;
	num2=numerator/10;
	den1=denominator;
	den2=i;
	eliminate(&num1, &den1);
	eliminate(&num2, &den2);
	if(num1==num2 && den1==den2 && numerator!=denominator)
	  std::cout << numerator << "/" << denominator << std::endl;
      }
    }
    return 0;
}


void eliminate(int* numerator, int* denominator)
{
  int i=2;
  while(i<100)
  {
    if(*numerator%i==0 && *denominator%i==0)
    {
      *numerator/=i;
      *denominator/=i;
    }
    else
      i++;
  }
}