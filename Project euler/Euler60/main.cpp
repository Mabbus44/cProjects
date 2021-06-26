#include <iostream>
#include "C:/Users/Mabbus/Documents/c++ projects/Primelist/primelist.h"

#define DEBUG		0

//Found 55621, 18493, 991, 883, 733
//733: 3,127,157,307,409
//883: 7,109,163,193,241,331,433,613,661,733,877
//991: 313,541,607,643,733,811,883
//18493: 457,733,823,883,991,10093,10273,11047,11587,12583,13003,14653,15583,15889,16069,17011,17203,17539,17551,17761,17863
//55621: 193,673,733,883,991,10831,10891,10903,11941,12109,12511,12601,13327,13591,13693,14083,17047,18181,18439,18493,20323
//Vilket stämmer, men kanske inte är den lägsta

using namespace std;

class IntList{
public:
  int* num;						//The actual num
  IntList* next;					//Adress to the next num in the list
  IntList* previous;					//Adress to the previous num in the list
  IntList();						//Default constructor
  IntList(const int& num);				//Put num in this listspot
  ~IntList();						//Connects list item after with the one before
  bool addAfter(const int& num);				//Add num after this one in the list
  bool addBefore(const int& num);				//Add num before this one in the list
  IntList* myAnd(IntList* other);         //Returns list with all int present in both lists
};

int digits(int64_t num);
int64_t combine(int64_t numA, int64_t numB);

int main(int argc, char **argv) {
  PrimeList primeList;
  IntList indexLists[100000];
  IntList* matchCompares[5];
  IntList* nextList;
  int index = 170;
  bool done = false;
  bool containNum;
  bool allCombinationsTested;
  int mcNum;

  while(!done){
    indexLists[index].num = new int(index);
//    if(primeList.returnPrime(index) == 55621 || primeList.returnPrime(index) == 18493 || primeList.returnPrime(index) == 991 || primeList.returnPrime(index) == 883 || primeList.returnPrime(index) == 733)
//      cout << primeList.returnPrime(index);
    for(int i=0; i<index; i++){
      if(primeList.isPrime((combine(primeList.returnPrime(index), primeList.returnPrime(i)))) && primeList.isPrime((combine(primeList.returnPrime(i), primeList.returnPrime(index))))){
//        if(primeList.returnPrime(index) == 55621 || primeList.returnPrime(index) == 18493 || primeList.returnPrime(index) == 991 || primeList.returnPrime(index) == 883 || primeList.returnPrime(index) == 733)
//          cout << ", " << primeList.returnPrime(i);
        indexLists[index].addAfter(i);
      }
    }
//    if(primeList.returnPrime(index) == 55621 || primeList.returnPrime(index) == 18493 || primeList.returnPrime(index) == 991 || primeList.returnPrime(index) == 883 || primeList.returnPrime(index) == 733)
//      cout << endl;
    matchCompares[0] = &indexLists[index];
    mcNum = 0;
    while(mcNum < 5 && matchCompares[mcNum]->next){
      mcNum++;
      matchCompares[mcNum] = matchCompares[mcNum-1]->next;
    }
    if(mcNum==5){
      allCombinationsTested = false;
      while(!allCombinationsTested){
        containNum = true;
        for(int i=1; i<5 && containNum; i++){
          for(int i2=i+1; i2<5 && containNum; i2++){
            containNum = false;
            nextList = &indexLists[*matchCompares[i]->num];
            while(!containNum && nextList->next){
              nextList = nextList->next;
              if(*nextList->num == *matchCompares[i2]->num)
                containNum = true;
            }
          }
        }
        if(containNum){
          cout << "Answer: " << primeList.returnPrime(*matchCompares[0]->num);
          for(int i=1; i<5; i++)
            cout << ", " << primeList.returnPrime(*matchCompares[i]->num);
          cout << endl;
          done = true;
        }
        if(matchCompares[4]->next)
          matchCompares[4] = matchCompares[4]->next;
        else{
          if(matchCompares[3]->next != matchCompares[4])
            matchCompares[3] = matchCompares[3]->next;
          else{
            if(matchCompares[2]->next != matchCompares[3])
              matchCompares[2] = matchCompares[2]->next;
            else{
              if(matchCompares[1]->next != matchCompares[2])
                matchCompares[1] = matchCompares[1]->next;
              else{
                  allCombinationsTested = true;
              }
              matchCompares[2] = matchCompares[1]->next;
            }
            matchCompares[3] = matchCompares[2]->next;
          }
          matchCompares[4] = matchCompares[3]->next;
        }
      }
    }
    index++;
  }

  return 0;
}

int digits(int64_t num){
	int digits=0;
	if(num<1)
		return 1;
	while(num!=0){
		digits++;
		num/=10;
	}
	return digits;
}

int64_t combine(int64_t numA, int64_t numB){
	int dig = digits(numB);
	int64_t ans = numA;
	for(int i = 0; i<dig; i++)
    ans = ans*10;
	ans = ans+numB;
	return ans;
}

IntList::IntList(){
  if(DEBUG)
    cout << "IntList() " << this << endl;
  next = NULL;
  previous = NULL;
  num = NULL;
}

IntList::IntList(const int& num){
  if(DEBUG)
    cout << "IntList(num) " << this << endl;
  this->num = new int(num);
  next = NULL;
  previous = NULL;
}

IntList::~IntList(){
  if(DEBUG)
    cout << "~IntList() " << this << endl;
  if(previous)
    previous->next=next;
  if(next)
    next->previous=previous;
  delete num;
}

bool IntList::addAfter(const int& num){
  if(DEBUG)
    cout << "addAfter() " << this << endl;
  IntList* newIntList = new IntList(num);
  if(next){
    newIntList->next = next;
    next->previous = newIntList;
  }
  newIntList->previous=this;
  next = newIntList;
  return true;
}

bool IntList::addBefore(const int& num){
  if(DEBUG)
    cout << "addbefore() " << this << endl;
  IntList* newIntList = new IntList(num);
  if(previous){
    newIntList->previous = previous;
    previous->next = newIntList;
  }
  newIntList->next=this;
  previous = newIntList;
  return true;
}

IntList* IntList::myAnd(IntList* other){
  IntList* next = this;
  IntList* otherNext = other;
  IntList* result = NULL;
  do{
    otherNext = other;
    do{
      if(*next->num == *other->num){
        if(result)
          result->addAfter(*next->num);
        else
          result = new IntList(*next->num);
      }
      otherNext = other->next;
    }while(otherNext);
    next = next->next;
  }while(next);
  return result;
}


