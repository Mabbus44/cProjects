#include "Day25.h"

Day25::Day25()
{
  //ctor
}

Day25::~Day25()
{
  //dtor
}

void Day25::part1(string filename){
  InputLoader loader(filename);
  vector<int> vi = loader.toVectorInt();
  __int64 cardPublicKey = vi[0];
  __int64 doorPublicKey = vi[1];

  __int64 cardLoop = findLoop(7, cardPublicKey);
  __int64 doorLoop = findLoop(7, doorPublicKey);

  __int64 encryptionKey1 = tform(doorPublicKey, cardLoop);
  __int64 encryptionKey2 = tform(cardPublicKey, doorLoop);
  if(encryptionKey1 != encryptionKey2)
    cout << "ERROR" << endl;

  cout << "part 1: " << encryptionKey1 << endl;
}

void Day25::part2(string filename){
  InputLoader loader(filename);
  cout << "part 2: " << endl;
}

__int64 Day25::tform(__int64 subject, __int64 loop){
  __int64 currVal = 1;
  for(int i=0; i<loop; i++){
    currVal = currVal*subject;
    currVal = currVal % 20201227;
  }
  return currVal;
}

__int64 Day25::findLoop(__int64 subject, __int64 target){
  __int64 currVal = 1;
  __int64 loop = 0;
  while(target != currVal){
    loop++;
    currVal = currVal*subject;
    currVal = currVal % 20201227;
  }
  return loop;
}
