#ifndef ROOTFRACTION_H
#define ROOTFRACTION_H

#include <list>
#include <map>

using namespace std;

class Abc{
  public:
    Abc();
    Abc(int a, int b, int c);
    int a;
    int b;
    int c;
    bool operator==(const Abc& other);
};

class RootFraction
{
  public:
    RootFraction();
    RootFraction(int n);
    ~RootFraction();

    void setN(int n);
    void nextFraction();
    void printFraction();
    int getPeriod(int n);

  protected:

  private:
    int a, b, c, m, n;
    list<Abc> fList;
};

#endif // ROOTFRACTION_H
