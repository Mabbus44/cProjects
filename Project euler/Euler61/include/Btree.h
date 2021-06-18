#ifndef BTREE_H
#define BTREE_H
#define LEFT -1
#define NOROT 0
#define RIGHT 1
#include <iostream>

using namespace std;


class Leaf
{
  public:
    int value;
    Leaf* left;
    Leaf* right;
    Leaf();
    Leaf(int value);
    ~Leaf();
    void insert(int value);
    Leaf* search(int value);
    void print();
    void printWeight(int level);
    void printChildren();
    int getHeight();
    Leaf* rotLeft();
    Leaf* rotRight();
    void balance();

  protected:

  private:
};

class Btree
{
  public:
    Btree();
    Btree(int value);
    ~Btree();
    void insert(int value);
    Leaf* search(int value);
    void print();
    void printWeight();
    void printChildren();
    void balance();

  protected:

  private:
    Leaf* root;
};

#endif // BTREE_H
