#include "ArnesTree.h"

ArnesTree::ArnesTree()
{
  //ctor
}

ArnesTree::~ArnesTree()
{
  //dtor
}

void ArnesTree::leftRot(ArnesNode* t){
  ArnesNode* tmp = t;
  t = t->right();
  tmp->right(t->left());
  t->left = tmp;
}

void ArnesTree::rightRot(ArnesNode* t){
  ArnesNode* tmp = t;
  t = t->left();
  tmp->left(t->right());
  t->right = tmp;
}

void ArnesTree::skew(ArnesNode* t){
  do {
    while(t->left())
      rightRot(t);
    t = t->right();
  }while(t);
}

void ArnesTree::split(ArnesNode* t, int p1, int p2){
  int incr = p1-p2;
  int count = 0;
  for(int i=p2; i>0; i--){
    count += incr;
    if(count >= p2){
      leftRot(t);
      count -= p2;
    }
    t = t->right();
  }
}

void ArnesTree::PerfectBalance(ArnesNode* t, int w){
  int b = 1;
  skew(t);
  while(b <= w)
    b *= 2;
  b /= 2;
  if(b != w)
    split(t, w-1, b-1);
  while(b > 2){
    split(t, b-1, b/2-1);
    b /= 2;
  }
}

int ArnesTree: treeWeight(ArnesNode* t){
  ArnesNode* stack[40];
  int top=0;
  int w=1;
  stack[0] = nullptr;
  while(t){
    while(t->left()){
      w++;
      if(t->right()){
        top++;
        stack[top] = t;
      }
      t = t->left();
    }
    w++;
    if(!t->right()){
      t=stack[top];
      top--;
    }
    t = t->right();
  }
  return w;
}

void ArnesNode::fixBalance()

ArnesTree::ArnesNode()
{
  //ctor
}

ArnesTree::~ArnesNode()
{
  //dtor
}
