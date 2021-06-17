#include <iostream>
#include <stdint.h>

class TestPrime
{
private:
  int primes[10000];				//all primes < 1500
  int primeCount;				//number of primes <1500
  int error;					//holds last error code
public:
  int64_t divisibleSum;				//sum of all divisible numbers
  TestPrime();					//creates list with primes<1000 at creation
  void outputPrimes();				//outputs all primes in list to terminal				
  bool isPrime(int num);			//tests if num is prime
  bool divisibilityCheck(int* digits, int digitCount, int64_t num);	//Checks if number is a circular prime (if the digits in any order is prime, example 197, 179, 917, 971, 719, 791)
  int outputError();				//Outputs and regurns last error
};




TestPrime::TestPrime()				//creates list of all primes < 1500
{
  primes[0]=2;					//first prime
  primeCount=1;					//1 prime so far
  for(int i=3; i<35000 && primeCount<10000; i++)			//test if numbers 3-999 is primes
  {
    if(isPrime(i))					//if i is prime, add it to list
    {
      primes[primeCount]=i;
      primeCount++;
    }
  }						//end for
  error=0;
  if(primeCount>=10000)
  {
    error=3;
    this->outputError();
    error=3;
  }
  divisibleSum=0;
}




void TestPrime::outputPrimes()			//Output all primes in list
{
  std::cout << "Prime count: " << primeCount << std::endl;
  for(int i=0; i<primeCount; i++)
    std::cout << primes[i] << std::endl;
}




bool TestPrime::isPrime(int num)		//test if num is prime
{
  bool isPrime=true;				//number is prime until shown otherwise
  int i;					//for iterations
  
  if(num<2)					//2 is smallest prime
    return false;
  for(i=0; primes[i]*primes[i]<=num && isPrime && i<primeCount; i++)	//cycle through all primes < sqrt(i) or until i is not prime or until list of primes run out
  {
    if(num%primes[i]==0)			//if devisible by prime i2 then i is not prime
      isPrime=false;
  }
  if(i==primeCount)
  {
    std::cout << std::endl << "Error, prime list of " << primeCount << " primes is to small for testing number: " << num << std::endl << std::endl;
    error=1;
  }
  return isPrime;					//return if num is prime
}




bool TestPrime::divisibilityCheck(int* digits, int digitCount, int64_t num)	//Checks if number is a circular prime
{
  int* digits2;							//Digits to pass on to next instance
  int64_t num2;							//Number to pass on to next instance
  int digitCount2;						//Digit count to pass on to the next instance
  bool isDivisible=true;					//If checked number is divisible
  
  if(digitCount>1)						//If there are more then 1 digit
  {
    digits2 = new int[digitCount-1];				//Digits for next instance is 1 fewer
    for(int i=0; i<digitCount; i++)				//Cycle throu which digit should be next in the number
    {
      digitCount2=0;
      for(int i2=0; i2<digitCount; i2++)				//Add the rest of the digit to new array
      {
	if(i==i2)						
	  num2=num*10+digits[i2];				//Add one digit to number
	else
	{
	  digits2[digitCount2]=digits[i2];					//Add the rest of the digits to array
	  digitCount2++;
	}
      }
      divisibilityCheck(digits2, digitCount2, num2);		//Perform pandigital check on new num and array
    }
    delete[] digits2;						//Relese array
  }
  else
  {
    num=num*10+digits[0];
    isDivisible = isDivisible && (((num-num/1000000000*1000000000)/1000000)%2==0);		//digit 2,3,4 divisible 2
    isDivisible = isDivisible && (((num-num/100000000*100000000)/100000)%3==0);		//digit 3,4,5 divisible 3
    isDivisible = isDivisible && (((num-num/10000000*10000000)/10000)%5==0);		//digit 4,5,6 divisible 5
    isDivisible = isDivisible && (((num-num/1000000*1000000)/1000)%7==0);		//digit 5,6,7 divisible 7
    isDivisible = isDivisible && (((num-num/100000*100000)/100)%11==0);		//digit 6,7,8 divisible 11
    isDivisible = isDivisible && (((num-num/10000*10000)/10)%13==0);		//digit 7,8,9 divisible 13
    isDivisible = isDivisible && (((num-num/1000*1000)/1)%17==0);		//digit 8,9,10 divisible 17
    if(isDivisible)					//Of only 1 digit then check if it is a prime
    {
      std::cout << "Divisible: " << num << std::endl;
      divisibleSum+=num;
    }
  }
  return true;						//Return true if all compinations of num+digits is primes
}





int TestPrime::outputError()				//Outputs and regurns last error
{
  int lastError=error;
  switch(error)
  {
    case 0:
      std::cout << std::endl << "No new errors" << std::endl << std::endl;
      break;
    case 1:
      std::cout << std::endl << "Error, prime list to small for testing if number is prime" << std::endl << std::endl;
      break;
    case 2:
      std::cout << std::endl << "Error, circularCheck2 on prime with more then 10 digits" << std::endl << std::endl;
      break;
    case 3:
      std::cout << std::endl << "Prime array to small" << std::endl << std::endl;
      break;
    default:
      std::cout << std::endl << "Unknown error" << std::endl << std::endl;
      break;
  }
  return lastError;
}




int main(int argc, char **argv) {
  TestPrime testPrime;
  int* digits = new int[10];
 
  digits[0] = 1;
  digits[1] = 2;
  digits[2] = 3;
  digits[3] = 4;
  digits[4] = 5;
  digits[5] = 6;
  digits[6] = 7;
  digits[7] = 8;
  digits[8] = 9;
  digits[9] = 0;
  
  testPrime.divisibilityCheck(digits, 10, 0);
  delete[] digits;
  std::cout << std::endl << "Sum of divisible numbers " << testPrime.divisibleSum << std::endl;
  return 0;
}