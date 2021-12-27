#include "Day07.h"

void Bag::output(){
  cout << name << endl;
  for(int i=0; i<(int)containName.size(); i++)
    cout << "  contains " << containCount[i] << " " << containName[i] << endl;
}

void Bag::load(vector<string>& input){
  name = input[0];
  for(int i=1; i<(int)input.size(); i++){
    if(input[i][1] == ' '){
      containCount.push_back(input[i][0]-'0');
      containName.push_back(input[i].substr(2,input[i].size()-2));
    }
  }
}

bool Bag::contains(string name){
  for(string s:containName){
    if(s.compare(name)==0)
      return true;
  }
  for(Bag* b:containBag){
    if(b->contains(name))
      return true;
  }
  return false;
}

int Bag::countBags(){
  int sum=1;
  for(int i=0; i<(int)containBag.size(); i++){
    sum += containBag[i]->countBags()*containCount[i];

  }
  return sum;
}

Day07::Day07()
{
  //ctor
}

Day07::~Day07()
{
  //dtor
}

void Day07::part1(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({" bags contain ", " bag, ", " bags, ", " bag.", " bags."});
  vector<Bag*> bags;
  for(vector<string> vs:vvs){
    bags.push_back(new Bag(vs));
  }
  for(Bag* b: bags){
    for(string name:b->containName){
      for(Bag* b2: bags){
        if(name.compare(b2->name)==0){
          b->containBag.push_back(b2);
        }
      }
    }
  }
  int sum=0;
  for(Bag* b: bags){
    if(b->contains("shiny gold"))
      sum++;
  }
  for(Bag* b: bags)
    delete b;

  cout << "part 1: " << sum << endl;
}

void Day07::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({" bags contain ", " bag, ", " bags, ", " bag.", " bags."});
  vector<Bag*> bags;
  for(vector<string> vs:vvs){
    bags.push_back(new Bag(vs));
  }
  for(Bag* b: bags){
    for(string name:b->containName){
      for(Bag* b2: bags){
        if(name.compare(b2->name)==0){
          b->containBag.push_back(b2);
        }
      }
    }
  }
  int sum=0;
  for(Bag* b: bags){
    if(b->name.compare("shiny gold")==0){
      sum = b->countBags()-1;
    }
  }
  for(Bag* b: bags)
    delete b;
  cout << "part 2: " << sum << endl;
}
