#include "PrimeList.h"
#include <iostream>
#include <list>

using namespace std;

PrimeList::PrimeList()
{
  primes = nullptr;
}

PrimeList::PrimeList(int primeCount)
{
  primes = nullptr;
  generatePrimes(primeCount);
}

PrimeList::~PrimeList()
{
  if(primes){
    //cout << "Primes " << primes << " deleted" << endl;
    delete[] primes;
  }
}

void PrimeList::generatePrimes(int primeCount){
  this->primeCount = primeCount;
  if(primes)
    delete[] primes;
  primes = new __int64 [primeCount];
  //cout << "Primes " << primes << " generated" << endl;
  int c=1;
  __int64 num=3;
  int testIndex;
  bool isPrime;
  primes[0] = 2;
  while(c<primeCount){
    testIndex = 0;
    isPrime = true;
    while(isPrime && primes[testIndex]*primes[testIndex] <= num){
      if(num%primes[testIndex] == 0)
        isPrime = false;
      testIndex++;
    }
    if(isPrime){
      primes[c] = num;
      c++;
    }
    num+=2;
  }
}

list<__int64> PrimeList::factorize(__int64 num){
  int index = 0;
  list<__int64> factors;
  if(num>primes[primeCount-1]*primes[primeCount-1]){
    std::cout << "Warning: " << num << " is to big to factorize, more primes needed" << std::endl;
    return factors;
  }
  while(primes[index]*primes[index] <= num){
    if(num%primes[index]==0){
      factors.push_back(primes[index]);
      num/=primes[index];
    }
    else
      index++;
  }
  factors.push_back(num);
  return factors;
}

void PrimeList::print(){
  for(int i=0; i<primeCount; i++){
    std::cout << primes[i] << ",";
  }
  std::cout << std::endl;
}
