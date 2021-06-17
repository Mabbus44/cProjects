#include <iostream>
#include <stdint.h>

#ifndef PRIMECOUNT
#define PRIMECOUNT 10000
#endif

class TestPrime
{
private:
  int primes[PRIMECOUNT];				//all primes < 1500
  int primeCount;				//number of primes <1500
  int error;					//holds last error code
  int breakConjecture;
public:
  TestPrime();					//creates list with primes<1000 at creation
  void outputPrimes();				//outputs all primes in list to terminal				
  bool isPrime(int num);			//tests if num is prime
  int outputError();				//Outputs and regurns last error
};




TestPrime::TestPrime()				//creates list of all primes < 1500
{
  primes[0]=2;					//first prime
  primeCount=1;					//1 prime so far
  breakConjecture=0;
  for(int i=3; i<1000000 && primeCount<PRIMECOUNT; i+=2)			//test if numbers 3-999 is primes
  {
    if(isPrime(i))					//if i is prime, add it to list
    {
      primes[primeCount]=i;
      primeCount++;
    }
    else						//test if it breaks golbachs conjecture
    {
      bool conjectureHolds = false;
      for(int i2=0; i2<primeCount && !conjectureHolds; i2++)		//go through all primes
      {
	int i3=1;
	while(primes[i2]+2*i3*i3 <= i && !conjectureHolds)
	{
	  if(primes[i2]+2*i3*i3 == i)
	  {
	    conjectureHolds=true;
	    //std::cout << i << " = " << primes[i2] << " + 2 * " << i3 << " * " << i3 << std::endl;
	  }
	  i3++;
	}
      }
      if(!conjectureHolds && breakConjecture == 0)
      {
	breakConjecture = i;
	std::cout << "Conjecture broken: " << breakConjecture << std::endl;
      }
    }
  }						//end for
  error=0;
  if(primeCount>=PRIMECOUNT)
  {
    error=3;
    this->outputError();
    error=3;
  }
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
 
  std::cout << std::endl << "Done" << std::endl;
  return 0;
}