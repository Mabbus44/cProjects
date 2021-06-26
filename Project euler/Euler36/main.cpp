#include <iostream>

int main(int argc, char **argv) {
  int* digits=new int[7];				//digits in tested number
  int digitCount;					//number of digits in tested number
  int num;						//used for extraction of digits
  int lastDigit, firstDigit;				//index of first and last digits
  int sum;						//sum of all palindroms
  bool isPalindrom;					//tracks if number i is palindrom
  
  sum=0;
  for(int i=1; i<1000000; i++)
  {
    digitCount=0;
    num=i;
    while(num>0)					//repeat until all digits added to array
    {
      digits[digitCount]=num-(num/10)*10;		//add last digit in num to list
      digitCount++;
      num=num/10;
      if(digitCount==7 && num>0)			//check that num is not to big
      {
	std::cout << std::endl << "Error, number with more then 7 digits" << std::endl;
	return 0;
      }
    }
    isPalindrom=true;					//number is palindrom until proven otherwise
    firstDigit=0;					//index of first digit
    lastDigit=digitCount-1;				//index of last digit
    while(firstDigit <= lastDigit)			//test if firstdigit=last digit until the middle of the number is passed
    {
      if(digits[firstDigit]!=digits[lastDigit])
	isPalindrom = false;
      firstDigit++;
      lastDigit--;
    }
    digitCount=0;					//calculate digitCount for binary number
    while(i>>digitCount > 0)				//Shift the number right until digitCount is figured out
      digitCount++;
    firstDigit=0;					//index of first digit
    lastDigit=digitCount-1;				//index of last digit
    while(firstDigit <= lastDigit)			//test if firstdigit=last digit until the middle of the number is passed
    {
      if(((1<<firstDigit)&i)>>firstDigit != ((1<<lastDigit)&i)>>lastDigit)
	isPalindrom = false;
      firstDigit++;
      lastDigit--;
    }
    if(isPalindrom)
    {
      sum+=i;
      std::cout << "palindrom found: " << i << std::endl;
    }
  }
  std::cout << "sum of palindroms: " << sum << std::endl;
  return 0;
}
