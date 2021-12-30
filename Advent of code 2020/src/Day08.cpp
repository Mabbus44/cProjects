#include "Day08.h"

void Instruction::output(){
  cout << instruction << " " << val << endl;
}

Day08::Day08()
{
  //ctor
}

Day08::~Day08()
{
  //dtor
}

void Day08::part1(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({" +", " "});
  vector<Instruction> vi;
  for(vector<string> vs:vvs){
    if(vs[0].compare("jmp")==0)
      vi.push_back(Instruction(JMP,stoi(vs[1])));
    if(vs[0].compare("acc")==0)
      vi.push_back(Instruction(ACC,stoi(vs[1])));
    if(vs[0].compare("nop")==0)
      vi.push_back(Instruction(NOP,stoi(vs[1])));
  }
  int pointer=0;
  int acc=0;
  while(!vi[pointer].run){
    vi[pointer].run=true;
    switch(vi[pointer].instruction){
      case NOP:
        pointer++;
        break;
      case ACC:
        acc += vi[pointer].val;
        pointer++;
        break;
      case JMP:
        pointer += vi[pointer].val;
        break;
    }
  }
  cout << "part 1: " << acc << endl;
}

void Day08::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({" +", " "});
  vector<Instruction> vi;
  for(vector<string> vs:vvs){
    if(vs[0].compare("jmp")==0)
      vi.push_back(Instruction(JMP,stoi(vs[1])));
    if(vs[0].compare("acc")==0)
      vi.push_back(Instruction(ACC,stoi(vs[1])));
    if(vs[0].compare("nop")==0)
      vi.push_back(Instruction(NOP,stoi(vs[1])));
  }
  bool done=false;
  int finalAcc;
  for(int firstSwap=0; firstSwap<(int)vi.size() && !done; firstSwap++){
    for(int secondSwap=firstSwap+1; secondSwap<(int)vi.size() && !done; secondSwap++){
      if(vi[firstSwap].instruction != ACC && vi[secondSwap].instruction != ACC && vi[firstSwap].instruction != vi[secondSwap].instruction){
        for(int i=0; i<(int)vi.size(); i++)
          vi[i].run=false;
        //cout << "Restarting " << firstSwap << " " << secondSwap << endl;
        int pointer=0;
        int acc=0;
        int otherInstruction = vi[firstSwap].instruction;
        vi[firstSwap].instruction = vi[secondSwap].instruction;
        vi[secondSwap].instruction = otherInstruction;
        while(pointer>=0 && pointer<(int)vi.size() && !vi[pointer].run){
          vi[pointer].run=true;
          switch(vi[pointer].instruction){
            case NOP:
              pointer++;
              break;
            case ACC:
              acc += vi[pointer].val;
              pointer++;
              break;
            case JMP:
              pointer += vi[pointer].val;
              break;
          }
        }
        if(pointer == (int)vi.size()){
          finalAcc = acc;
          done = true;
        }
        vi[secondSwap].instruction = vi[firstSwap].instruction;
        vi[firstSwap].instruction = otherInstruction;
      }
    }
  }
  cout << "part 2: " << finalAcc <<endl;
}
