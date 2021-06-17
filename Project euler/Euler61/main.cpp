#include <iostream>

#ifndef MAX_ARRAY_SIZE
#define MAX_ARRAY_SIZE 1000
#endif

using namespace std;

class numberLists{
public:

  int n3[MAX_ARRAY_SIZE];
  int n4[MAX_ARRAY_SIZE];
  int n5[MAX_ARRAY_SIZE];
  int n6[MAX_ARRAY_SIZE];
  int n7[MAX_ARRAY_SIZE];
  int n8[MAX_ARRAY_SIZE];
  int n3Count;
  int n4Count;
  int n5Count;
  int n6Count;
  int n7Count;
  int n8Count;

  numberLists();
  bool makeN3();
  bool makeN4();
  bool makeN5();
  bool makeN6();
  bool makeN7();
  bool makeN8();
  bool testRule2(int* numberSet);
  bool findSet();
};

int main()
{
    cout << "Creating lists..." << endl;
    numberLists list;
    cout << "Triangle numbers: " << list.n3Count << endl;
    cout << "Square numbers: " << list.n4Count << endl;
    cout << "Pentagonal numbers: " << list.n5Count << endl;
    cout << "Hexagonal numbers: " << list.n6Count << endl;
    cout << "Heptagonal numbers: " << list.n7Count << endl;
    cout << "Octagonal numbers: " << list.n8Count << endl;
    return 0;
}

numberLists::numberLists(){
  n3Count=0;
  n4Count=0;
  n5Count=0;
  n6Count=0;
  n7Count=0;
  n8Count=0;
  if(!makeN3())
    cout << "ARRAY SIZE TO SMALL!!!!"<<endl;
  if(!makeN4())
    cout << "ARRAY SIZE TO SMALL!!!!"<<endl;
  if(!makeN5())
    cout << "ARRAY SIZE TO SMALL!!!!"<<endl;
  if(!makeN6())
    cout << "ARRAY SIZE TO SMALL!!!!"<<endl;
  if(!makeN7())
    cout << "ARRAY SIZE TO SMALL!!!!"<<endl;
  if(!makeN8())
    cout << "ARRAY SIZE TO SMALL!!!!"<<endl;
}

bool numberLists::makeN3(){
  int n=1;
  int add=1;
  while(n<10000){
    add++;
    n=n+add;
    if(n>999){
      if(n3Count>=MAX_ARRAY_SIZE)
        return false;
      n3[n3Count] = n;
      n3Count++;
    }
  }
  return true;
}

bool numberLists::makeN4(){
  int n=1;
  int add=1;
  while(n<10000){
    add+=2;
    n=n+add;
    if(n>999){
      if(n4Count>=MAX_ARRAY_SIZE)
        return false;
      n4[n4Count] = n;
      n4Count++;
    }
  }
  return true;
}

bool numberLists::makeN5(){
  int n=1;
  int add=1;
  while(n<10000){
    add+=3;
    n=n+add;
    if(n>999){
      if(n5Count>=MAX_ARRAY_SIZE)
        return false;
      n5[n5Count] = n;
      n5Count++;
    }
  }
  return true;
}

bool numberLists::makeN6(){
  int n=1;
  int add=1;
  while(n<10000){
    add+=4;
    n=n+add;
    if(n>999){
      if(n6Count>=MAX_ARRAY_SIZE)
        return false;
      n6[n6Count] = n;
      n6Count++;
    }
  }
  return true;
}

bool numberLists::makeN7(){
  int n=1;
  int add=1;
  while(n<10000){
    add+=5;
    n=n+add;
    if(n>999){
      if(n7Count>=MAX_ARRAY_SIZE)
        return false;
      n7[n7Count] = n;
      n7Count++;
    }
  }
  return true;
}

bool numberLists::makeN8(){
  int n=1;
  int add=1;
  while(n<10000){
    add+=6;
    n=n+add;
    if(n>999){
      if(n8Count>=MAX_ARRAY_SIZE)
        return false;
      n8[n8Count] = n;
      n8Count++;
    }
  }
  return true;
}

bool numberLists::testRule2(int* numberSet){
  bool contain[6];
  int index;
  for(int i=0; i<6; i++)
    contain[i] = false;
  for(int i=0; i<6; i++){
    index=0;
    while(index<n3Count && n3[index]<=numberSet[i]){
      if(n3[index]==numberSet[i])
        contain[0] = true;
    }
    index=0;
    while(index<n4Count && n4[index]<=numberSet[i]){
      if(n4[index]==numberSet[i])
        contain[1] = true;
    }
    index=0;
    while(index<n5Count && n5[index]<=numberSet[i]){
      if(n5[index]==numberSet[i])
        contain[2] = true;
    }
    index=0;
    while(index<n6Count && n6[index]<=numberSet[i]){
      if(n6[index]==numberSet[i])
        contain[3] = true;
    }
    index=0;
    while(index<n7Count && n7[index]<=numberSet[i]){
      if(n7[index]==numberSet[i])
        contain[4] = true;
    }
    index=0;
    while(index<n8Count && n8[index]<=numberSet[i]){
      if(n8[index]==numberSet[i])
        contain[5] = true;
    }
  }
  for(int i=0; i<10; i++){
    if(!contain[i])
      return false;
  }
  return true;
}

bool numberLists::findSet(){
  int c;
  int lastA;
  int lastB;
  for(int a=1000; a<10000; a++){
    lastA = a-a/100*100;
    if(lastA>9){
      for(int b=lastA*100; b<10000){
        lastB = b-b/100*100;
        if(lastB>9){
          c = lastB+lastA/100;
          if(testRule2){

          }
        }
      }
    }
  }
}
