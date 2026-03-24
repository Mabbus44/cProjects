#include "BigInt.h"
#include "OutputSelected.h"
#include<iostream>
#include<list>

BigInt::BigInt()
{
    data.clear();
    data.push_back(0);
}

BigInt::BigInt(int num)
{
    data.clear();
    data.push_back(num);
}

BigInt::~BigInt()
{
    //dtor
}

void BigInt::operator=(int other){
    data.clear();
    data.push_back(other);
}

void BigInt::operator=(BigInt other){
    data = other.data;
}

bool BigInt::operator<(BigInt& other){
    if(data.size() > other.data.size())
        return false;
    if(data.size() < other.data.size())
        return true;
    for(int i=data.size()-1; i>=0; i--){
        if(data[i] > other.data[i])
            return false;
        if(data[i] < other.data[i])
            return true;
    }
    return false;
}

bool BigInt::operator>(BigInt& other){
    if(data.size() > other.data.size())
        return true;
    if(data.size() < other.data.size())
        return false;
    for(int i=data.size()-1; i>=0; i--){
        if(data[i] > other.data[i])
            return true;
        if(data[i] < other.data[i])
            return false;
    }
    return false;
}

bool BigInt::operator==(BigInt& other){
    if(data.size() != other.data.size())
        return false;
    for(int i=data.size()-1; i>=0; i--){
        if(data[i] != other.data[i])
            return false;
    }
    return true;
}

BigInt& BigInt::operator++(){
    addToData(0, 1);
    return *this;
}

BigInt BigInt::operator*(BigInt other){
    BigInt ret;
    for(int a=0; a<(int)data.size(); a++)
        for(int b=0; b<(int)other.data.size(); b++)
            ret.addToData(a+b, data[a]*other.data[b]);
    return ret;
}

BigInt& BigInt::operator+=(BigInt& other){
    for(int i=0; i<(int)other.data.size(); i++)
        addToData(i, other.data[i]);
    return *this;
}

BigInt& BigInt::operator+=(unsigned long long& other){
    addToData(0, other);
    return *this;
}

void BigInt::addToData(int dataId, unsigned long long num){
    while(dataId >= (int)data.size())
        data.push_back(0);
    data[dataId] += num;
    if(data[dataId] >= POWER32){
        unsigned long long upper32Bits = (data[dataId] >> 32);      // Extract the upper 32 bits
        data[dataId] = (data[dataId] & MAX32);                      // Remove the upper 32 bits
        addToData(dataId+1, upper32Bits);                           // Add the upper 32 bits to the next data
    }
}

void BigInt::output(){
    if(data.size() == 0){
        std::cout << "0";
        return;
    }
    for(int i=data.size()-1; i>=0; i--){
        std::cout << data[i];
        if(i!=0)
            std::cout << ",";
    }
}

int reduceTwos(unsigned long long& num){
  // If you have 64 bits, and the highest bit is set, it can maximum move 63 steps
  // So we let it do 64 steps, if it did the 64th the number must be zero.
  int twoCount = 0;
  while(!(num & 1) && twoCount < 64){
    ++twoCount;
    num = (num >> 1);
  }
  if(twoCount == 64)
    return 0;
  return twoCount;
}

int factorizeList(){
  OutputSelected output, output2;
  std::vector<unsigned long long> primes;
  primes.resize(450000000);
  primes[0] = 2;
  primes[1] = 3;
  unsigned long long lastPrime = 3;
  unsigned long long testNum = 5;
  unsigned long long primeCount = 2;
  while(lastPrime <4294967296){
    unsigned long long pid = 0;
    bool isPrime = true;
    while(pid != primeCount && isPrime && primes[pid]*primes[pid] <= testNum){
      if(testNum%primes[pid] == 0)
        isPrime = false;
      pid++;
    }
    if(isPrime){
      primes[primeCount] = testNum;
      lastPrime = testNum;
      primeCount++;
    }
    testNum +=2;
    output.output(testNum, "testNum: ");
    output2.output(primeCount, "primeCount: ");
  }

  std::vector<unsigned long long> numbers =
// d, k, dk + or - 2 (1 means 1, 2 means +2)
{2, 1, 2,
3, 1, 2,
5, 2, 2,
7, 1, 1,
11, 1, 2,
13, 50, 2,
17, 2, 2,
19, 9, 2,
23, 1, 1,
29, 338, 2,
31, 49, 1,
37, 2, 2,
41, 50, 2,
43, 81, 2,
47, 1, 1,
53, 1250, 2,
59, 9, 2,
61, 28956050, 2,
67, 729, 2,
71, 49, 1,
73, 31250, 2,
79, 1, 1,
83, 1, 2,
89, 5618, 2,
97, 647522, 2,
101, 2, 2,
103, 2209, 1,
107, 9, 2,
109, 1450189651250, 2,
113, 10658, 2,
127, 37249, 1,
131, 81, 2,
137, 44402, 2,
139, 558009, 2,
149, 173166050, 2,
151, 11444689, 1,
157, 297444132050, 2,
163, 393129, 2,
167, 1, 1,
173, 14450, 2,
179, 23409, 2,
181, 13644449855382200, 1,
191, 47089, 1,
193, 32250380450, 2,
197, 2, 2,
199, 81739681, 1,
211, 1319215041, 2,
223, 1, 1,
227, 1, 2,
229, 25538, 2,
233, 4602578, 2,
239, 25921, 1,
241, 41847068701250, 2,
251, 14641, 2,
257, 2, 2,
263, 529, 1,
269, 50, 2,
271, 427951969, 1,
281, 8050536050, 2,
283, 488601, 2,
293, 42050, 2,
307, 288369, 2,
311, 54289, 1,
313, 102837446738450, 2,
317, 784476050, 2,
331, 8415679158441, 2,
337, 6124066329761760, 1,
347, 1849, 2,
349, 486098, 2,
353, 28773698, 2,
359, 1, 1,
367, 51825601, 1,
373, 140450, 2,
379, 34145639104329, 2,
383, 49, 1,
389, 8450, 2,
401, 2, 2,
419, 644809, 2,
431, 351649, 1,
439, 1, 1,
443, 1, 2,
449, 159908176614050, 2,
461, 2564754642482, 2,
463, 534584709409, 1,
467, 3481, 2,
479, 6241, 1,
487, 106583313841, 1,
491, 190688481, 2,
499, 9, 2,
503, 49, 1,
509, 615326563501778, 2,
521, 63265703454962, 2,
523, 156425049, 2,
547, 292829252769, 2,
557, 50, 2,
563, 121, 2,
569, 29456016189180000, 2,
577, 2, 2,
587, 3249, 2,
593, 1216724450, 2,
599, 41212654081, 1,
607, 270306481, 1,
617, 5451529356242, 2,
619, 835563021895449, 1,
643, 3093250689, 2,
647, 185761, 1,
653, 16079611896902400, 2,
659, 9, 2,
677, 2, 2,
683, 249001, 2,
701, 396050, 2,
709, 939044674178, 2,
719, 561168721, 1,
727, 1, 1,
733, 266450, 2,
743, 961, 1,
757, 4953906722, 2,
761, 1682, 2,
773, 4666746050, 2,
787, 43996689, 2,
797, 1532947970450, 2,
811, 1704158031539600, 2,
827, 1089, 2,
829, 578812682450, 2,
839, 1, 1,
857, 153818311250, 2,
863, 21464689, 1,
877, 132812402, 2,
887, 529, 1,
911, 408158710129, 1,
941, 1135945702433520, 2,
947, 14265729, 2,
953, 15834765838048600, 2,
967, 4808203265581680, 1,
971, 12852530161, 2,
983, 289, 1,
997, 14461442, 2,
997, 14461442, 2};
  std::cout << "Prime factors for k" << std::endl;
  for(unsigned long long numId=0; numId<numbers.size(); numId+=3){
    std::vector<unsigned long long> factors = factorizeNum(numbers[numId+1], primes, primeCount);
    std::cout << numbers[numId] << ": ";
    if(factors.size() == 0)
      std::cout << "1";
    for(auto f: factors)
      std::cout << f << " ";
    std::cout << std::endl;
  }

  std::cout << std::endl << "Prime factors for kd+2 or kd-2" << std::endl;
  for(unsigned long long numId=0; numId<numbers.size(); numId+=3){
    unsigned long long numToFactorize;
    if(numbers[numId+2] == 2)
      numToFactorize = numbers[numId] * numbers[numId+1] - 2;
    else
      numToFactorize = numbers[numId] * numbers[numId+1] + 2;
    std::vector<unsigned long long> factors = factorizeNum(numToFactorize, primes, primeCount);
    std::cout << numbers[numId] << ": ";
    if(factors.size() == 0)
      std::cout << "1";
    for(auto f: factors)
      std::cout << f << " ";
    std::cout << std::endl;
  }
  return 0;
}

std::vector<unsigned long long> factorizeNum(unsigned long long num, std::vector<unsigned long long>& primes, unsigned long long primeCount){
  std::vector<unsigned long long> factors;
  unsigned long long pid = 0;
  while(pid < primeCount && primes[pid] * primes[pid] <= num){
    if(num%primes[pid] == 0){
      factors.push_back(primes[pid]);
      num /= primes[pid];
    }
    else{
      pid++;
    }
  }
  if(pid == primeCount)
    std::cout << "Warning! Primes ran out when factorizing " << num << std::endl;
  if(num > 1)
    factors.push_back(num);
  return factors;
}
