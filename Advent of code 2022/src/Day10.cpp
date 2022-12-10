#include "Day10.h"

Day10::Day10()
{
  //ctor
}

Day10::~Day10()
{
  //dtor
}

void Day10::part1(string filename){
  CPU cpu;
  cpu.load(filename);
  cpu.start();
  int sum = 0;
  while(cpu.runCpuCycle()){
    if(cpu.cpuCycle == 19 ||
       cpu.cpuCycle == 59 ||
       cpu.cpuCycle == 99 ||
       cpu.cpuCycle == 139 ||
       cpu.cpuCycle == 179 ||
       cpu.cpuCycle == 219)
      sum += (cpu.registerX*(cpu.cpuCycle+1));
  }
  cout << "part 1: " << sum << endl;
}

void Day10::part2(string filename){
  CPU cpu;
  cpu.load(filename);
  cpu.start();
  char image[240];
  int crtPosition = 0;
  int crtRow = 0;
  do{
    if(abs(crtPosition-cpu.registerX)<2)
      image[crtRow*40+crtPosition] = '#';
    else
      image[crtRow*40+crtPosition] = '.';
    crtPosition++;
    if(crtPosition == 40){
      crtPosition -= 40;
      crtRow++;
    }
  }while(cpu.runCpuCycle());
  cout << "part 2: " << endl;
  for(int row=0; row<6; row++){
    for(int col=0; col<40; col++){
      cout << image[row*40+col];
    }
    cout << endl;
  }
}

void Command::load(vector<string> cmdParts){
  if(cmdParts[0].compare("noop") == 0)
    instruction = NOOP;
  if(cmdParts[0].compare("addx") == 0){
    instruction = ADDX;
    intArg0 = InputLoader::toInt({cmdParts[1]})[0];
  }
}

void CPU::load(string fileName){
  InputLoader loader(fileName);
  vector<vector<string>> input = loader.toVectorStr2d({" "});
  for(vector<string> cmdParts: input){
    commands.push_back(Command(cmdParts));
  }
}

bool CPU::runCpuCycle(){
  if(currentCommand == commands.end())
    return false;
  cpuCycle++;
  cpuCycleOnCurrentCommand++;
  switch((*currentCommand).instruction){
    case NOOP:
      cpuCycleOnCurrentCommand = 0;
      currentCommand++;
      break;
    case ADDX:
      if(cpuCycleOnCurrentCommand == 2){
        registerX += (*currentCommand).intArg0;
        cpuCycleOnCurrentCommand = 0;
        currentCommand++;
      }
      break;
  }
  return true;
}
