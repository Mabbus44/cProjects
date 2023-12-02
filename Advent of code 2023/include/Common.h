#ifndef COMMON_H
#define COMMON_H
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class InputLoader
{
  public:
    InputLoader(){};
    InputLoader(string filename);
    virtual ~InputLoader();
    void resetFile();
    static vector<string> splitString(string s, vector<string> delimiters = {", "});
    static vector<int> toInt(vector<string> vs);
    static string ltrim(string s);
    static string rtrim(string s);
    static string trim(string s);
    vector<int> toVectorInt();
    vector<vector<int>> toVectorInt2d(vector<string> delimiters = {", "});
    vector<string> toVectorStr();
    vector<vector<string>> toVectorStr2d(vector<string> delimiters = {", "});
    vector<vector<char>> toVectorChar2d();

  protected:

  private:
    ifstream _file;
};

template <class T>
class BtNode
{
  public:
    BtNode(){}
    BtNode(T val){this->val = val;}
    virtual ~BtNode(){};
    bool insert(T iVal);
    int count();
    void clear();
    T val;
    BtNode* left=nullptr;
    BtNode* right=nullptr;
};

template <class T>
bool BtNode<T>::insert(T iVal){
  if(iVal > val){
    if(right){
      return right->insert(iVal);
    }else{
      right = new BtNode<T>(iVal);
    }
    return true;
  }
  if(iVal < val){
    if(left){
      return left->insert(iVal);
    }else{
      left = new BtNode<T>(iVal);
    }
    return true;
  }
  return false;
}

template <class T>
int BtNode<T>::count(){
  int c=1;
  if(left)
    c+=left->count();
  if(right)
    c+=right->count();
  return c;
}

template <class T>
void BtNode<T>::clear(){
  if(left){
    left->clear();
    delete left;
    left = nullptr;
  }
  if(right){
    right->clear();
    delete right;
    right = nullptr;
  }
}

#endif // COMMON_H
