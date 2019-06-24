#ifndef BINARYNODE_H
#define BINARYNODE_H
#include <list>

using namespace std;

template <class T>
class BinaryNode
{
  public:
    T* cubePointer;
    BinaryNode* parent;
    BinaryNode* smallerChild;
    BinaryNode* biggerChild;
    int height;
    BinaryNode();
    virtual ~BinaryNode();
    bool find(T* other);
    bool insert(T* newCube);
    bool rotUp();
    void print(bool verbose = false);

  protected:

  private:
};

template <class T>
BinaryNode<T>::BinaryNode()
{
  cubePointer = NULL;
  parent = NULL;
  smallerChild = NULL;
  biggerChild = NULL;
  height = 0;
}

template <class T>
BinaryNode<T>::~BinaryNode()
{
  //dtor
}

template <class T>
bool BinaryNode<T>::find(T* other)
{
  int seb = this->cubePointer->seb(other);
  if(seb==SMALLER)
  {
    if(this->biggerChild)
      return this->biggerChild->find(other);
    else
      return false;
  }
  if(seb==BIGGER)
  {
    if(this->smallerChild)
      return this->smallerChild->find(other);
    else
      return false;
  }
  return true;  //seb==EQUALS
}

template <class T>
bool BinaryNode<T>::insert(T* newCube)
{
  BinaryNode* curr = this;
  BinaryNode* lowestRoot = NULL;
  int seb;
  bool addRoots = false;
  bool done = false;
  int leftHeight;
  int rightHeight;
  int newHeight;
  //list<BinaryNode*> rotList;
  int rotCount = 0;
  while(!done)
  {
    //Check if new cube is smaller or bigger and store height of legs
    seb = curr->cubePointer->seb(newCube);
    if(curr->smallerChild)
      leftHeight = curr->smallerChild->height + 1;
    else
      leftHeight = 0;
    if(curr->biggerChild)
      rightHeight = curr->biggerChild->height + 1;
    else
      rightHeight = 0;
    if(seb == BIGGER)   //If new cube is smaller add it to left leg and save nodes if they should be rotated
    {
      if(leftHeight == 0)
      {
        BinaryNode<T>* newNode = new BinaryNode<T>;
        newNode->parent = curr;
        newNode->cubePointer = newCube;
        curr->smallerChild = newNode;
        done = true;
      }
      if(leftHeight > rightHeight)
      {
        lowestRoot = curr->smallerChild;
        addRoots = true;
        rotCount = 1;
        //rotList.push_front(lowestRoot);
      }
      else if(leftHeight == rightHeight && addRoots)
      {
        if(lowestRoot == lowestRoot->parent->biggerChild)
        {
          lowestRoot = curr->smallerChild;
          rotCount++;
          //rotList.push_front(lowestRoot);
        }
        else
          addRoots = false;
      }
      else if(leftHeight < rightHeight && lowestRoot)
      {
        lowestRoot = NULL;
        rotCount = 0;
        //rotList.clear();
        addRoots = false;
      }
      curr = curr->smallerChild;
    }
    if(seb == SMALLER)    //If new cube is bigger add it to right leg and save nodes if they should be rotated
    {
      if(rightHeight == 0)
      {
        BinaryNode<T>* newNode = new BinaryNode<T>;
        newNode->parent = curr;
        newNode->cubePointer = newCube;
        curr->biggerChild = newNode;
        done = true;
      }
      if(rightHeight > leftHeight)
      {
        lowestRoot = curr->biggerChild;
        addRoots = true;
        rotCount = 1;
        //rotList.push_front(lowestRoot);
      }
      else if(rightHeight == leftHeight && addRoots)
      {
        if(lowestRoot == lowestRoot->parent->smallerChild)
        {
          lowestRoot = curr->biggerChild;
          rotCount++;
          //rotList.push_front(lowestRoot);
        }
        else
          addRoots = false;
      }
      else if(rightHeight < leftHeight && lowestRoot)
      {
        lowestRoot = NULL;
        rotCount = 0;
        //rotList.clear();
        addRoots = false;
      }
      curr = curr->biggerChild;
    }
    if(seb == EQUALS)   //If new cube is equal then don't add it and return false
      return false;
  }

  //Rebalance tree;
  /*for(typename list<BinaryNode*>::iterator it=rotList.begin(); it != rotList.end(); ++it)
    (*it)->rotUp();*/
  for(int i=0; i<rotCount; i++)
    lowestRoot->rotUp();

  //Increase height
  int done2 = 0;
  while(done2 != 2)
  {
    if(curr->smallerChild)
      leftHeight = curr->smallerChild->height + 1;
    else
      leftHeight = 0;
    if(curr->biggerChild)
      rightHeight = curr->biggerChild->height + 1;
    else
      rightHeight = 0;
    if(leftHeight > rightHeight)
      newHeight = leftHeight;
    else
      newHeight = rightHeight;
    if(done2 == 1 && curr->height == newHeight)
      done2 = 2;
    curr->height = newHeight;
    if(curr == lowestRoot)
      done2 = 1;
    if(curr->parent)
      curr = curr->parent;
    else
      done2 = 2;
  }
  return true;
}

template <class T>
bool BinaryNode<T>::rotUp()
{
  int leftHeight, rightHeight, newHeight;
  if(!this->parent)
    return false;
  BinaryNode* oldParent = this->parent;
  if(this == this->parent->biggerChild) //Left rotation
  {
  /*   P
      / \
     N   C
        / \
      SC   BC     */
    BinaryNode* parentsParent = this->parent->parent;
    this->parent->biggerChild = this->smallerChild;
    if(this->smallerChild)
      this->smallerChild->parent = this->parent;
    this->parent->parent = this;
    this->smallerChild = this->parent;
    this->parent = parentsParent;
    if(parentsParent)
    {
      if(this->smallerChild == parentsParent->biggerChild)
        parentsParent->biggerChild = this;
      else
        parentsParent->smallerChild = this;
    }
  }
  else if(this == this->parent->smallerChild) //Right rotation
  {
  /*      P
         / \
        C   N
       / \
     SC   BC       */
    BinaryNode* parentsParent = this->parent->parent;
    this->parent->smallerChild = this->biggerChild;
    if(this->biggerChild)
      this->biggerChild->parent = this->parent;
    this->parent->parent = this;
    this->biggerChild = this->parent;
    this->parent = parentsParent;
    if(parentsParent)
    {
      if(this->biggerChild == parentsParent->biggerChild)
        parentsParent->biggerChild = this;
      else
        parentsParent->smallerChild = this;
    }
  }
  //Recalculate height
  if(oldParent->smallerChild)
    leftHeight = oldParent->smallerChild->height + 1;
  else
    leftHeight = 0;
  if(oldParent->biggerChild)
    rightHeight = oldParent->biggerChild->height + 1;
  else
    rightHeight = 0;
  if(leftHeight > rightHeight)
    newHeight = leftHeight;
  else
    newHeight = rightHeight;
  oldParent->height = newHeight;
  return true;
}

template <class T>
void BinaryNode<T>::print(bool verbose)
{
  std::cout << "Node: " << this << std::endl;
  std::cout << "Parent: " << parent << std::endl;
  std::cout << "smallerChild: " << smallerChild << std::endl;
  std::cout << "biggerChild: " << biggerChild << std::endl;
  std::cout << "height: " << height << std::endl;
  if(verbose)
    cubePointer->print();
  else
    std::cout << std::endl;
  if(smallerChild)
    smallerChild->print(verbose);
  if(biggerChild)
    biggerChild->print(verbose);
}

#endif // BINARYNODE_H
