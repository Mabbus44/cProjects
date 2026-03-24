#ifndef BIGINT_H
#define BIGINT_H
#define POWER32 4294967296 // 2^32
#define MAX32 4294967295   // 32 ones

#include <vector>

// From 2026
// Saves a integer in a vector<unsigned long long>
// Only first 32 bits in each unsigned long long are used, the other 32 are used when carrying over in calculations
// Can only do the basic stuff I needed
// Also a separate function bellow that divide a number by 2 as many times as possible, and returns the power of 2
class BigInt
{
    public:
        BigInt();
        BigInt(int num);
        virtual ~BigInt();
        void operator=(int other);
        void operator=(BigInt other);
        bool operator<(BigInt& other);
        bool operator>(BigInt& other);
        bool operator==(BigInt& other);
        BigInt& operator++();
        BigInt operator*(BigInt other); //Shouldent argument and return type be references? Maybe not return type since its created in the method, but at least argument.
        BigInt& operator+=(BigInt& other);
        BigInt& operator+=(unsigned long long& other);
        void output();
        int len() {return data.size();}

    protected:

    private:
        void addToData(int dataId, unsigned long long num);
        std::vector<unsigned long long> data;   // 32 bits used in each
};

int reduceTwos(unsigned long long& num);
int factorizeList();
std::vector<unsigned long long> factorizeNum(unsigned long long num, std::vector<unsigned long long>& primes, unsigned long long primeCount);
#endif // BIGINT_H
