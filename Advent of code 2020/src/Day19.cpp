#include "Day19.h"
#include <map>

namespace Day19{

  int Rule::load(vector<string> input){
    conditionA.clear();
    conditionB.clear();
    index = stoi(input[0]);
    bool useB = false;
    for(int i=1; i<(int)input.size(); i++){
      if(input[i].compare("|") == 0)
        useB = true;
      else if(input[i].compare("a") == 0 || input[i].compare("b") == 0){
        conditionC = input[i][0];
      }
      else{
        if(useB)
          conditionB.push_back(stoi(input[i]));
        else
          conditionA.push_back(stoi(input[i]));
      }
    }
    return index;
  }

  string Rule::followsRule(string message, bool& follows, map<int, Rule>& rules){
    if(conditionA.size() == 0 && conditionB.size() == 0){
      if(message.size() > 0 && message[0] == conditionC){
        follows = true;
        return message.substr(1,message.size()-1);
      }
      follows = false;
      return message;
    }
    string localMessage = message;
    for(int ruleIndex: conditionA){
      localMessage = rules[ruleIndex].followsRule(localMessage, follows, rules);
      if(!follows)
        break;
    }
    if(follows)
      return localMessage;
    if(conditionB.size() == 0)  //ConditionA failed and there is no conditionB
      return message;
    localMessage = message;
    for(int ruleIndex: conditionB){
      localMessage = rules[ruleIndex].followsRule(localMessage, follows, rules);
      if(!follows){
        break;
      }
    }
    if(follows)
      return localMessage;
    return message;
  }

  vector<string> Rule::followsRule2(vector<string> message, map<int, Rule>& rules){
    vector<string> ret;
    if(message.size() == 0)
      return ret;
    if(conditionA.size() == 0 && conditionB.size() == 0){
      for(string m: message)
        if(m.size() > 0 && m[0] == conditionC)
          ret.push_back(m.substr(1,m.size()-1));
      return ret;
    }
    ret = message;
    for(int ruleIndex: conditionA){
      ret = rules[ruleIndex].followsRule2(ret, rules);
      if(ret.size() == 0)
        break;
    }
    if(conditionB.size() == 0)
      return ret;
    vector<string> ret2 = message;
    for(int ruleIndex: conditionB){
      ret2 = rules[ruleIndex].followsRule2(ret2, rules);
      if(ret2.size() == 0)
        break;
    }
    ret.insert(ret.end(), ret2.begin(), ret2.end());
    return ret;
  }

  void Rule::output(){
    cout << index << ": ";
    if(conditionA.size() > 0){
      for(int i=0; i<(int)conditionA.size(); i++)
        cout << conditionA[i] << " ";
    }
    if(conditionB.size() > 0){
      cout << "| ";
      for(int i=0; i<(int)conditionB.size(); i++)
        cout << conditionB[i] << " ";
    }
    cout << endl;
  }


  Day19::Day19()
  {
    //ctor
  }

  Day19::~Day19()
  {
    //dtor
  }

  void Day19::part1(string filename){
    InputLoader loader(filename);
    vector<vector<string>> vvs = loader.toVectorStr2d({": ", " ", "\""});
    vector<string> inputs;
    map<int, Rule> rules;
    bool loadRules = true;
    for(vector<string> line: vvs){
      if(!loadRules){
        inputs.push_back(line[0]);
      }
      if(line.size() == 0){
        loadRules = false;
      }
      if(loadRules){
        Rule rule;
        int index=rule.load(line);
        rules[index] = rule;
      }
    }
    int followCount=0;
    for(string message: inputs){
      bool follows = true;
      string localMessage = rules[0].followsRule(message, follows, rules);
      if(follows && localMessage.size() == 0){
        //cout << "Match: " << message << endl;
        followCount++;
      }
    }
    cout << "part 1: " << followCount << endl;
  }

  void Day19::part2(string filename){
    InputLoader loader(filename);
    vector<vector<string>> vvs = loader.toVectorStr2d({": ", " ", "\""});
    vector<string> inputs;
    map<int, Rule> rules;
    bool loadRules = true;
    for(vector<string> line: vvs){
      if(!loadRules){
        inputs.push_back(line[0]);
      }
      if(line.size() == 0){
        loadRules = false;
      }
      if(loadRules){
        Rule rule;
        int index=rule.load(line);
        rules[index] = rule;
      }
    }
    Rule r8, r11;
    r8.load({"8", "42", "|", "42", "8"});
    r11.load({"11", "42", "31", "|", "42", "11", "31"});
    rules[8] = r8;
    rules[11] = r11;
    int followCount=0;
    for(string message: inputs){
      vector<string> result = rules[0].followsRule2({message}, rules);
      bool matches = false;
      for(string s: result){
        if(s.size()==0)
          matches=true;
      }
      if(matches){
        followCount++;
        //cout << "Match: " << message << endl;
      }
    }
    cout << "part 2: " << followCount << endl;  }
}
