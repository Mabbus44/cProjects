#include "Day24.h"

void Variable::output(){
  if(type==REFERENCE)
    cout << *varRef;
  else
    cout << val;
}

int64_t Variable::getVal(){
  if(type==REFERENCE)
    return *varRef;
  else
    return val;
}

void Instruction::output(){
  switch(type){
  case INP:
    cout << "INP ";
    break;
  case ADD:
    cout << "ADD ";
    break;
  case MUL:
    cout << "MUL ";
    break;
  case DIV:
    cout << "DIV ";
    break;
  case MOD:
    cout << "MOD ";
    break;
  case EQL:
    cout << "EQL ";
    break;
  default:
    cout << "INVALID OPERATION ";
    break;
  }
  varA.output();
  if(type!=INP){
    cout << " ";
    varB.output();
  }
  cout << endl;
}

void Instruction::execute(vector<int64_t>& inputs, bool debug){
  switch(type){
  case INP:
    if((int)inputs.size()==0)
      cout << "Error, trying to load nonexistent number" << endl;
    *(varA.varRef) = inputs.back();
    inputs.pop_back();
    if(debug)
      cout << "INP " << *(varA.varRef) << endl;
    break;
  case ADD:
    if(debug)
      cout << "ADD " << varA.getVal() << " + " << varB.getVal() << " = ";
    *(varA.varRef) = varA.getVal() + varB.getVal();
    if(debug)
      cout << *(varA.varRef) << endl;
    break;
  case MUL:
    if(debug)
      cout << "MUL " << varA.getVal() << " * " << varB.getVal() << " = ";
    *(varA.varRef) = varA.getVal() * varB.getVal();
    if(debug)
      cout << *(varA.varRef) << endl;
    break;
  case DIV:
    if(debug)
      cout << "DIV " << varA.getVal() << " / " << varB.getVal() << " = ";
    if(varB.getVal() == 0)
      cout << "Error, divide by zero" << endl;
    *(varA.varRef) = varA.getVal() / varB.getVal();
    if(debug)
      cout << *(varA.varRef) << endl;
    break;
  case MOD:
    if(debug)
      cout << "MOD " << varA.getVal() << " % " << varB.getVal() << " = ";
    *(varA.varRef) = varA.getVal() % varB.getVal();
    if(debug)
      cout << *(varA.varRef) << endl;
    break;
  case EQL:
    if(debug)
      cout << "EQL " << varA.getVal() << " == " << varB.getVal() << " = ";
    *(varA.varRef) = (varA.getVal() == varB.getVal());
    if(debug)
      cout << *(varA.varRef) << endl;
    break;
  }
}

/*void ALU::zx26(){
  if(z>0)
    z26power++;
}

void ALU::zdiv26(){
  if(z26power>0)
    z26power--;
  else
    z=0;
}*/

int ALU::execute(bool debug){
  for(int i=0; i<14; i++){
    if(debug)
      cout << i << ": ";
    if(zMax[i]<z){
      if(debug)
        cout << endl;
      return i;
    }
    if(z%26+k1[i] != inputNum[i]){
      if(d[i]){
        z = z/26;
        if(debug)
          cout << "z=z/26 ";
      }
      z=z*26+inputNum[i]+k2[i];
      if(debug)
        cout << "z=z*26+inputNum[i]+k2[i] ";
    }
    else if(d[i]){
      z = z/26;
      if(debug)
        cout << "z=z/26 ";
    }
    if(debug)
      cout << endl;
    if(debug)
      cout << i << ": " << inputNum[i] << " " << k1[i] << " " << k2[i] << " " << z << endl;
  }
  return 14;
}

void ALU::output(){
  for(Instruction* i:instructions){
    i->output();
  }
}

void ALU::loadInstruction(InputLoader& loader, string line){
  vector<string> input = loader.splitString(line, {" "});
  if((int)input.size()<2)
    return;
  int type;
  Variable varA, varB;
  if(input[0].compare("inp")==0)
    type=INP;
  else if(input[0].compare("add")==0)
    type=ADD;
  else if(input[0].compare("mul")==0)
    type=MUL;
  else if(input[0].compare("div")==0)
    type=DIV;
  else if(input[0].compare("mod")==0)
    type=MOD;
  else if(input[0].compare("eql")==0)
    type=EQL;
  else
    cout << "cannot load line: " << line << endl;
  if(input[1].compare("x")==0)
    varA = Variable(REFERENCE, 0, &x);
  else if(input[1].compare("y")==0)
    varA = Variable(REFERENCE, 0, &y);
  else if(input[1].compare("z")==0)
    varA = Variable(REFERENCE, 0, &z);
  else if(input[1].compare("w")==0)
    varA = Variable(REFERENCE, 0, &w);
  if(input[0].compare("inp")==0)
  {}
  else if(input[2].compare("x")==0)
    varB = Variable(REFERENCE, 0, &x);
  else if(input[2].compare("y")==0)
    varB = Variable(REFERENCE, 0, &y);
  else if(input[2].compare("z")==0)
    varB = Variable(REFERENCE, 0, &z);
  else if(input[2].compare("w")==0)
    varB = Variable(REFERENCE, 0, &w);
  else
    varB = Variable(NUMBER, stoi(input[2]), NULL);
  instructions.push_back(new Instruction(type, varA, varB));
}


Day24::Day24()
{
  //ctor
}

Day24::~Day24()
{
  //dtor
}

void Day24::part1(string filename){
  InputLoader loader(filename);
  vector<string> vs = loader.toVectorStr();
  ALU alu, alu2;
  for(string s:vs){
    alu2.loadInstruction(loader, s);
  }
  alu.z =1;
  alu2.z =1;
  int failedDigit=14;
  int oldThirdDigit=0;
  while(alu.z != 0){
    alu.x =0;
    alu.y =0;
    alu.z =0;
    alu.w =0;
    alu2.x =0;
    alu2.y =0;
    alu2.z =0;
    alu2.w =0;
    //cout << "start" << endl;
    for(int i=failedDigit; i<14; i++)
      alu.inputNum[i] = 9;
    int digitId=failedDigit-1;
    bool done=false;
    while(!done){
      alu.inputNum[digitId]--;
      if(alu.inputNum[digitId]==0)
        alu.inputNum[digitId]=9;
      if(alu.inputNum[digitId]==9 && digitId>0){
        digitId--;
      }else{
        done = true;
      }
    }
    /*done=false;
    digitId = 13;
    while(!done){
      alu2.inputNum[digitId]--;
      if(alu2.inputNum[digitId]==0)
        alu2.inputNum[digitId]=9;
      if(alu2.inputNum[digitId]==9 && digitId>0){
        digitId--;
      }else{
        done = true;
      }
    }*/
    failedDigit = alu.execute();
    if(false && oldThirdDigit != alu.inputNum[2]){
      for(int i=0; i<14; i++)
        cout << alu.inputNum[i];
      cout << " " << alu.z << endl;
      oldThirdDigit = alu.inputNum[2];
    }
    /*alu2.inputs.clear();
    for(int i=13; i>=0; i--)
      alu2.inputs.push_back(alu2.inputNum[i]);
    cout << endl;
    int tCount=-2;
    int lastInput = -1;
    for(Instruction* i:alu2.instructions){
      if(i->type == INP){
        tCount++;
        if(lastInput != -1){
          cout << "ALU2: " << tCount << ": " << lastInput << " " << alu2.z << endl<< endl;
        }
        lastInput = alu2.inputs.back();
      }
      i->execute(alu2.inputs, true);
    }
    cout << "ALU2: 13: " << lastInput << " " << alu2.z << endl<< endl;*/
    //alu.z = 0;
  }
  cout << "Part 1: ";
  for(int i=0; i<14; i++)
    cout << alu.inputNum[i];
  cout << endl;
}

void Day24::part2(string filename){
  InputLoader loader(filename);
  vector<string> vs = loader.toVectorStr();
  ALU alu, alu2;
  for(string s:vs){
    alu2.loadInstruction(loader, s);
  }
  alu.z =1;
  alu2.z =1;
  int failedDigit=14;
  bool done=true;
  int oldThirdDigit=0;
  while(alu.z != 0){
    alu.x =0;
    alu.y =0;
    alu.z =0;
    alu.w =0;
    alu2.x =0;
    alu2.y =0;
    alu2.z =0;
    alu2.w =0;
    //cout << "start" << endl;
    for(int i=failedDigit; i<14; i++)
      alu.inputNum[i] = 1;
    int digitId=failedDigit-1;
    while(!done){
      alu.inputNum[digitId]++;
      if(alu.inputNum[digitId]==10)
        alu.inputNum[digitId]=1;
      if(alu.inputNum[digitId]==1 && digitId>0){
        digitId--;
      }else{
        done = true;
      }
    }
    done=false;
    /*done=false;
    digitId = 13;
    while(!done){
      alu2.inputNum[digitId]--;
      if(alu2.inputNum[digitId]==0)
        alu2.inputNum[digitId]=9;
      if(alu2.inputNum[digitId]==9 && digitId>0){
        digitId--;
      }else{
        done = true;
      }
    }*/
    failedDigit = alu.execute();
    if(false && oldThirdDigit != alu.inputNum[2]){
      for(int i=0; i<14; i++)
        cout << alu.inputNum[i];
      cout << " " << alu.z << endl;
      oldThirdDigit = alu.inputNum[2];
    }
    /*alu2.inputs.clear();
    for(int i=13; i>=0; i--)
      alu2.inputs.push_back(alu2.inputNum[i]);
    cout << endl;
    int tCount=-2;
    int lastInput = -1;
    for(Instruction* i:alu2.instructions){
      if(i->type == INP){
        tCount++;
        if(lastInput != -1){
          cout << "ALU2: " << tCount << ": " << lastInput << " " << alu2.z << endl<< endl;
        }
        lastInput = alu2.inputs.back();
      }
      i->execute(alu2.inputs, true);
    }
    cout << "ALU2: 13: " << lastInput << " " << alu2.z << endl<< endl;*/
    //alu.z = 0;
  }
  cout << "Part 2: ";
  for(int i=0; i<14; i++)
    cout << alu.inputNum[i];
  cout << endl;}
