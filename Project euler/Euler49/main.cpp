#include <iostream>


class TestPrime
{
private:
  int primes[10000];				//all primes < 1500
  int primeCount;				//number of primes <1500
  int error;					//holds last error code
public:
  int combinations[24];				//Combinations of 4 digits
  int ocupiedCombinations;			//Number of currently saved compinations
  TestPrime();					//creates list with primes<1000 at creation
  void outputPrimes();				//outputs all primes in list to terminal				
  bool isPrime(int num);			//tests if num is prime
  bool pandigitalCheck(int* digits, int digitCount, int num);	//Checks if number is a circular prime (if the digits in any order is prime, example 197, 179, 917, 971, 719, 791)
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
  ocupiedCombinations=0;
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




bool TestPrime::pandigitalCheck(int* digits, int digitCount, int num)	//Checks if number is a circular prime
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
      pandigitalCheck(digits2, digitCount2, num2);		//Perform pandigital check on new num and array
    }
    delete[] digits2;						//Relese array
  }
  else
  {
    num=num*10+digits[0];
    if(this->isPrime(num))					//Of only 1 digit then check if it is a prime
    {
      if(ocupiedCombinations>=24)
      {
	error=4;
	outputError();
      }
      else
      {
	combinations[ocupiedCombinations]=num;
	ocupiedCombinations++;
      }
    }
  }
  return isPrime;						//Return true if all compinations of num+digits is primes
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
    case 4:
      std::cout << std::endl << "To many primes from number combinations" << std::endl << std::endl;
      break;
    default:
      std::cout << std::endl << "Unknown error" << std::endl << std::endl;
      break;
  }
  return lastError;
}




int main(int argc, char **argv) {
  TestPrime testPrime;
  int* digits = new int[4];
 

  for(int d1=0; d1<10; d1++)
  {
    for(int d2=0; d2<10; d2++)
    {
      for(int d3=0; d3<10; d3++)
      {
	for(int d4=0; d4<10; d4++)
	{
	  digits[0] = d1;
	  digits[1] = d2;
	  digits[2] = d3;
	  digits[3] = d4;
	  
	  testPrime.ocupiedCombinations=0;
	  testPrime.pandigitalCheck(digits, 4, 0);
	  if(testPrime.ocupiedCombinations>2)
	  {
	    for(int i=0; i<testPrime.ocupiedCombinations-1; i++)
	    {
	      for(int i2=0; i2<testPrime.ocupiedCombinations; i2++)
	      {
		for(int i3=0; i3<testPrime.ocupiedCombinations; i3++)
		{
		  if(testPrime.combinations[i]-testPrime.combinations[i2] == testPrime.combinations[i3]-testPrime.combinations[i] && testPrime.combinations[i] != testPrime.combinations[i2])
		  {
		    std::cout << testPrime.combinations[i2] << " : " << testPrime.combinations[i] << " : " << testPrime.combinations[i3] << std::endl;
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
  
  delete[] digits;

/*  std::cout << "Number of primes " << testPrime.ocupiedCombinations << std::endl;
  for(int i=0; i<testPrime.ocupiedCombinations; i++)
    std::cout << i << ": " << testPrime.combinations[i] << std::endl;*/
    
  return 0;
}