#include "Btree.h"

Leaf::Leaf(){
  left = nullptr;
  right = nullptr;
}

Leaf::Leaf(int value){
  this->value = value;
  left = nullptr;
  right = nullptr;
}

Leaf::~Leaf(){
  if(left)
    delete left;
  if(right)
    delete right;
}

void Leaf::insert(int value){
  if(value<this->value){
    if(left)
      left->insert(value);
    else
      left = new Leaf(value);
  }
  else if(value>this->value){
    if(right)
      right->insert(value);
    else
      right = new Leaf(value);
  }
}

Leaf* Leaf::search(int value){
  if(value == this->value)
    return this;
  if(value < this->value)
    return left->search(value);
  return right->search(value);
}

void Leaf::print(){
  if(left)
    left->print();
  cout << value << " ";
  if(right)
    right->print();
}

void Leaf::printWeight(int level){
  int leftHeight = 0;
  int rightHeight = 0;
  if(left)
    leftHeight = left->getHeight();
  if(right)
    rightHeight = right->getHeight();
  cout << value << " " << level << ": " << leftHeight << " " << rightHeight << endl;
  if(left)
    left->printWeight(level+1);
  if(right)
    right->printWeight(level+1);
}

void Leaf::printChildren(){
  int leftChild = 0;
  int rightChild = 0;
  if(left)
    leftChild = left->value;
  if(right)
    rightChild = right->value;
  cout << value << ": " << leftChild << " " << rightChild << endl;
  if(left)
    left->printChildren();
  if(right)
    right->printChildren();
}

int Leaf::getHeight(){
  int leftHeight = 0;
  int rightHeight = 0;
  if(left)
    leftHeight = left->getHeight();
  if(right)
    rightHeight = right->getHeight();
  if(leftHeight>rightHeight)
    return leftHeight+1;
  return rightHeight+1;
}

Leaf* Leaf::rotLeft(){
  Leaf* temp = right->left;
  Leaf* ret = right;
  right->left = this;
  right = temp;
  return ret;
}

Leaf* Leaf::rotRight(){
  Leaf* temp = left->right;
  Leaf* ret = left;
  left->right = this;
  left = temp;
  return ret;
}

void Leaf::balance(){
  Leaf* side;
  for(int i=0; i<2; i++){
    Leaf* newSide = nullptr;
    if(i==0)
      side=left;
    else
      side=right;
    int oldRot = NOROT;
    bool done = false;
    while(side && !done){
      int leftHeight = 0;
      int rightHeight = 0;
      if(side->left)
        leftHeight = side->left->getHeight();
      if(side->right)
        rightHeight = side->right->getHeight();
      if(leftHeight > rightHeight+1){
        if(oldRot==LEFT)
          done = true;
        else{
          newSide = side->rotRight();
          side = newSide;
          oldRot=RIGHT;
        }
      }
      else if(rightHeight > leftHeight+1){
        if(oldRot==RIGHT)
          done = true;
        else{
          newSide = side->rotLeft();
          side = newSide;
          oldRot=LEFT;
        }
      }
      else
        done = true;
    }
    if(side && newSide){
      if(i==0){
        left = newSide;
        left->balance();
      }
      else{
        right = newSide;
        right->balance();
      }
    }
  }
}

Btree::Btree(){
  root = nullptr;
}

Btree::Btree(int value){
  root = new Leaf(value);
}

Btree::~Btree(){
  if(root)
    delete root;
}

void Btree::insert(int value){
  if(root)
    root->insert(value);
  else
    root = new Leaf(value);
}

Leaf* Btree::search(int value){
  if(!root)
    return nullptr;
  return root->search(value);
}

void Btree::print(){
  if(!root)
    return;
  root->print();
}

void Btree::printWeight(){
  if(!root)
    return;
  root->printWeight(1);
}

void Btree::printChildren(){
  if(!root)
    return;
  root->printChildren();
}

void Btree::balance(){
  if(!root)
    return;
  Leaf* newSide = nullptr;
  int oldRot = NOROT;
  bool done = false;
  while(!done){
    int leftHeight = 0;
    int rightHeight = 0;
    if(root->left)
      leftHeight = root->left->getHeight();
    if(root->right)
      rightHeight = root->right->getHeight();
    if(leftHeight > rightHeight+1){
      if(oldRot==LEFT)
        done = true;
      else{
        newSide = root->rotRight();
        if(newSide)
          root = newSide;
        oldRot=RIGHT;
      }
    }
    else if(rightHeight > leftHeight+1){
      if(oldRot==RIGHT)
        done = true;
      else{
        newSide = root->rotLeft();
        if(newSide)
          root = newSide;
        oldRot=LEFT;
      }
    }
    else
      done = true;
  }
  root->balance();
}
