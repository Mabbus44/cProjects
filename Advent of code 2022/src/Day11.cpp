#include "Day11.h"

namespace Day11ns{
  Day11::Day11()
  {
    //ctor
  }

  Day11::~Day11()
  {
    //dtor
  }

  void Day11::part1(string filename){
    InputLoader loader(filename);
    vector<vector<string>> input = loader.toVectorStr2d({"Monkey ",
                         "  Starting items: ",
                         "  Operation: new = ",
                         "  Test: divisible by ",
                         "    If true: throw to monkey ",
                         "    If false: throw to monkey ",
                         ", ",
                         ":",
                         " "});
    list<Monkey*> monkeys;

    for(int i=0; i<8; i++){
      vector<vector<string>> oneInput(6);
      copy(input.begin() + i*7, input.begin() + i*7 + 6, oneInput.begin());
      monkeys.push_back(new Monkey(oneInput));
    }

    for(Monkey* m: monkeys){
      m->output();
      cout << endl;
    }
    cout << "part 1: " << endl;
  }

  void Day11::part2(string filename){
    cout << "part 2: " << endl;
  }

  void Monkey::output(){
    cout << "Monkey " << id << ":" << endl;
    cout << "  Starting items: ";
    for(int i: items)
      cout << i << ", ";
    cout << endl;
    cout << "  Operation: new = " << operandA << " ";
    switch(operation){
      case ADD:
        cout << "+";
        break;
      case SUBSTRACT:
        cout << "-";
        break;
      case MULTIPLY:
        cout << "*";
        break;
      case DIVIDE:
        cout << "/";
        break;
    }
    cout << " " << operandB << endl;
    cout << "  Test: divisible by " << test << endl;
    cout << "    If true: throw to monkey " << throwToIfTrue << endl;
    cout << "    If false: throw to monkey " << throwToIfFalse << endl;
  }

  void Monkey::load(vector<vector<string>> input){
    id = InputLoader::toInt(input[0])[0];
    vector<int> itemsInt = InputLoader::toInt(input[1]);
    items.clear();
    for(int i:itemsInt)
      items.push_back(i);
    operandA = input[2][0];
    if(input[2][1].compare("+") == 0)
      operation = ADD;
    else if(input[2][1].compare("-") == 0)
      operation = SUBSTRACT;
    else if(input[2][1].compare("*") == 0)
      operation = MULTIPLY;
    else if(input[2][1].compare("/") == 0)
      operation = DIVIDE;
    else
      cout << "ERROR " << input[2][1] << " is not a operation" << endl;
    operandB = input[2][2];
    test = InputLoader::toInt(input[3])[0];
    throwToIfTrue = InputLoader::toInt(input[4])[0];
    throwToIfFalse = InputLoader::toInt(input[5])[0];
  }

  void Monkey::inspect(){
    for(list<__int64>::iterator it=items.begin(); it != items.end(); it++){
      int operandAVal, operandBVal;
      if(operandA.compare("old") == 0)
        operandAVal = (*it);
      else
        operandAVal = InputLoader::toInt({operandA})[0];
      if(operandB.compare("old") == 0)
        operandBVal = (*it);
      else
        operandBVal = InputLoader::toInt({operandB})[0];
      switch(operation){
        case ADD:
          (*it) = operandAVal + operandBVal;
          break;
        case SUBSTRACT:
          (*it) = operandAVal - operandBVal;
          break;
        case MULTIPLY:
          (*it) = operandAVal * operandBVal;
          break;
        case DIVIDE:
          (*it) = operandAVal / operandBVal;
          break;
      }
    }
  }
  void Monkey::throwItems(list<Monkey*>& monkeys){
  }
}
