#include <iostream>
#include <vector>
#include <set>
#include <math.h>
#include <chrono>
#include <algorithm>
#include "../EulerMain/OutputSelected.h"
#include "../EulerMain/BigInt.h"

bool isSquareBabylonian(unsigned long long num);
bool isSquareBinary(unsigned long long num);
bool checkBothSquares(unsigned long long d, unsigned long long k, bool allowFactorTwos);
bool removeFactorTwos(unsigned long long& num);
int removeFactorTwosCount(unsigned long long& num);
unsigned long long pow32minus1 = 4294967295;
unsigned long long pow64minus1 = 18446744073709551615;


int main()
{
  // I come no futher with sets. I will now use an algoritm to calculate square roots instead
  // This program does not work for d=2, its a special case, so I skip it
  std::vector<unsigned long long> dVector =
    {3,5,6,8,10,12,15,18,20,24,26,28,32,38,40,45,48,50,51,52,58,60,63,65,66,72,75,76,77,78,80,82,87,92,94,95,96,102,104,105,106,111,112,115,116,117,119,122,123,124,125,128,133,148,152,153,160,166,170,172,180,185,186,192,200,203,204,208,209,210,213,217,221,232,234,236,238,240,242,244,245,246,247,249,252,254,255,260,261,262,264,273,275,278,279,285,288,290,291,292,294,295,300,303,304,305,306,308,309,312,314,315,318,319,320,322,328,334,335,339,343,348,350,351,355,356,357,358,362,365,366,368,370,371,376,380,381,382,384,385,386,387,388,390,391,399,402,403,405,406,407,408,411,414,415,416,417,420,422,423,424,425,426,428,429,430,434,436,437,438,442,444,445,446,448,450,451,452,458,460,464,465,466,468,469,470,471,473,474,475,476,478,485,486,488,489,490,492,493,494,496,497,498,500,505,507,508,510,511,512,515,525,527,531,532,534,539,546,549,550,555,556,558,561,562,566,570,573,574,578,581,583,585,590,592,594,596,597,605,608,609,610,611,612,614,615,621,623,627,629,630,638,639,640,652,654,655,658,664,667,674,678,680,682,687,688,689,690,694,695,703,706,710,713,715,720,723,734,735,738,740,744,745,750,753,754,759,762,763,768,772,775,779,783,786,788,790,791,794,798,800,812,816,818,822,831,832,836,838,840,843,844,845,846,847,851,852,865,868,869,870,871,873,874,882,884,886,890,891,894,897,902,903,906,909,914,916,917,918,922,923,928,932,934,935,936,938,939,943,944,946,952,954,958,960,962,963,964,966,968,970,975,976,979,980,984,985,986,988,989,990,994,995,996,999};

    // All non primes {6,8,10,12,15,18,20,24,26,28,32,38,40,45,48,50,51,52,58,60,63,65,66,72,75,76,77,78,80,82,87,92,94,95,96,102,104,105,106,111,112,115,116,117,119,122,123,124,125,128,133,148,152,153,160,166,170,172,180,185,186,192,200,203,204,208,209,210,213,217,221,232,234,236,238,240,242,244,245,246,247,249,252,254,255,260,261,262,264,273,275,278,279,285,288,290,291,292,294,295,300,303,304,305,306,308,309,312,314,315,318,319,320,322,328,334,335,339,343,348,350,351,355,356,357,358,362,365,366,368,370,371,376,380,381,382,384,385,386,387,388,390,391,399,402,403,405,406,407,408,411,414,415,416,417,420,422,423,424,425,426,428,429,430,434,436,437,438,442,444,445,446,448,450,451,452,458,460,464,465,466,468,469,470,471,473,474,475,476,478,485,486,488,489,490,492,493,494,496,497,498,500,505,507,508,510,511,512,515,525,527,531,532,534,539,546,549,550,555,556,558,561,562,566,570,573,574,578,581,583,585,590,592,594,596,597,605,608,609,610,611,612,614,615,621,623,627,629,630,638,639,640,652,654,655,658,664,667,674,678,680,682,687,688,689,690,694,695,703,706,710,713,715,720,723,734,735,738,740,744,745,750,753,754,759,762,763,768,772,775,779,783,786,788,790,791,794,798,800,812,816,818,822,831,832,836,838,840,843,844,845,846,847,851,852,865,868,869,870,871,873,874,882,884,886,890,891,894,897,902,903,906,909,914,916,917,918,922,923,928,932,934,935,936,938,939,943,944,946,952,954,958,960,962,963,964,966,968,970,975,976,979,980,984,985,986,988,989,990,994,995,996,999}
    // All primes {3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997}
    // Easy {2,3,7,11,23,47,79,83,167,223,227,359,439,443,727,839,5,17,37,101,197,257,401,577,677,19,59,107,499,659,31,71,383,503,13,41,269,557,43,131,563,983,29,263,887,67,743,827,53,761,347,103,587,467,89,479,389,113,173,251,179,229,239,73,127,293,137,191,311,373,647,683,733,307,431,163,701,349,283,139,419,97,233,151,947,997,863,353,61,787,367,199,877,523,149,491,607,271,719,317,593,211,643,773,757,281,971,193,599,487,857,547,157,911,463,829,709,109,797,461,617,331,379,241,521,313,449,509,619}
    // Hard {941,811,967,337,181,953,653,569}
    // Unsolved {277,397,409,421,433,457,541,571,601,613,631,641,661,673,691,739,751,769,809,821,823,853,859,881,883,907,919,929,937,977,991}

  auto start = std::chrono::system_clock::now();
  for(unsigned long long d: dVector){
    unsigned long long oddNumAdd = 8;
    unsigned long long oddNumSquare = 1;            // k
    unsigned long long oddNum2Add = 16;
    unsigned long long oddNum2SquareTimesTwo = 2;    // also k

    //unsigned long long k=1;

    unsigned long long maxK = (18446744073709551615 -2)/d;
    bool done = false;
    while(!done){

      /* All K
      unsigned long long kCopy=k;
      int twoCount = removeFactorTwosCount(kCopy);
      if(isSquareBabylonian(kCopy)){
        unsigned long long xMinusOne = k * d - 2;
        unsigned long long xPlusOne = k * d + 2;
        int twoCount2 = removeFactorTwosCount(xMinusOne);
        if(isSquareBabylonian(xMinusOne)){
          int twoCountSum = twoCount+twoCount2;
          if((twoCountSum&1)==0)
            done = true;
        }
        if(!done)
          twoCount2 = removeFactorTwosCount(xPlusOne);
        if(!done && isSquareBabylonian(xPlusOne)){
          int twoCountSum = twoCount+twoCount2;
          if((twoCountSum&1)==0)
            done = true;
        }
      }
      if(done)
        std::cout << d << " found\n";
      if(!done && maxK - 1 < k){
        std::cout << d << ": Not found!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        done = true;
      }
      ++k;*/

      // First try with unsigned long long
      if(oddNumSquare < oddNum2SquareTimesTwo){
        done = checkBothSquares(d, oddNumSquare, false);
        if(!done && maxK - oddNumAdd < oddNumSquare){
          std::cout << d << ": Not found!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
          done = true;
        }
        oddNumSquare += oddNumAdd;
        oddNumAdd += 8;
      }else{
        done = checkBothSquares(d, oddNum2SquareTimesTwo, true);
        if(!done && maxK - oddNum2Add < oddNum2SquareTimesTwo){
          std::cout << d << ": Not found!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
          done = true;
        }
        oddNum2SquareTimesTwo += oddNum2Add;
        oddNum2Add += 16;
      }


    }
  }

  std::cout << "Done" << std::endl;
  auto end = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  std::cout << "Time taken: " << elapsed.count() << " s\n";
  std::string a;
  std::cin >> a;
  return 0;
}

bool isSquareBabylonian(unsigned long long num){
  unsigned long long x = num;
  unsigned long long y = 1;
  while(x > y){
    x = ((x+y) >> 1);
    y = num / x;
  }
  return x * x == num;
}

bool isSquareBinary(unsigned long long num){
  unsigned long long left = 0;
  unsigned long long right = num;
  unsigned long long midSquared;
  while(left <= right){
    unsigned long long mid = ((left + right) >> 1);
    if(mid<=pow32minus1)
      midSquared = mid*mid;
    else
      midSquared = pow64minus1;
    if (midSquared < num)
      left = mid+1;
    else if (midSquared > num)
      if(mid>0)
        right = mid-1;
      else
        right = 0;
    else
      return true;
  }
  if(left == right && left*left == num)
    return true;
  return false;
}

bool checkBothSquares(unsigned long long d, unsigned long long k, bool allowFactorTwos){
  unsigned long long xMinusOne = k * d - 2;
  // Only check if square if twos are allowed and the amount of twos are odd, or if twos are not allowed and the number is odd
  if((allowFactorTwos && removeFactorTwos(xMinusOne)) || (!allowFactorTwos && ((xMinusOne & 1) == 1))){
    if(isSquareBabylonian(xMinusOne)){
      std::cout <<  d << ": " << k << " (x-1): " << k * d - 2 << std::endl;
      return true;
    }
  }
  unsigned long long xPlusOne = k * d + 2;
  // Only check if square if twos are allowed and the amount of twos are odd, or if twos are not allowed and the number is odd
  if((allowFactorTwos && removeFactorTwos(xPlusOne)) || (!allowFactorTwos && ((xPlusOne & 1) == 1))){
    if(isSquareBabylonian(xPlusOne)){
      std::cout <<  d << ": " << k << " (x+1): " << k * d + 2 << std::endl;
      return true;
    }
  }
  return false;
}

// Removes all factor twos from num. Returns true if the number of twos are odd
bool removeFactorTwos(unsigned long long& num){
  int c = 0;
  while((num & 1) == 0){
    ++c;
    num = num >> 1;
  }
  return ((c & 1) == 1);
}

// Removes all factor twos from num. Returns the number of twos
int removeFactorTwosCount(unsigned long long& num){
  int c = 0;
  while((num & 1) == 0){
    ++c;
    num = num >> 1;
  }
  return c;
}
