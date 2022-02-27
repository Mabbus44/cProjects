#include "number.h"
#include "variable.h"
using namespace std;

Variable::Variable(){
  type = "";
  name = "";
  next = NULL;
  prev = NULL;
}

Variable::Variable(string name, string type){
  this->type = type;
  this->name = name;
  next = NULL;
  prev = NULL;
}

bool Variable::add(string name, string type){
  Variable* next = this->next;
  this->next = new Variable(name, type);
  if(!this->next->content){
    delete this->next;
    this->next=next;
    return false;
  }
  this->next->next = next;
  this->next->prev = this;
  return true;
}

bool Variable::insert(string name, string type){
  Variable* prev = this->prev;
  this->prev = new Variable(name, type);
  if(!this->prev->content){
    delete this->prev;
    this->prev=prev;
    return false;
  }
  this->prev->prev = prev;
  this->prev->next = this;
  return true;
}

bool Variable::set(string type){
  if(!checkType(type))
    return false;
  if(content)
    delete[] content;
  this->type = type;
  if(type.compare("number")==0){
    content = new Number();
  }else{
    return false;
  }
  return true;
}

bool Variable::rename(string name){
  if(checkName(name)){
    this->name = name;
    return true;
  }
  return false;
}

bool Variable::checkName(string name){
  Variable* checked = this;
  while(checked->next){
    if(name == this->next->getName())
      return false;
    checked = checked->next;
  }
  checked = this;
  while(checked->prev){
    if(name == this->prev->getName())
      return false;
    checked = checked->prev;
  }
  return true;
}

bool Variable::checkType(string type){
  if(type == "number"){
    return true;
  }else{
    return false;
  }
}

string Variable::getType(){
  return type;
}

string Variable::getName(){
  return name;
}
