#include "Neurons/Neuron.h"
#include <iostream>

using namespace std;

Neuron::Neuron()
{
  _family = -1;
  _type = -1;
  reRollProperties();
}

Neuron::~Neuron()
{
  //dtor
}

bool Neuron::connectParent(Neuron* newParent){
  if(freeParentConnection())
    _parents.push_back(newParent);
  else
    return false;
  return true;
}

bool Neuron::connectChild(Neuron* newChild){
  if(freeChildConnection())
    _children.push_back(newChild);
  else
    return false;
  return true;
}

bool Neuron::freeParentConnection(){
  return true;
}

bool Neuron::freeChildConnection(){
  return true;
}

bool Neuron::myOffspring(Neuron* n){
  for(Neuron* c : _children)
    if(n==c || c->myOffspring(n))
      return true;
  return false;
}

void Neuron::setLevel(int level){
  if(_level < level)
    _level = level;
  for(Neuron* c : _children)
    c->setLevel(_level+1);
}

void Neuron::setColumn(vector<int>& columns){
  int levels = columns.size();
  if(levels < _level)
    for(int i=0; i<_level-levels; i++)
      columns.push_back(0);
  columns[_level-1] = columns[_level-1] + 1;
  _column = columns[_level-1];
  for(Neuron* n : _children)
    if(n->getColumn() == 0)
      n->setColumn(columns);
}

void Neuron::disconnect2way(){
  while(_parents.size()>0){
    _parents[0]->disconnectChild(this);
    _parents.erase(_parents.begin());
  }
  while(_children.size()>0){
    _children[0]->disconnectParent(this);
    _children.erase(_children.begin());
  }
}

void Neuron::disconnectParent(Neuron* parent){
  for(int i=0; i<(int)_parents.size(); i++){
    if(_parents[i]==parent){
      _parents.erase(_parents.begin()+i);
      return;
    }
  }
}

void Neuron::disconnectChild(Neuron* child){
  for(int i=0; i<(int)_children.size(); i++){
    if(_children[i]==child){
      _children.erase(_children.begin()+i);
      return;
    }
  }
}

void Neuron::disconnectRandomParent2way(){
  int parentId = rand()%_parents.size();
  _parents[parentId]->disconnectChild(this);
  _parents.erase(_parents.begin()+parentId);
}

void Neuron::disconnectRandomChild2way(){
  int childId = rand()%_children.size();
  _children[childId]->disconnectParent(this);
  _children.erase(_children.begin()+childId);
}

void Neuron::replaceParent(Neuron* oldParent, Neuron* newParent){
  for(int i=0; i<(int)_parents.size(); i++){
    if(_parents[i] == oldParent){
      _parents[i] = newParent;
      return;
    }
  }
}

void Neuron::replaceChild(Neuron* oldChild, Neuron* newChild){
  for(int i=0; i<(int)_children.size(); i++){
    if(_children[i] == oldChild){
      _children[i] = newChild;
      return;
    }
  }
}

void Neuron::replaceNeuron(Neuron* oldNeuron){
  vector<Neuron*> oldParents = oldNeuron->parents();
  vector<Neuron*> oldChildren = oldNeuron->children();
  for(Neuron* parent : oldParents){
    if(freeParentConnection()){
      parent->replaceChild(oldNeuron, this);
      _parents.push_back(parent);
    }
    else
      parent->disconnectChild(oldNeuron);
  }
  for(Neuron* child : oldChildren){
    if(freeChildConnection()){
      child->replaceParent(oldNeuron, this);
      _children.push_back(child);
    }
    else
      child->disconnectParent(oldNeuron);
  }
}

void Neuron::output(string tab, int level){
  switch(level){
    case OUTPUT_ONELINE:
      cout << tab << "Address: " << this << " Level: " << _level << " Column: " << _column << " Index: " << index << " Type: " << _type << " Family: " << _family << " ComputeDone: " << _computeDone << " ComputeResult: " << _computeResult << " Parent: " << _parent << " Parents: " << _parents.size() << " Children: " << _children.size();
      break;
    case OUTPUT_OVERVIEW:
    case OUTPUT_DEEP:
    case OUTPUT_ALL:
      cout << tab << "Address: " << this << endl;
      cout << tab << "Level: " << _level <<  endl;
      cout << tab << "Column: " << _column << endl;
      cout << tab << "Index: " << index << endl;
      cout << tab << "Type: " << _type << endl;
      cout << tab << "Family: " << _family << endl;
      cout << tab << "ComputeDone: " << _computeDone << endl;
      cout << tab << "ComputeResult: " << _computeResult << endl;
      cout << tab << "Parent: " << _parent << endl;
      cout << tab << "Parents: " << _parents.size() << endl;
      for(Neuron* p: _parents){
        p->output(tab+"  ", OUTPUT_ONELINE);
        cout << endl;
      }
      cout << tab << "Children: " << _children.size() << endl;
      for(Neuron* c: _children){
        c->output(tab+"  ", OUTPUT_ONELINE);
        cout << endl;
      }
      break;
  }
}

bool Neuron::inList(vector<Neuron*>& neuronList){
  for(Neuron* n: neuronList)
    if(n==this)
      return true;
  return false;
}

Neuron* Neuron::addToCopy(Neuron* n){
  n->_factor = _factor;
  n->_bonus = _bonus;
  n->index = index;
  n->_factor = _factor;
  n->_bonus = _bonus;
  return n;
}

double Neuron::_postCompute(){
  _computeResult = _computeResult*_factor+_bonus;
  if(_computeResult>1.0)
    _computeResult = 1.0;
  if(_computeResult<-1.0)
    _computeResult = -1.0;
  return _computeResult;
}

void Neuron::reRollProperties(){
  _factor = (rand()%2001-1000)/1000.0;
  _bonus = (rand()%2001-1000)/1000.0;
}

void Neuron::draw(SDLWindow* window){
  switch(_family){
    case LOGIC_NEURON:
      window->setDrawColor(0xFF, 0xFF, 0xFF);
      break;
    case SENSOR_NEURON:
      window->setDrawColor(0xFF, 0xFF, 0x00);
      break;
    case OUTPUT_NEURON:
      window->setDrawColor(0x00, 0x00, 0x00);
      break;
  }
  window->drawRect(_column*80-20, _level*40, 70, 30);
  for(Neuron* c : _children)
    window->drawLine(_column*80+15, _level*40+30, c->_column*80+15, c->_level*40);
  string t;
  switch(_type){
    case SN_GRASS_DIST_N:
      t="SGN";
      break;
    case SN_GRASS_DIST_S:
      t="SGS";
      break;
    case SN_GRASS_DIST_E:
      t="SGE";
      break;
    case SN_GRASS_DIST_W:
      t="SGW";
      break;
    case SN_HERBIVORE_DIST_N:
      t="SHN";
      break;
    case SN_HERBIVORE_DIST_S:
      t="SHS";
      break;
    case SN_HERBIVORE_DIST_E:
      t="SHE";
      break;
    case SN_HERBIVORE_DIST_W:
      t="SHW";
      break;
    case SN_CARNIVORE_DIST_N:
      t="SCN";
      break;
    case SN_CARNIVORE_DIST_S:
      t="SCS";
      break;
    case SN_CARNIVORE_DIST_E:
      t="SCE";
      break;
    case SN_CARNIVORE_DIST_W:
      t="SCW";
      break;
    case LN_OR:
      t="OR";
      break;
    case LN_AND:
      t="AND";
      break;
    case LN_GREATER_THAN:
      t=">";
      break;
    case LN_ADD:
      t="+";
      break;
    case ON_MOVE_N:
      t="MN";
      break;
    case ON_MOVE_S:
      t="MS";
      break;
    case ON_MOVE_E:
      t="ME";
      break;
    case ON_MOVE_W:
      t="MW";
      break;
    case ON_EAT:
      t="E";
      break;
  }
  window->drawText(_column*80, _level*40, t);
}
