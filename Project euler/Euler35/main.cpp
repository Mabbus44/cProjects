#include <iostream>


class TestPrime
{
private:
  int primes[1000];				//all primes < 1000
  int primeCount;				//number of primes <1000
  int error;					//holds last error code
public:
  TestPrime();					//creates list with primes<1000 at creation
  void outputPrimes();				//outputs all primes in list to terminal				
  bool isPrime(int num);			//tests if num is prime
  bool circularCheck(int* digits, int digitCount, int num);	//Checks if number is a circular prime (if the digits in any order is prime, example 197, 179, 917, 971, 719, 791)
  bool circularCheck2(int num);	//Checks if number is a circular prime (if the digits in the same order, but with all any digits as the first digit is prime, example 179, 791, 917)
  int outputError();				//Outputs and regurns last error
};




TestPrime::TestPrime()				//creates list of all primes < 1500
{
  primes[0]=2;					//first prime
  primeCount=1;					//1 prime so far
  for(int i=3; i<1500; i++)			//test if numbers 3-999 is primes
  {
    if(isPrime(i))					//if i is prime, add it to list
    {
      primes[primeCount]=i;
      primeCount++;
    }
  }						//end for
  error=0;
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




bool TestPrime::circularCheck(int* digits, int digitCount, int num)	//Checks if number is a circular prime
{
  int* digits2;							//Digits to pass on to next instance
  int num2;							//Number to pass on to next instance
  int digitCount2;						//Digit count to pass on to the next instance
  bool isPrime=true;						//If checked number is prime
  
  if(digitCount>1)						//If there are more then 1 digit
  {
    digits2 = new int[digitCount-1];				//Digits for next instance is 1 fewer
    for(int i=0; i<digitCount && isPrime; i++)				//Cycle throu which digit should be next in the number
    {
      digitCount2=0;
      for(int i2=0; i2<digitCount && isPrime; i2++)				//Add the rest of the digit to new array
      {
	if(i==i2)						
	  num2=num*10+digits[i2];				//Add one digit to number
	else
	{
	  digits2[digitCount2]=digits[i2];					//Add the rest of the digits to array
	  digitCount2++;
	}
      }
      isPrime = isPrime && circularCheck(digits2, digitCount2, num2);		//Perform circular check on new num and array
    }
    delete[] digits2;						//Relese array
  }
  else
  {
    std::cout << "Variant: " << num*10+digits[0] << std::endl;
    isPrime = isPrime && this->isPrime(num*10+digits[0]);		//Of only 1 digit then check if it is a prime
  }
  return isPrime;						//Return true if all compinations of num+digits is primes
}




bool TestPrime::circularCheck2(int num)			//Checks if number is a circular prime
{
  int* digits=new int[10];				//digits in tested number
  int digitCount;					//number of digits in tested number
  int factor;						//used for calculation of number
  int num2;						//num2 is num with some other digit as first digit
  bool isPrime;						//if tested number is prime
  
  digitCount=0;
  while(num>0)					//repeat until all digits added to array
  {
    digits[digitCount]=num-(num/10)*10;		//add last digit in num to list
    digitCount++;
    num=num/10;
    if(digitCount==10 && num>0)			//check that num is not to big
    {
      error=2;
      outputError();
      error=2;
      delete[] digits;
      return false;
    }
  }

//  std::cout << std::endl << "Digits " << digits[0] << " " << digits[1] << " " << digits[2] << std::endl;
//  std::cout << "Digitcount " << digitCount << std::endl;
//  std::cout << "Num " << num << std::endl;

  isPrime=true;					//num is prime until proven otherwise
  for(int i=0; i<digitCount && isPrime; i++)	//cycle through all digits i num
  {
    num2=digits[i];				//first digit is digit nr i
    factor=1;
    int i2=i+1;
    if(i2>=digitCount)
      i2=0;
    while(i2!=i)				//repeat until you are back at first digit
    {
      factor*=10;
      num2+=digits[i2]*factor;			//add all other digits * factor (10,100,1000...)
      i2++;
      if(i2>=digitCount)
	i2=0;
    }
    isPrime = isPrime && this->isPrime(num2);
  }
  delete[] digits;
  return isPrime;
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
    default:
      std::cout << std::endl << "Unknown error" << std::endl << std::endl;
      break;
  }
  error=0;
  return lastError;
}




int main(int argc, char **argv) {
  TestPrime testPrime;
  int circularPrimesCount=0;				//number of circular primes
  
  for(int i=2; i<1000000; i++)
  {
    if(testPrime.circularCheck2(i))	//test if digits is circular prime
    {
      std::cout << "Circular prime: " << i << std::endl;
      circularPrimesCount++;
    }
  }
  std::cout << std::endl << "Circular prime count: " << circularPrimesCount << std::endl;
  return 0;
}