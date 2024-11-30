#ifndef COMMON_H
#define COMMON_H
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

class InputLoader
{
  public:
    InputLoader(){};
    InputLoader(std::string filename);
    virtual ~InputLoader();
    void resetFile();
    static std::vector<std::string> splitString(std::string s, std::vector<std::string> delimiters = {", "});
    static std::vector<int> toInt(std::vector<std::string> vs);
    static int toSingleInt(std::string s);
    static std::vector<__int64> toInt64(std::vector<std::string> vs);
    static std::string ltrim(std::string s);
    static std::string rtrim(std::string s);
    static std::string trim(std::string s);
    std::vector<int> toVectorInt();
    std::vector<std::vector<int>> toVectorInt2d(std::vector<std::string> delimiters = {", "});
    std::vector<std::string> toVectorStr();
    std::vector<std::vector<std::string>> toVectorStr2d(std::vector<std::string> delimiters = {", "});
    std::vector<std::vector<char>> toVectorChar2d();

  protected:

  private:
    std::ifstream _file;
};

class PrimeFactorizer{
  public:
    PrimeFactorizer(){findNewPrimes(1000);}
    virtual ~PrimeFactorizer(){}
    void findNewPrimes(int maxVal);
    bool isPrime(int num);
    std::vector<int> factorize(int num);
  private:
    std::vector<int> _primes;
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
