#ifndef CLAIM_H
#define CLAIM_H
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "functions.h"

using namespace std;

class Claim
{
  public:
    int id;
    int posX, posY;
    int sizeX, sizeY;
    Claim();
    Claim(string line);
    virtual ~Claim();
    void loadData(string line);
    void output();

  protected:

  private:
};

#endif // CLAIM_H
