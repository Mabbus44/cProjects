#include <iostream>

int main(int argc, char **argv) {
  int num;				//Number being checked
  int num2;				//Used for calculation of sum
  int digit;				//One digit in number
  int digVal;				//digit! (digit*(digit-1)*(digit-2)...*2*1)
  int sum;				//Sum of all digits in a number
  int totSum;				//Sum of all sums
  int i;				//Used for loops
  
  totSum=0;				//Total sum of all sums = 0
  for(num=3; num<10000000; num++)	//Go througth 3-9 999 999
  {
    sum=0;				//Sum of digits starts at 0
    num2=num;				//num2 = num
    while(num2!=0)			//While num2!=0
    {
      digit=num2-(num2/10)*10;	//Digit = last digit in num2
      num2/=10;			//Last digit in num2 is removed
      switch(digit){
	case 0:
	  digVal=1;
	  break;
	case 1:
	  digVal=1;
	  break;
	case 2:
	  digVal=2;
	  break;
	case 3:
	  digVal=6;
	  break;
	case 4:
	  digVal=24;
	  break;
	case 5:
	  digVal=120;
	  break;
	case 6:
	  digVal=720;
	  break;
	case 7:
	  digVal=5040;
	  break;
	case 8:
	  digVal=40320;
	  break;
	case 9:
	  digVal=362880;
	  break;
	default:
	  std::cout << "Error, digVal = " << digVal << std::endl;	    
      }												//switch end
      sum+=digVal;
    }												//while end    
    //std::cout << "Num: " << num;
    //std::cout << " : " << sum << std::endl;
    if(sum==num)										//If sum of all digits! == number
    {
      totSum+=sum;										//Add sum to totSum
      std::cout << "New sum: " << sum << std::endl;
    }
  }												//for end
  std::cout << "Total sum: " << totSum << std::endl;
  return 0;
}
