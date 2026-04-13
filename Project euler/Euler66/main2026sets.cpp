#include <iostream>
#include <vector>
#include <set>
#include <math.h>
#include "../EulerMain/OutputSelected.h"
#include "../EulerMain/BigInt.h"

int reduceTwos(unsigned long long& num);
int factorizeList();
std::vector<unsigned long long> factorizeNum(unsigned long long num, std::vector<unsigned long long>& primes, unsigned long long primeCount);

int main()
{
  // 4,294,967,296 squares found (including 0) <= 8 byte unsigned int max (no shit sherlook, ofc its the square of 2^64 = 2^32)
  // Memory will run out trying to save all squares in a vector even if we didnt have to use a custom bignumber class.
  // long long = 8 byte. 2^64-1 = 18,446,744,073,709,551,615 (18 * 10^18)

  // Dont know what I was thinking when writing lines above. I already found all 64 bit squares.
  // Ran third try all 64 bit/100 squares, 64bit/10 squares and all 64bit squares. Last one took a few hours.
  // Se text files for output
  // 64bit/100: 23 not found
  // 64bit/10:  18 not found
  // 64bit:     10 not found
  // Found bug, was missing numberOfTwosFromK. valuse above are probably worse in readlity, gonna run again.
  // Found a second bug, reduce by 2s only did 8 bits instead of 64. Dont know how these two will affect the result. Have to run again.
  // Ran again now, took perhaps 12 hours, and now its more not found :(
  // 64bit:     31 not found

  // Only run the program for prime D, since they surely are the biggest ones (trust me bro).
  factorizeList();
  return 0;
  std::set<unsigned long long> primes = {2,3,5,7,11,13,17,19,23,29,
31,37,41,43,47,53,59,61,67,71,
73,79,83,89,97,101,103,107,109,113,
127,131,137,139,149,151,157,163,167,173,
179,181,191,193,197,199,211,223,227,229,
233,239,241,251,257,263,269,271,277,281,
283,293,307,311,313,317,331,337,347,349,
353,359,367,373,379,383,389,397,401,409,
419,421,431,433,439,443,449,457,461,463,
467,479,487,491,499,503,509,521,523,541,
547,557,563,569,571,577,587,593,599,601,
607,613,617,619,631,641,643,647,653,659,
661,673,677,683,691,701,709,719,727,733,
739,743,751,757,761,769,773,787,797,809,
811,821,823,827,829,839,853,857,859,863,
877,881,883,887,907,911,919,929,937,941,
947,953,967,971,977,983,991,997};
    std::vector<unsigned long long> dVector;
    for(int i=2; i<=1000; i++){
        int squareRootN = round(sqrt(i));
        if(squareRootN*squareRootN != i && primes.find(i) != primes.end()){
            dVector.push_back(i);
        }
    }
    /* Super naive sollution
    for(int oneD: d){
        unsigned long long dd = oneD;
        unsigned long long y = 1;
        unsigned long long xx = y*y*dd+1;
        unsigned long long x = std::sqrt(xx);
        while(x*x != xx){
            y++;
            xx = y*y*dd+1;
            x = std::sqrt(xx);
        }
        std::cout << "D " << dd << " x " << x << " y " << y << std::endl;
    }*/

    /* First try
    BigInt zero(0);
    BigInt x(1);
    BigInt y(1);
    BigInt x2(1);
    BigInt y2(1);
    OutputSelected output;
    unsigned long long yAsLong = 1;
    while(dVector.size() > 1){
        for(int i=0; i<(int)dVector.size(); i++){
            //BigInt dAsBig()
            y2 = y*y*d[i];
            ++y2;
            while(x2<y2){
                ++x;
                x2 = x*x;
            }
            if(x2==y2){
                std::cout << d[i] << ": ";
                x2.output();
                std::cout << std::endl;
                dVector.erase(dVector.begin()+i);
                i--;
            }
        }
        if(output.shouldOutput(yAsLong)){
            std::cout << "Remaining after ";
            y.output();
            std::cout << " is " << dVector.size() << ": ";
            for(int i:d)
                std::cout << i << ", ";
            std::cout << std::endl;
        }
        ++y;
        yAsLong++;
        x=y;
        x2 = x*x;
    }*/

    // Second try with 64 bit int
    // This solved 794/969, so 175 not found. took a few minutes
    /*unsigned long long maxX = 4294967296; // 2^32
    unsigned long long biggestX = 0;
    unsigned long long bestD = 0;
    int maxXReachedCount = 0;
    for(unsigned long long d: dVector){
        unsigned long long x=1;
        unsigned long long x2=d+1;
        unsigned long long dx2 = 3*d;
        unsigned long long xJump = std::sqrt(d);
        if(xJump < 3)
            xJump = 1;
        else
            xJump -= 2;
        bool doneWithD = false;
        while(!doneWithD){
            while(x*x < x2 && x<maxX)
                x++;
            if(x >= maxX){
                std::cout << d << ": Max X reached" << std::endl;
                maxXReachedCount++;
                doneWithD = true;
            }else if(x*x == x2){
                std::cout << d << ": " << x;
                if(x > biggestX){
                    biggestX = x;
                    bestD = d;
                    std::cout << " (best so far)";
                }
                std::cout << std::endl;
                doneWithD = true;
            }else{
                x2 += dx2;
                dx2 += d*2;
                x += xJump;
            }
        }
    }
    std::cout << "Best d: " << bestD << std::endl;
    std::cout << "Calculated " << dVector.size() - maxXReachedCount << "/" << dVector.size() << std::endl;
    std::cout << std::endl;*/

    // Second try but with BigInt
    /*BigInt biggestX(0);
    unsigned long long bestD = 0;
    int maxXReachedCount = 0;
    for(unsigned long long d: dVector){
        BigInt x(1);
        BigInt x2(d+1);
        BigInt dx2(3*d);
        unsigned long long xJump = std::sqrt(d);
        unsigned long long dTimes2 = d*2;
        if(xJump < 3)
            xJump = 1;
        else
            xJump -= 2;
        bool doneWithD = false;
        while(!doneWithD){
            while(x*x < x2)
                ++x;
            if(x*x == x2){
                std::cout << d << ": ";
                x.output();
                if(x > biggestX){
                    biggestX = x;
                    bestD = d;
                    std::cout << " (best so far)";
                }
                std::cout << std::endl;
                doneWithD = true;
            }else{
                x2 += dx2;
                dx2 += dTimes2;
                x += xJump;
            }
        }
    }
    std::cout << "Best d: " << bestD << std::endl;
    std::cout << "Calculated " << dVector.size() - maxXReachedCount << "/" << dVector.size() << std::endl;
    std::cout << std::endl;*/

  // Third try
  // 1. Make a set of all squares of odd numbers.
  // (also made a separate set of k, this should be optimized)
  unsigned long long base = 1;
  std::set<unsigned long long> oddSquares;
  std::set<unsigned long long> possibleK;
  OutputSelected outputOddSquares;
  unsigned long long maxBase = 4294967296;
  unsigned long long maxK = maxBase /10;
  maxK = maxK * maxK;

  unsigned long long prod2= 2;
  while(prod2 < maxK){
      possibleK.insert(prod2);
      prod2 *= 2;
    }

  while(base < maxBase){
    unsigned long long prod = base*base;
    oddSquares.insert(prod);
    while(prod < maxK){
      possibleK.insert(prod);
      prod *= 2;
    }
    base += 2;
    outputOddSquares.output(base);
  }
  std::cout << "Created set of all " << oddSquares.size() << " odd squares of 64 bits" << std::endl;

  // 2. Calculate kd+2 or kd-2
  //OutputSelected outputXPlus1;
  //unsigned long long d = 109;
  for(unsigned long long d: dVector){
    unsigned long long localMaxK = 18446744073709551615/d;
    bool done = false;
    for(unsigned long long k: possibleK){
      if(k >= localMaxK)
        break;
      unsigned long long reducedK = k;
      int numberOfTwosFromK = reduceTwos(reducedK);
      for(int addVal = -2; addVal <= 2 && !done; addVal += 4){
        unsigned long long secondFactor = k * d + addVal;
        int numberOfTwos = numberOfTwosFromK + reduceTwos(secondFactor);
        if(!(numberOfTwos & 1)){
          if(oddSquares.find(secondFactor) != oddSquares.end()){
            std::cout << d << ": k=" << k << std::endl;
            done = true;
          }
        }
      }
      if(done)
        break;
    }
    if(!done)
      std::cout << d << " not fonud" << std::endl;
  }

  std::cout << "Done" << std::endl;
  std::string a;
  std::cin >> a;
  return 0;
}

// First try: Maybe a naive approach with big int will work.
// Start with y = 1, square it, multiply with D, add 1, save in y2
// Start with x = 1, square it, save in x2
// If y2 == x2 you are done
// If x2 > Y2 add one to y and recalculate y2
// If x2 < Y2 add one to x and recalculate y2

// bigInt will need
// =(int)
// =(bigInt)
// <
// >
// ==
// ++
// *

// BigInt could have a vector if unsigned long long (64 bit)
// Each element should be lower then 2^32.
// The remainder is moved to the next element (n >>> 32)
// If one element is >= 2^32 after any operation it should be truncated n & 0xFFFFFFFF

// ----------------------------------------------------------
// Second try: Better idea. Noted in the files "2026 Formulas.docx" and "2026 Calculations.xlsx" that second derivative of Dy^2+1 is 2D.
// And the derivative of x seem to converge to sqrt(D).
// So a method for iterating all values of y for a gived D with only relative simple calculations would be
// 1. Set y = 1, x = 1
// 2. Calculate x2 = Dy^2+1 (with y==1 it will be just D+1)
// 3. Set dx2 = 3D
// 4. do x++ until x*x is >= x2 (if it equals we are done, else continue)
// 5. y++
// 6. x2 += dx2
// 7. dx2 += 2D
// 8. x += a little less then sqrt(D) (to reduce the number of x++ in nest iteration).
// 9. Loop back to step 4
// Looking at it now, I dont even need to keep track of y.

// If I use bigInt this will only require
// =(int)
// =(bigInt)
// >=
// ==
// ++
// +=

// --------------------------------------------------------
// Third try: Even better. Figured out most things I understood a few years ago.
// x^2 - Dy^2 = 1   =>
// (x+1)(x-1)/D = y^2
// Set k = (x+1)/D or k = (x-1)/D   =>
// k(kd+2) = y^2  (or k(kd-1) = y^2)
// k and kd+2 can only share the factor 2. And since the factors in y^2 must appear in pairs we can say:
// 1: The number of factor 2 in k plus number of factor 2 in kd+2 must be even.
// 2: After removing all factor 2 the remainder of k and k+2 must be a even number squared.
// So if these two things are true we dont even need to calculate y^2 to know if we found a match. The biggest number will be x.

// Im not sure how to cycle k, but however I solve that I should
// 1. Make a set of all squares of odd numbers.
// 2. Calculate kd+2 or kd-2
// 3. Remove all factor 2 from k and kd+2
// 4. Check that the count of factor 2 is even
// 5. Check that what remains of k and k+2 exist in the set of odd numbers


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
