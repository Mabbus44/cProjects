#include "Day18.h"

void SFNumber::load(string& input){
  if(input[0] == '['){
    input.erase(0,1);
    leftChild = new SFNumber(this);
    rightChild = new SFNumber(this);
    leftChild->load(input),
    input.erase(0,1);
    rightChild->load(input),
    input.erase(0,1);
  }else{
    val=(int)(input[0])-48;
    input.erase(0,1);
  }
}

void SFNumber::free(){
  if(val==-1){
    leftChild->free();
    rightChild->free();
    delete leftChild;
    delete rightChild;
  }
}

void SFNumber::output(){
  if(val>-1)
    cout << val;
  else{
    cout << "[";
    leftChild->output();
    cout << ",";
    rightChild->output();
    cout << "]";
  }
}

void SFNumber::addLeft(int num){
  if(val != -1){
    val += num;
    return;
  }
  leftChild->addLeft(num);
}

void SFNumber::addRight(int num){
  if(val != -1){
    val += num;
    return;
  }
  rightChild->addRight(num);
}

void SFNumber::addLeftOfMe(SFNumber* me, int num){
  if(rightChild == me)
    leftChild->addRight(num);
  else if(parent){
    parent->addLeftOfMe(this, num);
  }
}

void SFNumber::addRightOfMe(SFNumber* me, int num){
  if(leftChild == me)
    rightChild->addLeft(num);
  else if(parent){
    parent->addRightOfMe(this, num);
  }
}

bool SFNumber::explode(int level){
  if(val!=-1)
    return false;
  level++;
  if(level >= 4 && leftChild->val == -1 && leftChild->leftChild->val != -1 && leftChild->rightChild->val != -1){//Explode left child
    if(parent)
      parent->addLeftOfMe(this, leftChild->leftChild->val);
    rightChild->addLeft(leftChild->rightChild->val);
    leftChild->free();
    leftChild->val = 0;
    return true;
  }
  if(level >= 4 && rightChild->val == -1 && rightChild->leftChild->val != -1 && rightChild->rightChild->val != -1){//Explode right child
    if(parent)
      parent->addRightOfMe(this, rightChild->rightChild->val);
    leftChild->addRight(rightChild->leftChild->val);
    rightChild->free();
    rightChild->val = 0;
    return true;
  }
  if(leftChild->val != -1 || !leftChild->explode(level)){
    if(rightChild->val == -1){
      return rightChild->explode(level);
    }
    return false;
  }
  return true;
}

bool SFNumber::split(){
  if(val==-1){
    if(leftChild->split())
      return true;
    if(rightChild->split())
      return true;
    return false;
  }
  if(val<10)
    return false;
  leftChild = new SFNumber(this);
  leftChild->val=val/2;
  rightChild = new SFNumber(this);
  rightChild->val=val/2;
  if(val%2==1)
    rightChild->val++;
  val = -1;
  return true;
}

SFNumber* SFNumber::add(SFNumber* other, bool output){
  SFNumber* ret = new SFNumber();
  ret->leftChild = this;
  ret->rightChild = other;
  parent = ret;
  other->parent = ret;
  bool done=false;
  if(output){
    ret->output();
    cout << endl;
  }
  while(!done){
    done = true;
    while(ret->explode(0)){
      done = false;
      if(output){
        cout << "Explode" << endl;
        ret->output();
        cout << endl;
      }
    }
    if(ret->split()){
      done = false;
      if(output){
        cout << "split" << endl;
        ret->output();
        cout << endl;
      }
    }
  }
  return ret;
}

int SFNumber::magnigude(){
  if(val!=-1)
    return val;
  return 3*leftChild->magnigude()+2*rightChild->magnigude();
}

Day18::Day18()
{
  //ctor
}

Day18::~Day18()
{
  //dtor
}

void Day18::part1(string filename){
  InputLoader loader(filename);
  vector<string> inputs = loader.toVectorStr();
  vector<SFNumber*> numbers;
  for(string input:inputs){
    SFNumber* num = new SFNumber();
    num->load(input);
    numbers.push_back(num);
  }
  SFNumber* ans=numbers[0];
  for(int i=1; i<(int)numbers.size(); i++){
    ans = ans->add(numbers[i]);
  }
  cout << "Part 1: " << ans->magnigude() << endl;
}

void Day18::part2(string filename){
  InputLoader loader(filename);
  vector<string> inputs = loader.toVectorStr();
  int maxMagnitude = 0;
  for(int i1=0; i1<(int)inputs.size(); i1++){
    for(int i2=0; i2<(int)inputs.size(); i2++){
      if(i1!=i2){
        SFNumber* a = new SFNumber();
        SFNumber* b = new SFNumber();
        SFNumber* res;
        string input1 = inputs[i1];
        string input2 = inputs[i2];
        a->load(input1);
        b->load(input2);
        res = a->add(b);
        if(res->magnigude()>maxMagnitude)
          maxMagnitude = res->magnigude();
        res->free();
        delete res;
      }
    }
  }
  cout << "Part 2: " << maxMagnitude << endl;
}
