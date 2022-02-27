#include <iostream>
#include <list>
#include <math.h>
#include <vector>
#include <set>
#include <chrono>
#include <thread>
#include <future>
#include "../EulerMain/number.h"

/*Times
start:                350 remaining 23 seconds.
pointers:             350 remaining 22 seconds.
combineAndTest:       350 remaining 19 seconds.
chrono:               350 remaining 19 seconds.
cycle through y:      500 remaining 30 seconds.
always chose last y:  500 remaining 16 seconds.
-||-                  450 remaining 1:56 seconds.
maxProd               450 remaining 1:04 seconds.
removed last recu     450 remaining 56 seconds.
cycleX no factor      350 remaining 10 seconds.
cycleX bigJump        108 done 24 seconds.
cycleX bigJmp skp div 108 done 2 seconds.
cycleX bigJmp skp div 156 done 1:17 seconds.
*/
const int64_t int64Max=9223372036854775807;
using namespace std;

list<int64_t>::iterator nextIt(list<int64_t>::iterator iter){
    return ++iter;
}

vector<int64_t>::iterator nextIt2(vector<int64_t>::iterator iter){
    return ++iter;
}

class NValue{
public:
  void setValue();
  bool operator<(const NValue& n) const;
  bool operator>(const NValue& n) const;
  bool operator==(const NValue& n) const;
  vector<list<int64_t>::iterator> factors;
  Number value;
};

class Euler66{
public:
  Euler66();
  virtual ~Euler66(){};
  void findPrimes();
  void findPrimesList();
  void findN(int64_t newMaxN);
  void findN2part(int64_t newMaxN);
  bool isPrime(int64_t num);
  bool isPrimeList(int64_t num);
  vector<int64_t>* factorize(int64_t num);
  vector<int64_t>* combineLists(vector<int64_t>* a, vector<int64_t>* b);
  bool rootable(vector<int64_t>* a);
  bool divisible(vector<int64_t>* a, vector<int64_t>* b);
  vector<int64_t>* divide(vector<int64_t>* a, vector<int64_t>* b);
  bool combineAndTest(vector<int64_t>* xp1, vector<int64_t>* xm1, vector<int64_t>* di);
  bool combineAndTest(vector<int64_t>* xp1, vector<int64_t>* xm1);
  void outputVector(vector<int64_t>* a, bool oneValue=false);
  int64_t vectorSum(vector<int64_t>* a);
  int64_t getSmallestX(vector<int64_t>* v, int64_t prodChosen, int64_t prodSkipped, int factorId, int64_t maxX);
  int solveDCycleXBigJump(int id);
  int getAnsCycleY();
  int getAnsCycleXNoFactors();
  int getAnsCycleXBigJump();
  int getAnsCycleXBigJumpSingleThread();
  int getAnsCycleXnList();
  int getAnsCycleXcalcN();
  vector<vector<int64_t>::iterator> getSmallestnFactors();
  Number getnFactorProduct(vector<vector<int64_t>::iterator>& v);
  Number getnFactorProductList(vector<list<int64_t>::iterator>& v);
  void increasenFactor(int index);
  void outputnFactors();
  void outputnValuesClass();
  void outputSinglenValuesClass(const NValue& v);
  void resetnFactors();
  int getAnsCycleXcalcNClass();
  void generateNewN(const NValue& nValue);
  vector<list<int64_t>::iterator> getLowestNValue();
  void resetNValue();
  vector<int64_t> primes = {2, 3};
  list<int64_t> primesList = {2, 3};
  vector<int64_t> notReallyPrimes = {1};
  list<int64_t> notReallyPrimesList = {1};
  vector<vector<int64_t>*> d;
  vector<int64_t> lowestX;
  vector<Number> lowestXNumber;
  vector<int64_t> sqrtD;
  int64_t x;
  int64_t y;
  int64_t maxN;
  vector<int64_t>* xp1Factors;
  vector<int64_t>* xFactors;
  vector<int64_t>* xm1Factors;
  set<int64_t> nValues;
  set<int64_t> nValuesOdd2s;
  set<int64_t> nValuesEven2s;
  vector<vector<vector<int64_t>::iterator>> nFactors;
  set<NValue> nValuesClass;
  set<NValue>::iterator nextNForTest;
  int64_t maxSafenValue;
  set<int64_t> nValuesComplete;
  void generatenValuesComplete();
  void findPrimesUpTo(int64_t maxVal);
  int getAnsCycleXBackToBasics();
};

void Euler66::generatenValuesComplete(){
  findPrimesUpTo(sqrt(maxSafenValue));
  cout << "finding n values upto " << maxSafenValue << " ... " << endl;
  nValuesComplete.insert(1);
  nValuesComplete.insert(2);
  set<int64_t>::iterator it=nValuesComplete.begin();
  int64_t outputInterval=0;
  int64_t magnitude=1;
  int64_t primeSquare;
  while(it != nValuesComplete.end()){
    vector<int64_t>::iterator primeIt=primes.begin();
    if(*it%2==0){
      if(*it <= maxSafenValue/4)
        nValuesComplete.insert(*it*4);
    }
    primeIt++;
    primeSquare = (*primeIt)*(*primeIt);
    while(primeIt!=primes.end() && *it<=maxSafenValue/primeSquare){
      nValuesComplete.insert(*it*primeSquare);
      primeIt++;
      if(primeIt!=primes.end())
        primeSquare = (*primeIt)*(*primeIt);
    }
    it++;
    outputInterval++;
    if(outputInterval==magnitude){
      magnitude *=10;
      cout << "found: " << nValuesComplete.size() << " nValues. Checking nValue " << endl << *it << endl << maxSafenValue << endl;
      outputInterval=0;
    }
  }
  cout << "Generated " << nValuesComplete.size() << " nValues" << endl;
}

void Euler66::findPrimes(){
  cout << "Finding primes... ";
  int64_t count = max((int)primes.size()*2,1000);
  int64_t p=primes.back();
  while(count>0){
    p+=2;
    if(isPrime(p)){
      primes.push_back(p);
      count--;
    }
  }
  cout << " Found " << primes.size() << endl;
}

void Euler66::findPrimesUpTo(int64_t maxVal){
  cout << "Finding primes upto " << maxVal << "... " << endl;
  primes.clear();
  primes.push_back(2);
  int64_t p=3;
  int64_t maxInterval = maxVal/100;
  int outputInterval=0;
  while(p<=maxVal){
    if(isPrime(p)){
      primes.push_back(p);
    }
    p+=2;
    outputInterval++;
    if(outputInterval==maxInterval){
      double percent = (double)p/(double)maxVal;
      cout << "p: " << (int)(percent*100) << "%" << endl;
      outputInterval=0;
    }
  }
  cout << " Found " << primes.size() << endl;
}

void Euler66::findPrimesList(){
  cout << "Finding primesList... ";
  int64_t count = max((int)primesList.size()*2,1000);
  int64_t p=primesList.back();
  while(count>0){
    p+=2;
    if(isPrimeList(p)){
      primesList.push_back(p);
      count--;
    }
  }
  cout << " Found " << primesList.size() << endl;
}

void Euler66::findN(int64_t newMaxN){
  cout << "finding n values upto " << newMaxN << " ... " << endl;
  maxN = newMaxN;
  int64_t mul;
  int64_t val;
  int64_t nBaseId=1;
  nValues.clear();
  nValues.insert(1);
  mul = 2;
  val = mul;
  while(val<=maxN){
    nValues.insert(val);
    val*=mul;
  }
  mul = primes[nBaseId]*primes[nBaseId];
  while(mul<=maxN){
    nValues.insert(mul);
    set<int64_t>::iterator it= nValues.begin();
    val= (*it)*mul;
    while(val<=maxN){
      nValues.insert(val);
      it++;
      val= (*it)*mul;
    }
    nBaseId++;
    if(nBaseId>=(int)primes.size())
      findPrimes();
    mul = primes[nBaseId]*primes[nBaseId];
  }
  cout << "Generated " << nValues.size() << " nValues" << endl;
}

void Euler66::findN2part(int64_t newMaxN){
  cout << "finding n values upto " << newMaxN << " ... " << endl;
  maxN = newMaxN;
  int64_t mul;
  int64_t val;
  int64_t nBaseId=1;
  bool odd2s=true;
  nValuesEven2s.clear();
  nValuesOdd2s.clear();
  nValuesEven2s.insert(1);
  mul = 2;
  val = mul;
  while(val<=maxN){
    if(odd2s)
      nValuesOdd2s.insert(val);
    else
      nValuesEven2s.insert(val);
    val*=mul;
    odd2s =!odd2s;
  }
  mul = primes[nBaseId]*primes[nBaseId];
  while(mul<=maxN){
    set<int64_t>::iterator itO= nValuesOdd2s.begin();
    val= (*itO)*mul;
    while(val<=maxN){
      nValuesOdd2s.insert(val);
      itO++;
      val= (*itO)*mul;
    }
    set<int64_t>::iterator itE= nValuesEven2s.begin();
    val= (*itE)*mul;
    while(val<=maxN){
      nValuesEven2s.insert(val);
      itE++;
      val= (*itE)*mul;
    }
    nBaseId++;
    if(nBaseId>=(int)primes.size())
      findPrimes();
    mul = primes[nBaseId]*primes[nBaseId];
  }
  cout << "Generated " << nValuesOdd2s.size() + nValuesEven2s.size() << "  nValues (2part)" << endl;
}

bool Euler66::isPrime(int64_t num){
  while(true){
    for(int64_t p:primes){
      if(num%p==0)
        return false;
      if(p*p>num)
        return true;
    }
    findPrimes();
  }
  cout << "ERROR: PRIMELIST TO SMALL TO TEST IF " << num << " IS PRIME" << endl;
  return false;
}

bool Euler66::isPrimeList(int64_t num){
  while(true){
    for(int64_t p:primesList){
      if(num%p==0)
        return false;
      if(p*p>num)
        return true;
    }
    findPrimesList();
  }
  cout << "ERROR: PRIMELIST TO SMALL TO TEST IF " << num << " IS PRIME" << endl;
  return false;
}

vector<int64_t>* Euler66::factorize(int64_t num){
  vector<int64_t>* ans = new vector<int64_t>;
  int primeId=0;
  int64_t p;
  while(true){
    if(primeId == (int)primes.size())
      findPrimes();
    p = primes[primeId];
    while(num%p==0){
      ans->push_back(p);
      num /= p;
    }
    if(p*p>num){
      if(num>1)
        ans->push_back(num);
      return ans;
    }
    primeId++;
  }
  cout << "ERROR: PRIMELIST TO SMALL TO FACTORIZE " << num << endl;
  return ans;
}

vector<int64_t>* Euler66::combineLists(vector<int64_t>* a, vector<int64_t>* b){
  int indexA=0;
  int indexB=0;
  vector<int64_t>* ans = new vector<int64_t>;
  while(true){
    if((*a)[indexA]<(*b)[indexB]){
      ans->push_back((*a)[indexA]);
      indexA++;
      if(indexA==(int)a->size()){
        for(int i=indexB; i<(int)b->size(); i++)
          ans->push_back((*b)[i]);
        return ans;
      }
    }
    else{
      ans->push_back((*b)[indexB]);
      indexB++;
      if(indexB==(int)b->size()){
        for(int i=indexA; i<(int)a->size(); i++)
          ans->push_back((*a)[i]);
        return ans;
      }
    }
  }
  cout << "ERROR: SHOULD NOT GET TO THE END OF COMBINE LISTS" << endl;
  return ans;
}

bool Euler66::rootable(vector<int64_t>* a){
  if((int)a->size()<2)
    return false;
  for(int i=0; i<(int)a->size(); i+=2){
    if(i+1>=(int)a->size())
      return false;
    if((*a)[i] != (*a)[i+1])
      return false;
  }
  return true;
}

bool Euler66::divisible(vector<int64_t>* a, vector<int64_t>* b){
  int aIndex=0;
  for(int64_t i:*b){
    while(aIndex<(int)a->size() && (*a)[aIndex]<i)
      aIndex++;
    if(aIndex>=(int)a->size() || (*a)[aIndex] != i)
      return false;
    aIndex++;
  }
  return true;
}

vector<int64_t>* Euler66::divide(vector<int64_t>* a, vector<int64_t>* b){
  int bIndex=0;
  vector<int64_t>* ans = new vector<int64_t>;
  for(int64_t i:*a){
    if(bIndex<(int)b->size() && (*b)[bIndex] == i)
      bIndex++;
    else
      ans->push_back(i);
  }
  return ans;
}

Euler66::Euler66(){
  findPrimesList();
  resetnFactors();
  for(int i=181; i<=1000; i++){
    int root=sqrt(i);
    if(i!=root*root){
      d.push_back(factorize(i));
      Number n=0;
      lowestXNumber.push_back(n);
      lowestX.push_back(0);
      sqrtD.push_back(root+1);
    }
  }
  //findN2part(1000000000000000);
  //findN(1000000000000000);
}

bool Euler66::combineAndTest(vector<int64_t>* xp1, vector<int64_t>* xm1, vector<int64_t>* di){
  int xp1Index=0;
  int xm1Index=0;
  int diIndex=0;
  bool done=false;
  while(!done){
    if(xp1Index!=(int)xp1->size() && (xm1Index==(int)xm1->size() || (*xp1)[xp1Index]<(*xm1)[xm1Index])){
      if(diIndex<(int)di->size() && (*xp1)[xp1Index] == (*di)[diIndex]){
        diIndex++;
      }
      else if(xp1Index+1<(int)xp1->size() && (*xp1)[xp1Index] == (*xp1)[xp1Index+1]){
        xp1Index++;
      }
      else if(xm1Index<(int)xm1->size() && (*xp1)[xp1Index] == (*xm1)[xm1Index]){
        xm1Index++;
      }
      else{
        return false;
      }
      xp1Index++;
    }else if(xm1Index!=(int)xm1->size()){
      if(diIndex<(int)di->size() && (*xm1)[xm1Index] == (*di)[diIndex]){
        diIndex++;
      }
      else if(xm1Index+1<(int)xm1->size() && (*xm1)[xm1Index] == (*xm1)[xm1Index+1]){
        xm1Index++;
      }
      else if(xp1Index<(int)xp1->size() && (*xm1)[xm1Index] == (*xp1)[xp1Index]){
        xp1Index++;
      }
      else{
        return false;
      }
      xm1Index++;
    }else{
      done = true;
    }
  }
  return diIndex == (int)di->size();
}

bool Euler66::combineAndTest(vector<int64_t>* xp1, vector<int64_t>* xm1){
  int xp1Index=0;
  int xm1Index=0;
  while(true){
    if(xp1Index!=(int)xp1->size() && (xm1Index==(int)xm1->size() || (*xp1)[xp1Index]<(*xm1)[xm1Index])){
      if(xp1Index+1<(int)xp1->size() && (*xp1)[xp1Index] == (*xp1)[xp1Index+1]){
        xp1Index++;
      }
      else if(xm1Index<(int)xm1->size() && (*xp1)[xp1Index] == (*xm1)[xm1Index]){
        xm1Index++;
      }
      else{
        return false;
      }
      xp1Index++;
    }else if(xm1Index!=(int)xm1->size()){
      if(xm1Index+1<(int)xm1->size() && (*xm1)[xm1Index] == (*xm1)[xm1Index+1]){
        xm1Index++;
      }
      else if(xp1Index<(int)xp1->size() && (*xm1)[xm1Index] == (*xp1)[xp1Index]){
        xp1Index++;
      }
      else{
        return false;
      }
      xm1Index++;
    }else{
      return true;
    }
  }
}

void Euler66::outputVector(vector<int64_t>* a, bool oneValue){
  int64_t sum=1;
  for(int64_t i:*a){
    sum *= i;
    if(!oneValue)
      cout << i << " ";
  }
  cout << sum;
  if(!oneValue)
    cout << endl;
}

int64_t Euler66::vectorSum(vector<int64_t>* a){
  int64_t sum=1;
  for(int64_t i:*a)
    sum *= i;
  return sum;
}

int64_t Euler66::getSmallestX(vector<int64_t>* v, int64_t prodChosen, int64_t prodSkipped, int factorId, int64_t maxX){
//  cout << "getSmallestX(" << vectorSum(v) << ", " << prodChosen << ", " << prodSkipped << ", " << factorId << ")" << endl;
  int64_t maxProdChosen = prodChosen*(*v)[v->size()-factorId];
//  cout << "  maxProdChosen: " << maxProdChosen << ", maxProdSKIPPED: " << maxProdSkipped << ", possible: " << possible << endl;
  if(maxProdChosen<=maxX){
    if(factorId==(int)v->size()){
  //    cout << "  last digit... ending." << endl;
      if(maxProdChosen==prodSkipped+2)
        return prodSkipped+1;
      if(prodSkipped==maxProdChosen+2)
        return maxProdChosen+1;
      return 0;
    }else{
      int64_t x1=getSmallestX(v, maxProdChosen, prodSkipped, factorId+1, maxX);
      if(x1!=0)
        return x1;
    }
  }
  int64_t maxProdSkipped = prodSkipped*(*v)[v->size()-factorId];
//  cout << "  maxProdCHOSEN: " << maxProdChosen << ", maxProdSkipped: " << maxProdSkipped << ", possible: " << possible << endl;
  if(maxProdSkipped<=maxX){
    if(factorId==(int)v->size()){
  //    cout << "  last digit... ending." << endl;
      if(prodChosen==maxProdSkipped+2)
        return maxProdSkipped+1;
      if(maxProdSkipped==prodChosen+2)
        return prodChosen+1;
      return 0;
    }else{
      int64_t x2=getSmallestX(v, prodChosen, maxProdSkipped, factorId+1, maxX);
      if(x2!=0)
        return x2;
    }
  }
//  cout << "  returning 0" << endl;
  return 0;
}

int Euler66::getAnsCycleY(){
  y=0;
  int bestD=-1;
  int64_t bestX=0;
  int64_t tempX;
  vector<int64_t>* yFactors;
  vector<int64_t>* yy;
  vector<int64_t>* yyd;
  chrono::steady_clock::time_point begin;
  chrono::steady_clock::time_point end;
  chrono::nanoseconds elapsed1=chrono::nanoseconds(0), elapsed2=chrono::nanoseconds(0);
  while((int)d.size()){
    if(y%100==0){
      cout << "Factorization time: " << elapsed1.count()/100 << endl;
      cout << "Checking time: " << elapsed2.count()/100 << endl;
      elapsed1=chrono::nanoseconds(0);
      elapsed2=chrono::nanoseconds(0);
    }
    begin = chrono::steady_clock::now();
    y++;
    if(y==1){
      yFactors = new vector<int64_t>;
      yy = new vector<int64_t>;
    }else{
      yFactors = factorize(y);
      yy = combineLists(yFactors, yFactors);
    }
    elapsed1 += chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - begin);
    begin = chrono::steady_clock::now();
    for(int i=0; i<(int)d.size(); i++){
      if(y==1){
        yyd=new vector<int64_t>;
        for(int64_t dNum:*(d[i]))
          yyd->push_back(dNum);
      }else
        yyd = combineLists(yy, d[i]);
      if(yyd->size() == 1)
        tempX = 0;
      else
        tempX = getSmallestX(yyd, yyd->back(), 1, 2, y*sqrtD[i]+2);
      if(tempX!=0){
        cout << "Removing " << vectorSum(d[i]) << ", y=" << y << ", x=" << tempX << ", remaning=" << d.size() << endl;
        if(tempX>bestX || bestD == -1){
          bestD = vectorSum(d[i]);
          bestX = tempX;
        }
        sqrtD.erase(sqrtD.begin()+i);
        d.erase(d.begin()+i);
        i--;
      }
      delete yyd;
    }
    elapsed2 += chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - begin);
    delete yy;
    delete yFactors;
  }
  return 0;
}

int Euler66::getAnsCycleXNoFactors(){
  bool ok;
  int64_t xp1;
  int64_t xm1;
  int64_t xxdd;     //(x+1)(x-1)/d
  x=1;
  chrono::steady_clock::time_point begin;
  chrono::steady_clock::time_point end;
  chrono::nanoseconds elapsed1=chrono::nanoseconds(0), elapsed2=chrono::nanoseconds(0);
  while((int)d.size()>1){
    if(x%1000000==0){
      cout << "Factorization time: " << elapsed1.count()/1000000 << endl;
      cout << "Checking time: " << elapsed2.count()/1000000 << endl;
      elapsed1=chrono::nanoseconds(0);
      elapsed2=chrono::nanoseconds(0);
    }
    begin = chrono::steady_clock::now();
    x++;
    for(int i=0; i<(int)d.size(); i++){
      ok=true;
      xp1 = x+1;
      xm1 = x-1;
      for(int f: (*(d[i]))){
        if(xp1%f==0){
          xp1/=f;
        }else if(xm1%f==0){
          xm1/=f;
        }else{
          ok=false;
          break;
        }
      }
      if(ok){
        xxdd=xp1*xm1;
        y = sqrt(xxdd);
        if(y*y==xxdd){
          if(d.size()<300){
            for(vector<int64_t>* v:d){
              cout << vectorSum(v) << endl;
            }
          }
          cout << "Removing " << vectorSum(d[i]) << ", y=" << y << ", x=" << x << ", remaning=" << d.size()-1 << endl;
          d.erase(d.begin()+i);
          i--;
        }
      }
    }
    elapsed2 += chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - begin);
  }
  return vectorSum(d[0]);
}

int Euler66::solveDCycleXBigJump(int id){
  chrono::steady_clock::time_point begin;
  chrono::seconds elapsed1=chrono::seconds(0);
  begin = chrono::steady_clock::now();
  bool ok;
  int64_t xp1;
  int64_t xm1;
  int64_t xxdd;     //(x+1)(x-1)/d
  int64_t biggestFactor;
  bool addType;
  vector<int64_t>* currentD = new vector<int64_t>;
  bool done;
  done = false;
  (*currentD) = *(d[id]);
  biggestFactor = d[0]->back()-2;
  addType=false;
  int64_t localX=1;
  int64_t localY;
  while(!done){
    if(biggestFactor>3){
      if(addType)
        localX+=2;
      else
        localX+=biggestFactor;
      addType = !addType;
    }else{
      localX++;
    }
    ok=true;
    xp1 = localX+1;
    xm1 = localX-1;
    for(int f: (*currentD)){
      if(xp1%f==0){
        xp1/=f;
      }else if(xm1%f==0){
        xm1/=f;
      }else{
        ok=false;
        break;
      }
    }
    if(ok){
      xxdd=xp1*xm1;
      localY = sqrt(xxdd);
      if(localY*localY==xxdd){
        lowestX[id] = localX;
        done = true;
      }
    }
  }
  elapsed1 == chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - begin);
  return elapsed1.count();
}

int Euler66::getAnsCycleXBigJump(){
  int threadCount =7;
  int threadWorkingOn[threadCount];
  future<int> fut[threadCount];
  for(int i=0; i<threadCount; i++){
    threadWorkingOn[i] = i;
    fut[i] = async(launch::async, &Euler66::solveDCycleXBigJump, this,i);
  }
  int nextFreeD=threadCount;
  int finishedD=0;
  while(finishedD<(int)d.size()){
    for(int i=0; i<threadCount; i++){
      if(threadWorkingOn[i] != -1 && fut[i].wait_for(0ms) == future_status::ready){
        finishedD++;
        if(nextFreeD<=1000){
          fut[i] = async(launch::async, &Euler66::solveDCycleXBigJump, this,nextFreeD);
          cout << vectorSum(d[threadWorkingOn[i]]) << " done in " /*<< fut[i].get()*/ << " seconds, x=" << lowestX[threadWorkingOn[i]] << ". Starting on " << vectorSum(d[nextFreeD]) << endl;
          threadWorkingOn[i] = nextFreeD;
          nextFreeD++;
          for(int i2=0; i2<threadCount; i2++){
            if(i==i2)
              cout << "  thread " << i2 << "*: " <<vectorSum(d[threadWorkingOn[i2]]) << endl;
            else
              cout << "  thread " << i2 << ": " <<vectorSum(d[threadWorkingOn[i2]]) << endl;
          }
        }else{
          cout << vectorSum(d[threadWorkingOn[i]]) << " done in " /*<< fut[i].get()*/ << " seconds, x=" << lowestX[threadWorkingOn[i]] << ". No more free d" << endl;
          threadWorkingOn[i] = -1;
          for(int i2=0; i2<threadCount; i2++){
            if(i==i2)
              cout << "  thread " << i2 << "*: " <<vectorSum(d[threadWorkingOn[i2]]) << endl;
            else
              cout << "  thread " << i2 << ": " <<vectorSum(d[threadWorkingOn[i2]]) << endl;
          }
        }
      }
    }
  }
  int64_t bestX = lowestX[0];
  int bestD = 0;
  for(int i=1; i<(int)lowestX.size(); i++){
    if(lowestX[i]>bestX){
      bestX = lowestX[i];
      bestD = i;
    }
  }
  return vectorSum(d[bestD]);
}

int Euler66::getAnsCycleXBigJumpSingleThread(){
  int i=0;
  while(i<(int)d.size()){
    chrono::steady_clock::time_point begin;
    chrono::seconds elapsed1=chrono::seconds(0);
    begin = chrono::steady_clock::now();
    bool ok;
    int64_t xp1;
    int64_t xm1;
    int64_t xxdd;     //(x+1)(x-1)/d
    int64_t biggestFactor;
    bool addType;
    bool done;
    done = false;
    biggestFactor = d[i]->back();
    addType=true;
    int64_t n=0;
    int64_t nd=0;
    //cout << "d: " << vectorSum(d[i]) << endl;
    while(!done){
      if(addType){
        n++;
        nd+=biggestFactor;
        if(n==1 && biggestFactor==2){
          n++;
          nd+=biggestFactor;
        }
        xp1 = n;
        xm1 = nd-2;
        //cout << "x: " << nd-1 << endl;
      }else{
        xp1 = nd+2;
        xm1 = n;
        //cout << "x: " << nd+1 << endl;
      }
      addType = !addType;
      ok=true;
      for(int fId=0; fId<(int)d[i]->size()-1; fId++){
        if(xp1%(*(d[i]))[fId]==0){
          xp1/=(*(d[i]))[fId];
        }else if(xm1%(*(d[i]))[fId]==0){
          xm1/=(*(d[i]))[fId];
        }else{
          ok=false;
          break;
        }
      }
      if(ok){
        xxdd=xp1*xm1;
        y = sqrt(xxdd);
        if(y*y==xxdd){
          lowestX[i] = x;
          done = true;
          elapsed1 == chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - begin);
          if(addType)
            cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: " << nd+1 << ", y: " << y << endl;
          else
            cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: " << nd-1 << ", y: " << y << endl;
        }
      }
    }
    i++;
  }
  int64_t bestX = lowestX[0];
  int bestD = 0;
  for(int i=1; i<(int)lowestX.size(); i++){
    if(lowestX[i]>bestX){
      bestX = lowestX[i];
      bestD = i;
    }
  }
  return vectorSum(d[bestD]);
}

int Euler66::getAnsCycleXnList(){
  int i=0;
  int64_t maxInt = sqrt(9223372036854775807);
  Number xxddN, xp1N, xm1N, yN;
  while(i<(int)d.size()){
    chrono::steady_clock::time_point begin;
    chrono::seconds elapsed1=chrono::seconds(0);
    begin = chrono::steady_clock::now();
    bool ok;
    int64_t otherFactor;
    int64_t xp1;
    int64_t xm1;
    int64_t biggestFactor;
    int64_t xxdd;
    bool addType;
    bool done;
    bool overflow;
    done = false;
    biggestFactor = d[i]->back();
    addType=true;
    set<int64_t>::iterator nItE=nValuesEven2s.begin();
    nItE++;
    set<int64_t>::iterator nItO=nValuesOdd2s.begin();
    int64_t currentNValue;
    int64_t n=0;
    int64_t nd=0;
    bool evenNValue;
    bool thisIsAPrime = ((int)d[i]->size()==1);
    int64_t maxNLocal = (maxN-2)/biggestFactor;
    while(!done){
      overflow=false;
      if(thisIsAPrime){
        if(addType){
          if(*nItE<*nItO){
            currentNValue = *nItE;
            nItE++;
            evenNValue=true;
          }else{
            currentNValue = *nItO;
            nItO++;
            evenNValue=false;
          }
          if(currentNValue>=maxNLocal){
            if(maxN>=9223372036854775807/2){
              cout << "Error: maximum n reached" << endl;
              return 0;
            }
            findN(maxN*2);
            maxNLocal = (maxN-2)/biggestFactor;
            nItE=nValuesEven2s.begin();
            nItE++;
            nItO=nValuesOdd2s.begin();
            currentNValue=*nItO;
            evenNValue=false;
            nItO++;
          }
          otherFactor=biggestFactor*currentNValue+2;
        }else{
          otherFactor=biggestFactor*currentNValue-2;
        }
        addType = !addType;
        if((evenNValue && nValuesEven2s.find(otherFactor)!= nValuesEven2s.end()) || (!evenNValue && nValuesOdd2s.find(otherFactor)!= nValuesOdd2s.end())){
          done = true;
          elapsed1 = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - begin);
          if(addType){
            lowestX[i] = otherFactor+1;
            cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: " << otherFactor+1 << ". nIt: " << currentNValue << endl;
          }else{
            lowestX[i] = otherFactor-1;
            cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: " << otherFactor-1 << ". nIt: " << currentNValue << endl;
          }
        }
      }else{
        if(addType){
          n++;
          nd+=biggestFactor;
          if(n==1 && biggestFactor==2){
            n++;
            nd+=biggestFactor;
          }
          xp1 = n;
          xm1 = nd-2;
          if(xm1>maxInt)
            overflow=true;
        }else{
          xp1 = nd+2;
          xm1 = n;
          if(xp1>maxInt)
            overflow=true;
        }
        addType = !addType;
        ok=true;
        for(int fId=0; fId<(int)d[i]->size()-1; fId++){
          if(xp1%(*(d[i]))[fId]==0){
            xp1/=(*(d[i]))[fId];
          }else if(xm1%(*(d[i]))[fId]==0){
            xm1/=(*(d[i]))[fId];
          }else{
            ok=false;
            break;
          }
        }
        if(ok){
          if(overflow){
            xp1N=xp1;
            xm1N=xm1;
            xxddN=xp1N*xm1N;
            ok=xxddN.sqrtAble();
          }else{
            xxdd=xp1*xm1;
            y = sqrt(xxdd);
            ok=(y*y==xxdd);
          }
          if(ok){
            done = true;
            elapsed1 = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - begin);
            if(overflow){
              if(addType){
                lowestX[i] = nd+1;
                cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: " << nd+1 << ", y: ";
                yN.outputNumber();
                cout << ", xp1: " << xp1 << ", xm1: " << xm1 << endl;
              }else{
                lowestX[i] = nd-1;
                cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: " << nd-1 << ", y: ";
                yN.outputNumber();
                cout << ", xp1: " << xp1 << ", xm1: " << xm1 << endl;
              }
            }else{
              if(addType){
                lowestX[i] = nd+1;
                cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: " << nd+1 << ", y: " << y << ", xp1: " << xp1 << ", xm1: " << xm1 << endl;
              }else{
                lowestX[i] = nd-1;
                cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: " << nd-1 << ", y: " << y << ", xp1: " << xp1 << ", xm1: " << xm1 << endl;
              }
            }
          }
        }
      }
    }
    i++;
  }
  int64_t bestX = lowestX[0];
  int bestD = 0;
  for(int i=1; i<(int)lowestX.size(); i++){
    if(lowestX[i]>bestX){
      bestX = lowestX[i];
      bestD = i;
    }
  }
  return vectorSum(d[bestD]);
}

vector<vector<int64_t>::iterator> Euler66::getSmallestnFactors(){
  int index=0;
  Number lowestProd;
  Number nProd;
  bool firstRound=true;
  if((int)nFactors.size()==0){
    vector<vector<int64_t>::iterator> singles;
    singles.push_back(primes.begin());
    nFactors.push_back(singles);
    return {notReallyPrimes.begin()};
  }
  for(int i=0; i<(int)nFactors.size(); i++){
    nProd = getnFactorProduct(nFactors[i]);
    if(firstRound || nProd<lowestProd){
      firstRound=false;
      lowestProd=nProd;
      index=i;
    }
  }
  vector<vector<int64_t>::iterator> ans = nFactors[index];
  increasenFactor(index);
  return ans;
}

Number Euler66::getnFactorProduct(vector<vector<int64_t>::iterator>& v){
  Number ans=1;
  for(vector<int64_t>::iterator it: v){
    Number it2=*it;
    ans = ans*it2;
    if((*it)!=2)
      ans = ans*it2;
  }
  return ans;
}

Number Euler66::getnFactorProductList(vector<list<int64_t>::iterator>& v){
  Number ans=1;
  for(list<int64_t>::iterator it: v){
    Number it2=*it;
    ans = ans*it2;
    if((*it)!=2)
      ans = ans*it2;
  }
  return ans;
}

void Euler66::increasenFactor(int index){
  vector<vector<int64_t>::iterator> nFactorCopy;
  vector<vector<int64_t>::iterator> bestnFactorCopy;
  Number minnProduct = -1;
  Number nProd;
  bool firstRound=true;
  for(int i=0; i<(int)nFactors[index].size(); i++){
    nFactorCopy = nFactors[index];
    if((nFactorCopy[i]+1)==primes.end())
      findPrimes();
    nFactorCopy[i]++;
    for(int i2=i+1; i2<(int)nFactorCopy.size(); i2++)
      nFactorCopy[i2]=nFactorCopy[i];
    nProd = getnFactorProduct(nFactorCopy);
    if(firstRound || nProd<minnProduct){
      firstRound=false;
      minnProduct = nProd;
      bestnFactorCopy = nFactorCopy;
    }
  }
  nFactors[index] = bestnFactorCopy;
  if(index==(int)nFactors.size()-1){
    vector<vector<int64_t>::iterator> newnFactors;
    for(int i=0; i<=index+1; i++){
      newnFactors.push_back(primes.begin());
    }
    nFactors.push_back(newnFactors);
  }
}

void Euler66::outputnFactors(){
  for(vector<vector<int64_t>::iterator> v: nFactors){
    for(vector<int64_t>::iterator it:v){
      cout << *it << "*";
      /*if((*it)!=2)
        cout << *it << "*";*/
      cout << " ";
    }
    cout << "= ";
    getnFactorProduct(v).outputNumber();
    cout << endl;
  }
}

void Euler66::resetnFactors(){
  nFactors.clear();
}

int Euler66::getAnsCycleXcalcN(){
  int i=0;
  int64_t maxInt = sqrt(9223372036854775807);
  Number xxddN, xp1N, xm1N, yN;
  while(i<(int)d.size()){
    chrono::steady_clock::time_point begin;
    chrono::seconds elapsed1=chrono::seconds(0);
    begin = chrono::steady_clock::now();
    bool ok;
    vector<vector<int64_t>::iterator> currentNValue;
    Number otherFactor;
    int64_t xp1;
    int64_t xm1;
    int64_t biggestFactor;
    int64_t xxdd;
    bool addType;
    bool done;
    bool overflow;
    done = false;
    biggestFactor = d[i]->back();
    addType=true;
    int64_t n=0;
    int64_t nd=0;
    bool thisIsAPrime = ((int)d[i]->size()==1);
    if(thisIsAPrime)
      resetnFactors();
    cout << endl << endl << "d: " << vectorSum(d[i])<<endl;
    while(!done){
      overflow=false;
      if(thisIsAPrime){
        if(addType){
          currentNValue = getSmallestnFactors();
          otherFactor=getnFactorProduct(currentNValue)*biggestFactor+2;
        }else{
          otherFactor=otherFactor-4;
        }
        /*cout << "currentNValue: ";
        getnFactorProduct(currentNValue).outputInfo();
        cout << "otherFactor: ";
        otherFactor.outputInfo();*/
        addType = !addType;
        bool matching2s=true;
        vector<vector<int64_t>::iterator>::iterator it=currentNValue.begin();
        while(it!=currentNValue.end() && **it == 2){
          matching2s = !matching2s;
          //cout << "currentNValue matching 2s: " << matching2s << endl;
          it++;
        }
        vector<int64_t>::iterator primeIt=primes.begin();
        ok=true;
        int64_t oneOfTwo=0;
        Number otherFactorCopy = otherFactor;
        Number primeSquared=(*primeIt);
        primeSquared = primeSquared*(*primeIt);
        while(!(primeSquared>otherFactorCopy) && ok){
          if(otherFactorCopy%(*primeIt)==0){
            //cout << "Prime factor: " << (*primeIt) << endl;
            if(*primeIt==2)
              matching2s = !matching2s;
            else if(oneOfTwo==0)
              oneOfTwo = (*primeIt);
            else if(oneOfTwo == (*primeIt))
              oneOfTwo = 0;
            else
              ok=false;
            otherFactorCopy/=(*primeIt);
          }else{
            if((primeIt+1)==primes.end())
              findPrimes();
            primeIt++;
          }
          primeSquared=(*primeIt);
          primeSquared = primeSquared*(*primeIt);
        }
        //cout << "Prime factor: ";
        //otherFactorCopy.outputInfo();
        if(otherFactorCopy==2){
          matching2s = !matching2s;
          if(oneOfTwo!=0)
            ok=false;
        }else if(!(otherFactorCopy==oneOfTwo))
          ok=false;
        if(!matching2s)
          ok=false;
        //cout << "ok: " << ok << endl;
        if(ok){
          done = true;
          elapsed1 = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - begin);
          if(addType){
            lowestXNumber[i] = otherFactor+1;
            cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: ";
            lowestXNumber[i].outputNumber();
            cout << ". nCalc: ";
            getnFactorProduct(currentNValue).outputNumber();
            cout << endl;
          }else{
            lowestXNumber[i] = otherFactor-1;
            cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: ";
            lowestXNumber[i].outputNumber();
            cout << ". nCalc: ";
            getnFactorProduct(currentNValue).outputNumber();
            cout << endl;
          }
        }
      }else{
        if(addType){
          n++;
          nd+=biggestFactor;
          if(n==1 && biggestFactor==2){
            n++;
            nd+=biggestFactor;
          }
          xp1 = n;
          xm1 = nd-2;
          if(xm1>maxInt)
            overflow=true;
        }else{
          xp1 = nd+2;
          xm1 = n;
          if(xp1>maxInt)
            overflow=true;
        }
        addType = !addType;
        ok=true;
        for(int fId=0; fId<(int)d[i]->size()-1; fId++){
          if(xp1%(*(d[i]))[fId]==0){
            xp1/=(*(d[i]))[fId];
          }else if(xm1%(*(d[i]))[fId]==0){
            xm1/=(*(d[i]))[fId];
          }else{
            ok=false;
            break;
          }
        }
        if(ok){
          if(overflow){
            xp1N=xp1;
            xm1N=xm1;
            xxddN=xp1N*xm1N;
            ok=xxddN.sqrtAble();
          }else{
            xxdd=xp1*xm1;
            y = sqrt(xxdd);
            ok=(y*y==xxdd);
          }
          if(ok){
            done = true;
            elapsed1 = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - begin);
            if(overflow){
              if(addType){
                lowestX[i] = nd+1;
                cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: " << nd+1 << ", y: ";
                yN.outputNumber();
                cout << ", xp1: " << xp1 << ", xm1: " << xm1 << endl;
              }else{
                lowestX[i] = nd-1;
                cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: " << nd-1 << ", y: ";
                yN.outputNumber();
                cout << ", xp1: " << xp1 << ", xm1: " << xm1 << endl;
              }
            }else{
              if(addType){
                lowestX[i] = nd+1;
                cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: " << nd+1 << ", y: " << y << ", xp1: " << xp1 << ", xm1: " << xm1 << endl;
              }else{
                lowestX[i] = nd-1;
                cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: " << nd-1 << ", y: " << y << ", xp1: " << xp1 << ", xm1: " << xm1 << endl;
              }
            }
          }
        }
      }
    }
    i++;
  }
  int64_t bestX = lowestX[0];
  int bestD = 0;
  for(int i=1; i<(int)lowestX.size(); i++){
    if(lowestX[i]>bestX){
      bestX = lowestX[i];
      bestD = i;
    }
  }
  return vectorSum(d[bestD]);
}

int Euler66::getAnsCycleXcalcNClass(){
  int i=0;
  int64_t maxInt = sqrt(9223372036854775807);
  Number xxddN, xp1N, xm1N, yN;
  int outputInterval=0;
  while(i<(int)d.size()){
    chrono::steady_clock::time_point begin;
    chrono::steady_clock::time_point subBegin;
    chrono::steady_clock::time_point subBegin2;
    chrono::seconds elapsed1=chrono::seconds(0);
    chrono::nanoseconds subTimes[10];
    for(int i=0; i<10; i++)
      subTimes[i] =chrono::nanoseconds(0);
    begin = chrono::steady_clock::now();
    bool ok;
    vector<list<int64_t>::iterator> currentNValue;
    Number otherFactor;
    int64_t xp1;
    int64_t xm1;
    int64_t biggestFactor;
    int64_t xxdd;
    bool addType;
    bool done;
    bool overflow;
    bool firstRound = true;
    done = false;
    biggestFactor = d[i]->back();
    addType=true;
    int64_t n=0;
    int64_t nd=0;
    bool thisIsAPrime = ((int)d[i]->size()==1);
    if(thisIsAPrime){
      resetNValue();
    }
    //cout << endl << endl << "d: " << vectorSum(d[i])<<endl;
    while(!done){
      overflow=false;
      if(thisIsAPrime){
        subBegin = chrono::steady_clock::now();
        if(addType){
          currentNValue = getLowestNValue();
          otherFactor=getnFactorProductList(currentNValue)*biggestFactor-2;
        }else{
          otherFactor=otherFactor+4;
        }
        if(firstRound){
          nextNForTest = nValuesClass.begin();
          firstRound=false;
        }
        ok=true;
        outputInterval++;
        subTimes[0] += chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - subBegin);
        if(outputInterval==10000){
          cout << "currentNValue: ";
          getnFactorProductList(currentNValue).outputInfo();
          cout << subTimes[0].count()/10000<< " Time (getLowestN)" << endl;
          cout << subTimes[1].count()/10000<<" Time (getOtherN)"<<endl;
          cout << subTimes[2].count()/10000<<" Time (generateNewN)"<<endl;
          outputInterval=0;
          for(int i=0; i<10; i++)
            subTimes[i] =chrono::nanoseconds(0);
        }
        /*cout << "otherFactor: ";
        otherFactor.outputInfo();*/
        subBegin = chrono::steady_clock::now();
        addType = !addType;
        /*cout << "comparing ";
        otherFactor.outputNumber();
        cout << endl;*/
        while(otherFactor>nextNForTest->value){
          subBegin2 = chrono::steady_clock::now();
          generateNewN(*nextNForTest);
          nextNForTest++;
          subTimes[2] += chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - subBegin2);
        }
        /*cout << " with ";
        outputSinglenValuesClass(nextNForTest);*/
        if(!(otherFactor==nextNForTest->value))
          ok=false;
        else{
          if((**currentNValue.begin() == 2) != (**nextNForTest->factors.begin() == 2)) //Matching 2s
            ok = false;
        }
        subTimes[1] += chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - subBegin);
        //cout << "ok: " << ok << endl;
        if(ok){
          done = true;
          elapsed1 = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - begin);
          if(addType){
            lowestXNumber[i] = otherFactor-1;
            cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: ";
            lowestXNumber[i].outputNumber();
            cout << ". nCalc: ";
            getnFactorProductList(currentNValue).outputNumber();
            cout << endl;
          }else{
            lowestXNumber[i] = otherFactor+1;
            cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: ";
            lowestXNumber[i].outputNumber();
            cout << ". nCalc: ";
            getnFactorProductList(currentNValue).outputNumber();
            cout << endl;
          }
        }
      }else{
        if(addType){
          n++;
          nd+=biggestFactor;
          if(n==1 && biggestFactor==2){
            n++;
            nd+=biggestFactor;
          }
          xp1 = n;
          xm1 = nd-2;
          if(xm1>maxInt)
            overflow=true;
        }else{
          xp1 = nd+2;
          xm1 = n;
          if(xp1>maxInt)
            overflow=true;
        }
        addType = !addType;
        ok=true;
        for(int fId=0; fId<(int)d[i]->size()-1; fId++){
          if(xp1%(*(d[i]))[fId]==0){
            xp1/=(*(d[i]))[fId];
          }else if(xm1%(*(d[i]))[fId]==0){
            xm1/=(*(d[i]))[fId];
          }else{
            ok=false;
            break;
          }
        }
        if(ok){
          if(overflow){
            xp1N=xp1;
            xm1N=xm1;
            xxddN=xp1N*xm1N;
            ok=xxddN.sqrtAble();
          }else{
            xxdd=xp1*xm1;
            y = sqrt(xxdd);
            ok=(y*y==xxdd);
          }
          if(ok){
            done = true;
            elapsed1 = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - begin);
            if(overflow){
              if(addType){
                lowestX[i] = nd+1;
                cout << vectorSum(d[i]) << " done. x: " << nd+1 << endl;
              }else{
                lowestX[i] = nd-1;
                cout << vectorSum(d[i]) << " done. x: " << nd-1 << endl;
              }
            }else{
              if(addType){
                lowestX[i] = nd+1;
                cout << vectorSum(d[i]) << " done. x: " << nd+1 << endl;
              }else{
                lowestX[i] = nd-1;
                cout << vectorSum(d[i]) << " done in. x: " << nd-1 << endl;
              }
            }
          }
        }
      }
    }
    i++;
  }
  int64_t bestX = lowestX[0];
  int bestD = 0;
  for(int i=1; i<(int)lowestX.size(); i++){
    if(lowestX[i]>bestX){
      bestX = lowestX[i];
      bestD = i;
    }
  }
  return vectorSum(d[bestD]);
}

int Euler66::getAnsCycleXBackToBasics(){
  int i=0;
  int64_t maxInt = sqrt(9223372036854775807);
  Number xxddN, xp1N, xm1N, yN;
  int outputInterval=0;
  while(i<(int)d.size()){
    chrono::steady_clock::time_point begin;
    chrono::steady_clock::time_point subBegin;
    chrono::steady_clock::time_point subBegin2;
    chrono::seconds elapsed1=chrono::seconds(0);
    chrono::nanoseconds subTimes[10];
    for(int i=0; i<10; i++)
      subTimes[i] =chrono::nanoseconds(0);
    begin = chrono::steady_clock::now();
    bool ok;
    set<int64_t>::iterator currentNValue=nValuesComplete.begin();
    int64_t otherFactor;
    int64_t xp1;
    int64_t xm1;
    int64_t biggestFactor;
    int64_t xxdd;
    bool addType;
    bool done;
    bool overflow;
    bool firstRound = true;
    done = false;
    biggestFactor = d[i]->back();
    int64_t maxNValue=maxSafenValue/biggestFactor-2;
    addType=true;
    int64_t n=0;
    int64_t nd=0;
    bool thisIsAPrime = ((int)d[i]->size()==1);
    if(thisIsAPrime){
      resetNValue();
    }
    //cout << endl << endl << "d: " << vectorSum(d[i])<<endl;
    while(!done){
      overflow=false;
      if(thisIsAPrime){
        subBegin = chrono::steady_clock::now();
        if(addType){
          if(!firstRound)
            currentNValue++;
          firstRound=false;
          if(currentNValue == nValuesComplete.end() || *currentNValue > maxNValue){
            cout << "end of nvalues reached" << endl;
            return 0;
          }
          otherFactor=*currentNValue*biggestFactor+2;
        }else{
          otherFactor=otherFactor-4;
        }
        ok=(nValuesComplete.find(otherFactor)!=nValuesComplete.end());
        outputInterval++;
        if(outputInterval==1000000){
          cout << "current value: " << *currentNValue << ". Other factor: " << otherFactor << endl;
          outputInterval=0;
        }
        addType = !addType;

        if(ok){
          done = true;
          elapsed1 = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - begin);
          if(addType){
            lowestXNumber[i] = otherFactor-1;
            cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: ";
            lowestXNumber[i].outputNumber();
            cout << endl;
          }else{
            lowestXNumber[i] = otherFactor+1;
            cout << vectorSum(d[i]) << " done in " << elapsed1.count() << ". x: ";
            lowestXNumber[i].outputNumber();
            cout << endl;
          }
        }
      }else{
        if(addType){
          n++;
          nd+=biggestFactor;
          if(n==1 && biggestFactor==2){
            n++;
            nd+=biggestFactor;
          }
          xp1 = n;
          xm1 = nd-2;
          if(xm1>maxInt)
            overflow=true;
        }else{
          xp1 = nd+2;
          xm1 = n;
          if(xp1>maxInt)
            overflow=true;
        }
        addType = !addType;
        ok=true;
        for(int fId=0; fId<(int)d[i]->size()-1; fId++){
          if(xp1%(*(d[i]))[fId]==0){
            xp1/=(*(d[i]))[fId];
          }else if(xm1%(*(d[i]))[fId]==0){
            xm1/=(*(d[i]))[fId];
          }else{
            ok=false;
            break;
          }
        }
        if(ok){
          if(overflow){
            xp1N=xp1;
            xm1N=xm1;
            xxddN=xp1N*xm1N;
            ok=xxddN.sqrtAble();
          }else{
            xxdd=xp1*xm1;
            y = sqrt(xxdd);
            ok=(y*y==xxdd);
          }
          if(ok){
            done = true;
            elapsed1 = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - begin);
            if(overflow){
              if(addType){
                lowestX[i] = nd+1;
                cout << vectorSum(d[i]) << " done. x: " << nd+1 << endl;
              }else{
                lowestX[i] = nd-1;
                cout << vectorSum(d[i]) << " done. x: " << nd-1 << endl;
              }
            }else{
              if(addType){
                lowestX[i] = nd+1;
                cout << vectorSum(d[i]) << " done. x: " << nd+1 << endl;
              }else{
                lowestX[i] = nd-1;
                cout << vectorSum(d[i]) << " done in. x: " << nd-1 << endl;
              }
            }
          }
        }
      }
    }
    i++;
  }
  int64_t bestX = lowestX[0];
  int bestD = 0;
  for(int i=1; i<(int)lowestX.size(); i++){
    if(lowestX[i]>bestX){
      bestX = lowestX[i];
      bestD = i;
    }
  }
  return vectorSum(d[bestD]);
}

void Euler66::generateNewN(const NValue& nValue){
  /*cout << "Generating from: ";
  outputSinglenValuesClass(nValue);*/
  if(nValue.factors[0] == notReallyPrimesList.begin())
    return;
  int last2=-1;
  int firstNon2=-1;
  for(int i=0; i<(int)nValue.factors.size(); i++){
    if(*(nValue.factors[i])!=2){
      firstNon2 = i;
      break;
    }else{
      last2=i;
    }
  }
  if(firstNon2==-1){                        //All 2s
    NValue n=nValue;
    n.factors.push_back(primesList.begin());
    if(n.factors.size()%2==0){              //Even number of 2s not allowed, dont save and generate new instead
      generateNewN(n);
    }else{
      n.setValue();
      /*cout << " generated: ";
      outputSinglenValuesClass(n);*/
      nValuesClass.insert(n);
    }
  }else{                                    //First non 2
    if((firstNon2==(int)nValue.factors.size()-1 || *(nValue.factors[firstNon2])<*(nValue.factors[firstNon2+1])) && (firstNon2==0 || firstNon2%2==1)){
      NValue n=nValue;                      //Even number of 2s not allowed, combinations above this one is reached through the last2 increase.
      if(nextIt(n.factors[firstNon2])==primesList.end())
        findPrimesList();
      n.factors[firstNon2]++;
      n.setValue();
      /*cout << " generated: ";
      outputSinglenValuesClass(n);*/
      nValuesClass.insert(n);
    }
  }
  if(last2!=-1){                            //last2
    if(last2==(int)nValue.factors.size()-1 || *(nValue.factors[last2])<*(nValue.factors[last2+1])){
      NValue n=nValue;
      if(nextIt(n.factors[last2])==primesList.end())
        findPrimesList();
      n.factors[last2]++;
      if(last2>0 && last2%2==0){      //Even number of 2s not allowed, dont save and generate new instead
        generateNewN(n);
      }else{
        n.setValue();
        /*cout << " generated: ";
        outputSinglenValuesClass(n);*/
        nValuesClass.insert(n);
      }
    }
  }
  if(firstNon2>0 && *(nValue.factors[firstNon2])==3 && firstNon2%2==1){    //Since we dont create new values from "fistNon2" when there are even number of 2s, we create them from here instead
    if(firstNon2+1 == (int)nValue.factors.size()-1 || (firstNon2+1 < (int)nValue.factors.size()-1 && *(nValue.factors[firstNon2+1])<*(nValue.factors[firstNon2+2]))){
      NValue n=nValue;
      if(nextIt(n.factors[firstNon2+1])==primesList.end())
        findPrimesList();
      n.factors[firstNon2+1]++;
      n.setValue();
      /*cout << " generated: ";
      outputSinglenValuesClass(n);*/
      nValuesClass.insert(n);
    }
  }
  //cout << "Generation done" << endl;
}

vector<list<int64_t>::iterator> Euler66::getLowestNValue(){
  NValue n = *nValuesClass.begin();
  /*cout << "Getting lowest n: ";
  outputSinglenValuesClass(nValuesClass.begin());*/
  nValuesClass.erase(nValuesClass.begin());
  return n.factors;
}

void Euler66::resetNValue(){
  nValuesClass.clear();
  NValue v;
  v.factors.push_back(primesList.begin());
  v.setValue();
  NValue v2;
  v2.factors.push_back(notReallyPrimesList.begin());
  v2.setValue();
  nValuesClass.insert(v);
  nValuesClass.insert(v2);
}

void NValue::setValue(){
  value=1;
  for(list<int64_t>::iterator it: factors){
    Number factor = *it;
    value = value*factor;
    if((*it)!=2)
      value = value*factor;
  }
}

void Euler66::outputnValuesClass(){
  for(NValue v: nValuesClass){
    for(list<int64_t>::iterator it:v.factors){
      cout << *it << "*";
      cout << " ";
    }
    cout << "= ";
    v.value.outputNumber();
    cout << endl;
  }
}

void Euler66::outputSinglenValuesClass(const NValue& v){
  for(list<int64_t>::iterator it:v.factors){
    cout << *it << "*";
    cout << " ";
  }
  cout << "= ";
  Number n = v.value;
  n.outputNumber();
  cout << endl;
}

bool NValue::operator<(const NValue& n) const{
  return value<n.value;
}

bool NValue::operator>(const NValue& n) const{
  return value>n.value;
}

bool NValue::operator==(const NValue& n) const{
  return value==n.value;
}

int main(){
  //int64Max/100 did not give the answer :(
  Euler66 e;
  e.maxSafenValue=int64Max/100;
  e.generatenValuesComplete();
  int ans = e.getAnsCycleXBackToBasics();
  cout << "Final D: " << ans << endl;
  /*int64_t calculated=0;
  int64_t magnitude=1000000;
  e.resetNValue();
  e.nextNForTest = e.nValuesClass.begin();
  while(calculated<200000000){
    e.generateNewN(*e.nextNForTest);
    calculated++;
    if(calculated==magnitude){
      cout << "Generated from " << calculated << " nalues. Last tested nValue ";
      Number n = e.nextNForTest->value;
      n.outputNumber();
      cout << ". Generated " << e.nValuesClass.size() << endl;
      magnitude += 1000000;
    }
    e.nextNForTest++;
  }*/
  return 0;
}
