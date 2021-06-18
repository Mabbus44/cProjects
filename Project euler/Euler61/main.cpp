#include <iostream>
#include <list>

using namespace std;

bool findNextNum(int firstNum, int num, list<int>* p4, list<int>* p5, list<int>* p6, list<int>* p7, list<int>* p8);

int main()
{
    list<int> polygonals[6];
    int n, result;

    for(int i=0; i<6; i++){
      n=1;
      result=0;
      while(result<10000){
        if(result>999)
          polygonals[i].push_back(result);
        n++;
        switch(i){
          case 0:
            result = n*(n+1)/2;
            break;
          case 1:
            result = n*n;
            break;
          case 2:
            result = n*(3*n-1)/2;
            break;
          case 3:
            result = n*(2*n-1);
            break;
          case 4:
            result = n*(5*n-3)/2;
            break;
          case 5:
            result = n*(3*n-2);
            break;
        }
      }
    }
    for (int p3 : polygonals[0]) {
      findNextNum(p3, p3, &polygonals[1], &polygonals[2], &polygonals[3], &polygonals[4], &polygonals[5]);
    }

    return 0;
}

bool findNextNum(int firstNum, int num, list<int>* p4, list<int>* p5, list<int>* p6, list<int>* p7, list<int>* p8){
  if(!p4 && !p5 && !p6 && !p7 && !p8){
    if(firstNum/100 == num%100){
      cout << num << " : ";
      return true;
    }
  }
  if(p4)
    for(int num2 : *p4)
      if(num%100 == num2/100)
        if(findNextNum(firstNum, num2, nullptr, p5, p6, p7, p8)){
          cout << num << " : ";
          return true;
        }
  if(p5)
    for(int num2 : *p5)
      if(num%100 == num2/100)
        if(findNextNum(firstNum, num2, p4, nullptr, p6, p7, p8)){
          cout << num << " : ";
          return true;
        }
  if(p6)
    for(int num2 : *p6)
      if(num%100 == num2/100)
        if(findNextNum(firstNum, num2, p4, p5, nullptr, p7, p8)){
          cout << num << " : ";
          return true;
        }
  if(p7)
    for(int num2 : *p7)
      if(num%100 == num2/100)
        if(findNextNum(firstNum, num2, p4, p5, p6, nullptr, p8)){
          cout << num << " : ";
          return true;
        }
  if(p8)
    for(int num2 : *p8)
      if(num%100 == num2/100)
        if(findNextNum(firstNum, num2, p4, p5, p6, p7, nullptr)){
          cout << num << " : ";
          return true;
        }
  return false;
}
