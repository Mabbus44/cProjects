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
public:
  bool showStats;				//Show some text output
  TestPrime();					//creates list with primes<1000 at creation
  void outputPrimes();				//outputs all primes in list to terminal				
  bool isPrime(int num);			//tests if num is prime
  int outputError();				//Outputs and regurns last error
  int factorCount(int num);				//Return number of distinct factors
};




TestPrime::TestPrime()				//creates list of all primes < 1500
{
  primes[0]=2;					//first prime
  primeCount=1;					//1 prime so far
  for(int i=3; i<35000 && primeCount<PRIMECOUNT; i++)			//test if numbers 3-999 is primes
  {
    if(isPrime(i))					//if i is prime, add it to list
    {
      primes[primeCount]=i;
      primeCount++;
    }
  }						//end for
  error=0;
  if(primeCount>=PRIMECOUNT)
  {
    error=3;
    this->outputError();
    error=3;
  }
  showStats=false;
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




int TestPrime::factorCount(int num)				//Return number of distinct factors
{
  int factorCount=0;
  int i=0;
  int num2=num;
  
  while(i < primeCount && primes[i]*primes[i]<=num)
  {
    if(num2%primes[i] == 0)
      factorCount++;
    while(num2%primes[i] == 0)
    {
      if(showStats)
	std::cout << primes[i] << " ";
      num2/=primes[i];
    }
    i++;
  }
  if(num2!=1)
  {
    if(showStats)
      std::cout << num2 << " ";
    factorCount++;
  }
  if(i==primeCount)
  {
    error=1;
    outputError();
  }
  return factorCount;
}




int main(int argc, char **argv) {
  TestPrime testPrime;
  int t=10;
  int factorsInARow=0;
  
  while(factorsInARow<4)
  {
    if(testPrime.factorCount(t)==4)
      factorsInARow++;
    else
      factorsInARow=0;
    t++;
  }
  t--;
  std::cout << "last number: " << t << std::endl;
  testPrime.showStats = true;
  for(int i=t-3; i<=t; i++)
    std::cout << "= " << i << " and has " << testPrime.factorCount(i) << " distinct factors" << std::endl;
  return 0;
}