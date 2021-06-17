#include <iostream>

bool is19Pandigital(int num);				//Checks if number contains the digits 1-9 once each





bool is19Pandigital(int num)				//Checks if number contains the digits 1-9 once each
{
  bool digits[9];					//Tracks if digit 1-9 has bee used
  int digit;						//One digit in num
  
  if(num>999999999 || num<100000000)
    return false;
  for(int i=0; i<9; i++)
    digits[i]=false;
  while(num>0)					//repeat until all digits are checked
  {
    digit=num-(num/10)*10;			//add last digit in num to variable
    num=num/10;
    if(digit==0 || digits[digit-1])		//if digit was already used earlier or it was 0, return false
      return false;
    digits[digit-1]=true;			//Mark that this digit has appered once
  }
  return true;					//No duplicates, no zeros, 9 digit numbner = all digits 1-9 appere once
}





int main(int argc, char **argv)
{
  int largest=918273645;			//9, (1,2,3,4,5)
  int num;					//number to check
  for(int i=9000; i<10000; i++)			//Check number 9000-9999
  {
    num = i*100000+i*2;				//i, (1,2)
    if(is19Pandigital(num))
    {
      std::cout << "New biggest number: " << num << std::endl;
      std::cout << i << ", (1,2)" << std::endl;
      largest=num;
    }
  }
  return 0;
}
