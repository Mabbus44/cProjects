#include "Enteties/Animal.h"
#include <stdlib.h>
#include <stdio.h>
#include "Includes.h"
#include "Map.h"

Animal::Animal()
{
}

Animal::~Animal()
{
  //dtor
}

void Animal::generateNeurons(){
  for(int i=0; i<NEURONS_PER_ANIMAL; i++){
    createRandomNeuron();
  }
}

void Animal::createRandomNeuron(bool connectChildren, bool connectParents, int copyNeuronId){
  int nodeType = rand()%NODE_TYPE_COUNT;
  Neuron* neuron;
  switch(nodeType){
    case SN_GRASS_DIST_N:
    case SN_GRASS_DIST_S:
    case SN_GRASS_DIST_E:
    case SN_GRASS_DIST_W:
      neuron = new SNGrassDist(this, nodeType);
      break;
    case SN_HERBIVORE_DIST_N:
    case SN_HERBIVORE_DIST_S:
    case SN_HERBIVORE_DIST_E:
    case SN_HERBIVORE_DIST_W:
      neuron = new SNHerbivoreDist(this, nodeType);
      break;
    case SN_CARNIVORE_DIST_N:
    case SN_CARNIVORE_DIST_S:
    case SN_CARNIVORE_DIST_E:
    case SN_CARNIVORE_DIST_W:
      neuron = new SNCarnivoreDist(this, nodeType);
      break;
    case LN_OR:
      neuron = new LNOr(this);
      break;
    case LN_AND:
      neuron = new LNAnd(this);
      break;
    case LN_GREATER_THAN:
      neuron = new LNGreaterThan(this);
      break;
    case LN_ADD:
      neuron = new LNAdd(this);
      break;
    case ON_MOVE_N:
    case ON_MOVE_S:
    case ON_MOVE_E:
    case ON_MOVE_W:
      neuron = new ONMove(this, nodeType);
      break;
    case ON_EAT:
      neuron = new ONEat(this);
      break;
  }
  _neurons.push_back(neuron);
  if(connectChildren)
    connectNeuronToChildren(neuron);
  if(connectParents)
    connectNeuronToParents(neuron);
  if(copyNeuronId>-1){
    neuron->replaceNeuron(_neurons[copyNeuronId]);
    delete _neurons[copyNeuronId];
    _neurons.erase(_neurons.begin()+copyNeuronId);
  }
}

void Animal::connectNeuronToChildren(Neuron* n){
  vector<Neuron*> availableNeurons = _neurons;
  int childCount = rand()%(CHILDREN_PER_NEURON_MAX-CHILDREN_PER_NEURON_MIN+1)+CHILDREN_PER_NEURON_MIN;
  while(childCount>0 && n->freeChildConnection() && availableNeurons.size()>0){
    int candidate = rand()%availableNeurons.size();
    if(n == availableNeurons[candidate] || availableNeurons[candidate]->myOffspring(n) || !availableNeurons[candidate]->connectParent(n))
      availableNeurons.erase(availableNeurons.begin()+candidate);
    else{
      n->connectChild(availableNeurons[candidate]);
      childCount--;
    }
  }
}

void Animal::connectNeuronToParents(Neuron* n){
  vector<Neuron*> availableNeurons = _neurons;
  int parentCount = rand()%(CHILDREN_PER_NEURON_MAX-CHILDREN_PER_NEURON_MIN+1)+CHILDREN_PER_NEURON_MIN;
  while(parentCount>0 && n->freeParentConnection() && availableNeurons.size()>0){
    int candidate = rand()%availableNeurons.size();
    if(n == availableNeurons[candidate] || n->myOffspring(availableNeurons[candidate]) || !availableNeurons[candidate]->connectChild(n))
      availableNeurons.erase(availableNeurons.begin()+candidate);
    else{
      n->connectParent(availableNeurons[candidate]);
      parentCount--;
    }
  }
}

void Animal::rewireNeuron(int index){
  Neuron* n=_neurons[index];
  vector<Neuron*> availableNeurons = _neurons;
  int childCount = rand()%(REWIRE_NEURON_MAX_WIRES-REWIRE_NEURON_MIN_WIRES+1)+REWIRE_NEURON_MIN_WIRES;
  int parentCount = rand()%(REWIRE_NEURON_MAX_WIRES-REWIRE_NEURON_MIN_WIRES+1)+REWIRE_NEURON_MIN_WIRES;
  while(childCount>0 && availableNeurons.size()>0 && n->children().size()>0){
    int candidate = rand()%availableNeurons.size();
    if(n == availableNeurons[candidate] || availableNeurons[candidate]->myOffspring(n) || !availableNeurons[candidate]->freeParentConnection())
      availableNeurons.erase(availableNeurons.begin()+candidate);
    else{
      n->freeChildConnection();
      n->disconnectRandomChild2way();
      n->connectChild(availableNeurons[candidate]);
      availableNeurons[candidate]->connectParent(n);
      childCount--;
    }
  }
  availableNeurons = _neurons;
  while(parentCount>0 && availableNeurons.size()>0 && n->parents().size()>0){
    int candidate = rand()%availableNeurons.size();
    if(n == availableNeurons[candidate] || n->myOffspring(availableNeurons[candidate]) || !availableNeurons[candidate]->freeChildConnection())
      availableNeurons.erase(availableNeurons.begin()+candidate);
    else{
      n->disconnectRandomParent2way();
      n->connectParent(availableNeurons[candidate]);
      availableNeurons[candidate]->connectChild(n);
      parentCount--;
    }
  }
}

void Animal::free(){
  for(Neuron* n : _neurons)
    if(n)
      delete n;
  _neurons.clear();
}

void Animal::prepareDrawNeurons(){
  for(Neuron* n : _neurons)
    n->resetLevelColumn();
  for(Neuron* n : _neurons)
    if(n->parents().size() == 0)
      n->setLevel(1);
  vector<int> columns;
  for(Neuron* n : _neurons)
    if(n->parents().size() == 0)
      n->setColumn(columns);
}

void Animal::compute(){
  for(Neuron* n : _neurons)
    n->compute();
}

Neuron* Animal::getAction(){
  Neuron* ret = NULL;
  double bestNeuronOutput = 0.0;
  for(Neuron* n : _neurons){
    if(n->family() == OUTPUT_NEURON && n->compute() >= bestNeuronOutput){
      ret = n;
      bestNeuronOutput = n->compute();
    }
  }
  return ret;
}

void Animal::mutateNeurons(){
  int mutation;
  int mutationCount = rand()%(NEW_NEURON_MAX-NEW_NEURON_MIN)+NEW_NEURON_MIN;
  int neuronId;
  while(_neurons.size()>0 && mutationCount>0){
    mutation = rand()%NEURON_MUTATION_COUNT;
    neuronId = rand()%_neurons.size();
    switch(mutation){
      case NEW_NEURON:
        deleteNeuron(neuronId);
        createRandomNeuron(true, true);
        break;
      case REPLACE_NEURON:
        createRandomNeuron(false, false, neuronId);
        break;
      case REWIRE_NEURON:
        rewireNeuron(neuronId);
        break;
      case REROLL_PROPERTIES_NEURON:
        _neurons[neuronId]->reRollProperties();
        break;
    }
    mutationCount--;
  }
}

void Animal::deleteNeuron(int i){
  _neurons[i]->disconnect2way();
  delete _neurons[i];
  _neurons.erase(_neurons.begin()+i);
}

Animal* Animal::deepCopy(Map* parent, int x, int y, int bellyFood, int index){
  Animal* newAnimal;
  if(x==-1)
    x = _posX;
  if(y==-1)
    y = _posY;
  if(bellyFood==-1)
    bellyFood = _bellyFood;
  if(index==-1)
    index = _index;
  switch(_type){
    case CARNIVORE:
      newAnimal = new Carnivore(parent, x, y, index, bellyFood, false);
      break;
    case HERBIVORE:
      newAnimal = new Herbivore(parent, x, y, index, bellyFood, false);
      break;
  }
  for(int i=0; i<(int)_neurons.size(); i++){
    _neurons[i]->index=i;
    newAnimal->_neurons.push_back(_neurons[i]->deepCopy(newAnimal));
  }
  for(int i=0; i<(int)_neurons.size(); i++){
    vector<Neuron*> parents = _neurons[i]->parents();
    for(int i2=0; i2<(int)parents.size(); i2++){
      newAnimal->_neurons[i]->connectParent(newAnimal->_neurons[parents[i2]->index]);
    }
    vector<Neuron*> children = _neurons[i]->children();
    for(int i2=0; i2<(int)children.size(); i2++){
      newAnimal->_neurons[i]->connectChild(newAnimal->_neurons[children[i2]->index]);
    }
  }
  return newAnimal;
}

void Animal::output(string tab, int level){
  Entity::output(tab, level);
  switch(level){
    case OUTPUT_ONELINE:
      cout << " Neurons: " << _neurons.size() << " BellyFood: " << _bellyFood;
      break;
    case OUTPUT_OVERVIEW:
      cout << tab << "BellyFood: " << _bellyFood << endl;
      cout << tab << "Neurons: " << _neurons.size() << endl;

      for(int i=0; i<(int)_neurons.size(); i++){
        _neurons[i]->output(tab+to_string(i)+": ", OUTPUT_ONELINE); cout << endl;}
      break;
    case OUTPUT_DEEP:
      cout << tab << "BellyFood: " << _bellyFood << endl;
      cout << tab << "Neurons: " << _neurons.size() << endl;
      for(int i=0; i<(int)_neurons.size(); i++){
        _neurons[i]->output(tab+to_string(i)+": ", OUTPUT_OVERVIEW); cout << tab+"  " << "----------" << endl;}
      break;
    case OUTPUT_ALL:
      cout << tab << "BellyFood: " << _bellyFood << endl;
      cout << tab << "Neurons: " << _neurons.size() << endl;
      for(int i=0; i<(int)_neurons.size(); i++){
        _neurons[i]->output(tab+to_string(i)+": ", OUTPUT_ALL); cout << tab+"  " << "----------" << endl;}
      break;
  }
}

bool Animal::neuronSanityCheck(){
  for(Neuron* n: _neurons){
    for(Neuron* c: n->children()){
      if(!c->inList(_neurons)){
        cout << "unknown child!!" << endl;
        return false;
      }
      if(!n->inList(c->parents())){
        cout << "child does not recognize its parent!!" << endl;
        return false;
      }
    }
    for(Neuron* p: n->parents()){
      if(!p->inList(_neurons)){
        cout << "unknown parent!!" << endl;
        return false;
      }
      if(!n->inList(p->children())){
        cout << "parent does not recognize its child!!" << endl;
        return false;
      }
    }
    if(n->parent() != this){
      cout << "neuron does not have its animal as parent!!" << endl;
      return false;
    }
  }
  return true;
}

void Animal::doAction(){
  Neuron* neuron = getAction();
  hunger();
  if(!neuron)
    return;
  int neuronType = neuron->type();
  switch(neuronType){
    case ON_MOVE_N:
      if(_posY>0)
        _posY--;
      break;
    case ON_MOVE_S:
      if(_posY<479)
        _posY++;
      break;
    case ON_MOVE_E:
      if(_posX<639)
        _posX++;
      break;
    case ON_MOVE_W:
      if(_posX>0)
        _posX--;
      break;
    case ON_EAT:
      if(_type == CARNIVORE)
        if(_parent->eatHerbivore(_posX, _posY))
          eat();
      if(_type == HERBIVORE)
        if(_parent->eatPlant(_posX, _posY))
          eat();
      break;
  }
}

void Animal::drawNeurons(SDLWindow* window){
  window->drawClear();
  for(Neuron* n : _neurons)
    n->draw(window);
  window->render();
}

int Animal::closestEntity(int type, int dir){
  return _parent->closestEntity(type, dir, _posX, _posY);
}
