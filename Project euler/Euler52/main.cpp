#include <iostream>
#include <stdint.h>

#ifndef XCOUNT
#define XCOUNT 6
#endif


class Number
{
private:
  bool debug;
  int number;					//The number being tested

  int digit2Num();				//Converts digit to a intiger
  bool num2Digit();				//Converts number to digits

public:
  int8_t* digits;				//DigitsInNumber
  int digitCount;				//DigitCount in number

  Number();					//Default
  bool compare(Number other);			//Compares if two number is the same
  bool setNumber(int number);			//Sets number
};





Number::Number()
{
  debug=false;
  digitCount=0;
  number=0;
}





int Number::digit2Num()
{
/*  if(this->debug)
  {
    std::cout << "digit2Num()" << std::endl;
  }*/
  int number=0;
  int factor=1;
  for(int i=0; i<this->digitCount; i++)		//Converts digits to number
  {
    number+=this->digits[i]*factor;
    factor*=10;
/*    if(this->debug)
    {
      std::cout << (int)(this->digits[i]);
    }*/
  }
  if(this->debug)
  {
    std::cout << "Number: " << number << std::endl;
  }
  return number;
}





bool Number::num2Digit()
{
/*  if(this->debug)
  {
    std::cout << "num2Digit()" << std::endl;
    std::cout << "number: " << this->number << std::endl;
    std::cout << "digitCount: " << this->digitCount << std::endl;
  }*/
  int number = this->number;
  for(int i=0; i<this->digitCount; i++)		//Set new digits to desider number
  {
    this->digits[i] = number-(number/10)*10;
    number/=10;
/*    if(this->debug)
    {
      std::cout << (int)(this->digits[i]);
    }*/
  }
  /*if(this->debug)
  {
    std::cout << std::endl;
  }*/
  return true;
}





bool Number::compare(Number other)			//Compares if two number is the same
{
  bool ans;
  int digitCount;
  int8_t* digits1;				//DigitsInNumber1
  int8_t* digits2;				//DigitsInNumber2
  int i,i2,i3;
  if(this->debug)
  {
    std::cout << "compare" << std::endl;
  }
  if(this->digitCount<1)
  {
    std::cout << "Error, cannot compare when digitCount<1" << std::endl;
    return false;
  }
  if(this->digitCount != other.digitCount)
    return false;
  digitCount = this->digitCount;
  digits1 = new int8_t[digitCount];
  digits2 = new int8_t[digitCount];
  for(i=0; i<digitCount; i++)
  {
    digits1[i] = this->digits[i];
    digits2[i] = other.digits[i];
  }
  for(i=0; i<this->digitCount; i++)
  {
    i2=0;
    while(i2 < digitCount && digits1[i]!=digits2[i2])
    {
      if(this->debug)
      {
	std::cout << (int)(digits1[i]) << " & " << (int)(digits2[i2]) << " are not the same" << std::endl;
      }
      i2++;
    }
    if(i2==digitCount)
    {
      if(this->debug)
      {
	std::cout << (int)(digits1[i]) << " was not found in digits2" << std::endl;
      }
      delete [] digits1;
      delete [] digits2;
      return false;
    }
    else
    {
      if(this->debug)
      {
	std::cout << "digits2 are now: ";
      }
      for(i3=i2; i3<digitCount-1; i3++)
      {	
	digits2[i3] = digits2[i3+1];
      }
      digitCount--;
      if(this->debug)
      {
	for(int debugVar=0; debugVar<digitCount; debugVar++)
	std::cout << (int)(digits2[debugVar]);
	std::cout << std::endl;
      }
    }
  }
  delete [] digits1;
  delete [] digits2;
  return true;
}





bool Number::setNumber(int number)
{
  if(this->debug)
  {
    std::cout << "setNumber(" << number << ")" << std::endl;
  }
  int digitCount;				//Digitcount in new number
  if(number<1)					//Give error if digitCount is outside bounds
  {
    std::cout << std::endl << std::endl << "Error: Number outside bounds: " << number << std::endl << std::endl;
    return false;
  }
  this->number = number;			//Set number to desired number
  digitCount = 0;				//Count digits in "number"
  while(number>0)				//
  {
    number/=10;
    digitCount++;
  }
  if(digitCount!=this->digitCount && digits)					//Delete old digits
  {
    if(this->debug)
    {
      std::cout << "Old digits deleted" << std::endl;
    }
    delete[] digits;
  }
  if(digitCount!=this->digitCount)		//Allocate memory for new digits
  {
    digits = new int8_t[digitCount];		
    if(this->debug)
      if(digits)
	std::cout << "New digits created" << std::endl;
      else
	std::cout << "New digits could not be created" << std::endl;
  }
  this->digitCount = digitCount;		//Set digitCount to desired number
  this->num2Digit();				//Set digits
  return true;
}





int main(int argc, char **argv)
{
  Number* num;
  int numInt;
  bool finiched=false;
  num = new Number[XCOUNT];
  std::cout << "Start" << std::endl;
  numInt=0;
  while(!finiched && numInt<200000)
  {
    numInt++;
    if(numInt%100==0)
      std::cout << "numInt: " << numInt << std::endl;
    for(int i=0; i<XCOUNT;  i++)
      num[i].setNumber(numInt*(i+1));
    finiched=true;
    for(int i=0; i<XCOUNT-1;  i++)
      if(!num[i].compare(num[i+1]))
	finiched=false;
  }
  std::cout << "Answer: " << numInt << std::endl;
  std::cout << "Stopp" << std::endl;
  delete[] num;
  return 0;
}
