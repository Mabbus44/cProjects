#ifndef DAY24_H
#define DAY24_H
#include <iostream>
#include <vector>
#include "Common.h"

enum instructions {INP, ADD, MUL, DIV, MOD, EQL};
enum variableTypes {NUMBER, REFERENCE};

class Variable{
public:
  Variable(){};
  Variable(int t, int64_t v, int64_t* r){type=t; val=v; varRef=r;/*cout << "Variable(data)"<<endl; output(); cout << endl;*/}
  Variable(const Variable& v){type=v.type; val=v.val; varRef=v.varRef;/*cout << "Variable(&variable)"<<endl; output(); cout << endl;*/}
  virtual ~Variable(){};
  Variable& operator=(const Variable& v){type=v.type; val=v.val; varRef=v.varRef; /*cout << "Variable="<<endl; output(); cout << endl;*/return *this;}
  void output();
  int64_t getVal();
  int type;
  int64_t val;
  int64_t* varRef;
};

class Instruction{
public:
  Instruction(){};
  Instruction(int t, Variable a, Variable b){type=t; varA=a; varB=b;/*cout << "Instruction(data)"<<endl; output(); cout << endl;*/}
  Instruction(const Instruction& i){type=i.type; varA=i.varA; varB=i.varB;/*cout << "Instruction(&Instruction)"<<endl; output(); cout << endl;*/}
  virtual ~Instruction(){};
  Instruction& operator=(const Instruction& i){type=i.type; varA=i.varA; varB=i.varB;/*cout << "Instruction="<<endl; output(); cout << endl;*/return *this;}
  void output();
  void execute(vector<int64_t>& inputs, bool debug=false);
  int type;
  Variable varA, varB;
};

class ALU{
public:
  ALU(){};
  virtual ~ALU(){};
  void loadInstruction(InputLoader& loader, string line);
  void output();
  /*void zx26();
  void zdiv26();*/
  int execute(bool debug=false);
  vector<Instruction*> instructions;
  vector<int64_t> inputs;
  int64_t inputNum[14] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1};
  //int64_t inputNum[14] = {9,9,3,9,1,8,9,9,8,9,1,9,7,2};
  int64_t k1[14] = {11, 13, 15, -8, 13, 15, -11, -4, -15, 14, 14, -1, -8, -14};
  int64_t k2[14] = {6, 14, 14, 10, 9, 12, 8, 13, 12, 6, 9, 15, 4, 10};
  bool d[14] = {false, false, false, true, false, false, true, true, true, false, false, true, true, true};
  int64_t zMax[14] = {26*26*26*26*26*26, 26*26*26*26*26*26, 26*26*26*26*26*26, 26*26*26*26*26*26, 26*26*26*26*26*26, 26*26*26*26*26*26, 26*26*26*26*26*26, 26*26*26*26*26, 26*26*26*26, 26*26*26, 26*26*26, 26*26*26, 26*26, 26};
  int64_t w,x,y,z;
};

class Day24
{
  public:
    Day24();
    virtual ~Day24();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY24_H
