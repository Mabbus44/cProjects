#include "Day16.h"

void Rule::load(vector<string> input){
  InputLoader loader;
  name = input[0];
  for(int i=1; i<(int)input.size(); i++){
    vector<int> vi=loader.toInt(loader.splitString({input[i]}, {"-"}));
    ranges.push_back(Range(vi[0], vi[1]));
  }
  for(int i=0; i<20; i++)
    index.push_back(i);
}

bool Rule::inRange(int val){
  for(Range& r:ranges){
    if(val>=r.rangeMin && val<=r.rangeMax)
      return true;
  }
  return false;
}

void Rule::output(){
  cout << name << ": ";
  for(int i: index)
    cout << i << ",";
  cout << endl;
  for(Range& range: ranges){
    cout << range.rangeMin << "-" << range.rangeMax << endl;
  }
}

Day16::Day16()
{
  //ctor
}

Day16::~Day16()
{
  //dtor
}

void Day16::part1(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({": ", " or ", ","});
  vector<Rule> rules;
  vector<int> yourTicket;
  vector<vector<int>> otherTickets;
  int i=0;
  while(vvs[i].size() > 0){
    rules.push_back(Rule(vvs[i]));
    i++;
  }
  i+=2;
  yourTicket = loader.toInt(vvs[i]);
  i+=3;
  while(i<(int)vvs.size()){
    otherTickets.push_back(loader.toInt(vvs[i]));
    i++;
  }
  int sumOfInvalidFields=0;
  for(vector<int> ticket:otherTickets){
    for(int field:ticket){
      bool valid=false;
      for(Rule& rule:rules){
        if(rule.inRange(field))
          valid=true;
      }
      if(!valid)
        sumOfInvalidFields += field;
    }
  }
  cout << "part 1: " << sumOfInvalidFields << endl;
}

void Day16::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({": ", " or ", ","});
  vector<Rule> rules;
  vector<int> yourTicket;
  vector<vector<int>> otherTickets;
  int i=0;
  while(vvs[i].size() > 0){
    rules.push_back(Rule(vvs[i]));
    i++;
  }
  i+=2;
  yourTicket = loader.toInt(vvs[i]);
  i+=3;
  while(i<(int)vvs.size()){
    otherTickets.push_back(loader.toInt(vvs[i]));
    i++;
  }
  vector<vector<int>>::iterator ticketIt = otherTickets.begin();
  while(ticketIt != otherTickets.end()){
    bool validTicket = true;
    for(int field:*ticketIt){
      bool valid=false;
      for(Rule& rule:rules){
        if(rule.inRange(field))
          valid=true;
      }
      if(!valid)
        validTicket = false;
    }
    if(!validTicket)
      ticketIt = otherTickets.erase(ticketIt);
    else
      ticketIt++;
  }
  int ticketCount=0;
  for(vector<int> ticket: otherTickets){
    ticketCount++;
    int ruleCount=0;
    for(Rule& rule: rules){
      ruleCount++;
      vector<int>::iterator index = rule.index.begin();
      while(index != rule.index.end()){
        if(!rule.inRange(ticket[*index]))
          index = rule.index.erase(index);
        else
          index++;
      }
    }
  }
  bool deleted = true;
  while(deleted){
    deleted = false;
    for(vector<Rule>::iterator ruleIt=rules.begin(); ruleIt!=rules.end(); ruleIt++){
      if((*ruleIt).index.size()==1){
        for(vector<Rule>::iterator ruleIt2=rules.begin(); ruleIt2!=rules.end(); ruleIt2++){
          if(!(ruleIt==ruleIt2)){
            vector<int>::iterator index = (*ruleIt2).index.begin();
            while(index != (*ruleIt2).index.end()){
              if(*index == (*ruleIt).index[0]){
                index = (*ruleIt2).index.erase(index);
                deleted = true;
              }
              else
                index++;
            }
          }
        }
      }
    }
  }
  __int64 ans=1;
  for(Rule& rule:rules)
    if(rule.name.find("departure") != string::npos)
      ans = ans * yourTicket[rule.index[0]];
  cout << "part 2: " << ans << endl;
}
