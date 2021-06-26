#ifndef PRIMELIST_H
#define PRIMELIST_H
#include <list>
#include <iostream>

using namespace std;

class PrimeList
{
  public:
    PrimeList();
    PrimeList(int primeCount);
    ~PrimeList();

    void generatePrimes(int primeCount);
    list<__int64> factorize(__int64 num);
    void print();

  protected:

  private:
    __int64* primes;
    int primeCount;
};

#endif // PRIMELIST_H
