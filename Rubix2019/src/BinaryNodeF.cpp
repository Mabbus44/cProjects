#include <iostream>
#include "RubixCube20BF.h"
#include "FileHandler.h"
#include "BinaryNodeF.h"

BinaryNodeF::BinaryNodeF()
{
  adress = 0;
  parent = 0;
  smallerChild = 0;
  biggerChild = 0;
  height = 0;
}

BinaryNodeF::~BinaryNodeF()
{
  //dtor
}

bool BinaryNodeF::find(RubixCube20BF* other, FileHandler* fh)
{
  RubixCube20BF* cube = fh->loadCube(this->adress);
  int seb = cube->seb(other);
  delete cube;
  if(seb==SMALLER)
  {
    if(this->biggerChild > 0)
    {
      BinaryNodeF* bc = fh->loadNode(this->biggerChild);
      bool ret = bc->find(other, fh);
      delete bc;
      return ret;
    }
    else
      return false;
  }
  if(seb==BIGGER)
  {
    if(this->smallerChild > 0)
    {
      BinaryNodeF* sc = fh->loadNode(this->smallerChild);
      bool ret = sc->find(other, fh);
      delete sc;
      return ret;
    }
    else
      return false;
  }
  return true;  //seb==EQUALS
}

bool BinaryNodeF::insert(RubixCube20BF* newCube, FileHandler* fh)
{
  BinaryNodeF* curr = this;
  BinaryNodeF* child = NULL;
  __int64 lowestRoot = 0;
  int seb;
  bool addRoots = false;
  bool done = false;
  __int64 leftHeight;
  __int64 rightHeight;
  __int64 newHeight;
  int rotCount = 0;
  int lastDirection = 0;
  while(!done)
  {
    //Check if new cube is smaller or bigger and store height of legs
    RubixCube20BF* cube = fh->loadCube(curr->adress);
    seb = cube->seb(newCube);
    delete cube;
    if(seb == BIGGER)   //If new cube is smaller add it to left leg and save nodes if they should be rotated
    {
      if(curr->smallerChild > 0)
      {
        child = fh->loadNode(curr->smallerChild);
        leftHeight = child->height + 1;
      }
      else
        leftHeight = 0;
      if(curr->biggerChild > 0)
        rightHeight = fh->loadNodeHeight(curr->biggerChild) + 1;
      else
        rightHeight = 0;
      if(leftHeight == 0)
      {
        BinaryNodeF* newNode = new BinaryNodeF;
        newNode->parent = curr->adress;
        newNode->adress = newCube->adress;
        curr->smallerChild = newCube->adress;
        fh->saveNodeSmallerChild(curr->adress, curr->smallerChild);
        fh->saveNode(newNode);
        delete newNode;
        done = true;
      }
      if(leftHeight > rightHeight)
      {
        lowestRoot = curr->smallerChild;
        addRoots = true;
        rotCount = 1;
        lastDirection = LEFT;
      }
      else if(leftHeight == rightHeight && addRoots)
      {
        if(lastDirection == RIGHT)
        {
          lowestRoot = curr->smallerChild;
          rotCount++;
          lastDirection = LEFT;
        }
        else
          addRoots = false;
      }
      else if(leftHeight < rightHeight && lowestRoot)
      {
        lowestRoot = 0;
        rotCount = 0;
        addRoots = false;
      }
    }
    if(seb == SMALLER)    //If new cube is bigger add it to right leg and save nodes if they should be rotated
    {
      if(curr->biggerChild > 0)
      {
        child = fh->loadNode(curr->biggerChild);
        rightHeight = child->height + 1;
      }
      else
        rightHeight = 0;
      if(curr->smallerChild > 0)
        leftHeight = fh->loadNodeHeight(curr->smallerChild) + 1;
      else
        leftHeight = 0;
      if(rightHeight == 0)
      {
        BinaryNodeF* newNode = new BinaryNodeF;
        newNode->parent = curr->adress;
        newNode->adress = newCube->adress;
        curr->biggerChild = newCube->adress;
        fh->saveNodeBiggerChild(curr->adress, curr->biggerChild);
        fh->saveNode(newNode);
        delete newNode;
        done = true;
      }
      if(rightHeight > leftHeight)
      {
        lowestRoot = curr->biggerChild;
        addRoots = true;
        rotCount = 1;
        lastDirection = RIGHT;
      }
      else if(rightHeight == leftHeight && addRoots)
      {
        if(lastDirection == LEFT)
        {
          lowestRoot = curr->biggerChild;
          rotCount++;
          lastDirection = RIGHT;
        }
        else
          addRoots = false;
      }
      else if(rightHeight < leftHeight && lowestRoot)
      {
        lowestRoot = 0;
        rotCount = 0;
        addRoots = false;
      }
    }
    if(curr!=this)
      delete curr;
    curr = child;
    if(seb == EQUALS)   //If new cube is equal then don't add it and return false. This should not happend since we check "Find" before we "Insert"
      return false;
  }

  //Rebalance tree;
  if(lowestRoot)
  {
    BinaryNodeF* lr = fh->loadNode(lowestRoot);
    for(int i=0; i<rotCount; i++)
      lr->rotUp(fh);
    fh->saveNode(lr);
    delete lr;
  }

  //Increase height
  int done2 = 0;
  __int64 hAdress = newCube->adress;
  while(done2 != 2)
  {
    child = fh->loadNode(hAdress);
    if(child->smallerChild)
      leftHeight = fh->loadNodeHeight(child->smallerChild) + 1;
    else
      leftHeight = 0;
    if(child->biggerChild)
      rightHeight = fh->loadNodeHeight(child->biggerChild) + 1;
    else
      rightHeight = 0;
    if(leftHeight > rightHeight)
      newHeight = leftHeight;
    else
      newHeight = rightHeight;
    if(done2 == 1 && child->height == newHeight)
      done2 = 2;
    child->height = newHeight;
    if(hAdress == lowestRoot)
      done2 = 1;
    if(child->parent)
      hAdress = child->parent;
    else
      done2 = 2;
    fh->saveNodeHeight(child->adress, child->height);
    delete child;
  }

  return true;
}

bool BinaryNodeF::rotUp(FileHandler* fh)
{
  int leftHeight, rightHeight;
  if(!this->parent)
    return false;
  BinaryNodeF* parent = fh->loadNode(this->parent);
  __int64 parentsParent = parent->parent;
  if(this->adress == parent->biggerChild) //Left rotation
  {
  /*   P
      / \
     N   C
        / \
      SC   BC     */
    parent->biggerChild = this->smallerChild;
    if(this->smallerChild)
      fh->saveNodeParent(this->smallerChild, this->parent);
    parent->parent = this->adress;
    this->smallerChild = this->parent;
    this->parent = parentsParent;
    if(parentsParent)
    {
      if(this->smallerChild == fh->loadNodeBiggerChild(parentsParent))
        fh->saveNodeBiggerChild(parentsParent, this->adress);
      else
        fh->saveNodeSmallerChild(parentsParent, this->adress);
    }
  }
  else if(this->adress == parent->smallerChild) //Right rotation
  {
  /*      P
         / \
        C   N
       / \
     SC   BC       */
    parent->smallerChild = this->biggerChild;
    if(this->biggerChild)
      fh->saveNodeParent(this->biggerChild, this->parent);
    parent->parent = this->adress;
    this->biggerChild = this->parent;
    this->parent = parentsParent;
    if(parentsParent)
    {
      if(this->biggerChild == fh->loadNodeBiggerChild(parentsParent))
        fh->saveNodeBiggerChild(parentsParent, this->adress);
      else
        fh->saveNodeSmallerChild(parentsParent, this->adress);
    }
  }
  //Recalculate height
  if(parent->smallerChild)
    leftHeight = fh->loadNodeHeight(parent->smallerChild) + 1;
  else
    leftHeight = 0;
  if(parent->biggerChild)
    rightHeight = fh->loadNodeHeight(parent->biggerChild) + 1;
  else
    rightHeight = 0;
  if(leftHeight > rightHeight)
    parent->height = leftHeight;
  else
    parent->height = rightHeight;
  fh->saveNode(parent);
  return true;
}

void BinaryNodeF::print(FileHandler* fh, bool verbose)
{
  std::cout << "Node adress: " << this->adress << std::endl;
  std::cout << "Parent: " << parent << std::endl;
  std::cout << "SmallerChild: " << smallerChild << std::endl;
  std::cout << "BiggerChild: " << biggerChild << std::endl;
  std::cout << "Height: " << height << std::endl;
  if(verbose)
  {
    RubixCube20BF* cube = fh->loadCube(adress);
    cube->print();
    delete cube;
  }
  else
    std::cout << std::endl;
}
