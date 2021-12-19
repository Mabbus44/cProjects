#include "Map.h"

Map::Map()
{
  //ctor
}

Map::~Map()
{
  //dtor
}

void Map::init(){
  free();
  for(int i=0; i<PLANTS_PER_SIMULATION; i++)
    _plants.push_back(new Plant(this, rand()%MAP_WIDTH, rand()%MAP_HEIGHT, i));
  for(int i=0; i<HERBIVORES_PER_SIMULATION; i++)
    _herbivores.push_back(new Herbivore(this, rand()%MAP_WIDTH, rand()%MAP_HEIGHT, i));
  for(int i=0; i<CARNIVORES_PER_SIMULATION; i++)
    _carnivores.push_back(new Carnivore(this, rand()%MAP_WIDTH, rand()%MAP_HEIGHT, i));
  _done = false;
  _step = 0;
  _generation = 0;
}

void Map::restart(){
  deleteEnteties();
  for(int i=0; i<PLANTS_PER_SIMULATION; i++)
    _plants.push_back(new Plant(this, rand()%MAP_WIDTH, rand()%MAP_HEIGHT, i));
  if(_bestHerbivores.size() == 0){
    for(int i=0; i<HERBIVORES_PER_SIMULATION; i++)
      _herbivores.push_back(new Herbivore(this, rand()%MAP_WIDTH, rand()%MAP_HEIGHT, i));
  }
  else{
    int i = 0;
    int newI = 0;
    while(_herbivores.size()<HERBIVORES_PER_SIMULATION){
      _herbivores.push_back(_bestHerbivores[i]->deepCopy(this, rand()%MAP_WIDTH, rand()%MAP_HEIGHT, HERBIVORE_START_FOOD, newI));
      i++;
      newI++;
      if(i == (int)_bestHerbivores.size())
        i=0;
    }
    for(Animal* h : _herbivores){
      int mutationCount = rand()%(NEURON_MUTATIONS_PER_ROUND_MAX-NEURON_MUTATIONS_PER_ROUND_MIN)+NEURON_MUTATIONS_PER_ROUND_MIN;
      for(int i=0; i<mutationCount; i++)
        h->mutateNeurons();
    }
  }
  if(_bestCarnivores.size() == 0){
    for(int i=0; i<CARNIVORES_PER_SIMULATION; i++)
      _carnivores.push_back(new Carnivore(this, rand()%MAP_WIDTH, rand()%MAP_HEIGHT, i));
  }
  else{
    int i = 0;
    int newI = 0;
    while(_carnivores.size()<CARNIVORES_PER_SIMULATION){
      _carnivores.push_back(_bestCarnivores[i]->deepCopy(this, rand()%MAP_WIDTH, rand()%MAP_HEIGHT, CARNIVORE_START_FOOD, newI));
      i++;
      newI++;
      if(i == (int)_bestCarnivores.size())
        i=0;
    }
    for(Animal* c : _carnivores){
      int mutationCount = rand()%(NEURON_MUTATIONS_PER_ROUND_MAX-NEURON_MUTATIONS_PER_ROUND_MIN)+NEURON_MUTATIONS_PER_ROUND_MIN;
      for(int i=0; i<mutationCount; i++)
        c->mutateNeurons();
    }
  }
  deleteBestEnteties();
  for(Animal* c : _carnivores)
    if(!c->neuronSanityCheck())
      while(true){}
  for(Animal* c : _herbivores)
    if(!c->neuronSanityCheck())
      while(true){}
  _done = false;
  _step = 0;
  _generation++;
}

void Map::deleteEnteties(){
  for(Animal* h : _herbivores){
    h->free();
    delete h;
  }
  for(Animal* c : _carnivores){
    c->free();
    delete c;
  }
  for(Plant* p : _plants)
    delete p;
  _herbivores.clear();
  _carnivores.clear();
  _plants.clear();
}

void Map::deleteBestEnteties(){
  for(Animal* h : _bestHerbivores){
    h->free();
    delete h;
  }
  for(Animal* c : _bestCarnivores){
    c->free();
    delete c;
  }
  _bestHerbivores.clear();
  _bestCarnivores.clear();
}

bool Map::oneTick(){
  if(_done)
    restart();
  _step++;
  _computeId = 3-_computeId;
  for(Animal* h : _herbivores)
    h->doAction(_computeId);
  for(Animal* c : _carnivores)
    c->doAction(_computeId);
  for(int i=0; i<(int)_herbivores.size(); i++){
    if(_herbivores[i]->isDead()){
      _herbivores[i]->free();
      delete _herbivores[i];
      _herbivores.erase(_herbivores.begin()+i);
      i--;
      if((int)_herbivores.size() == SAVE_HERBIVORES){
        for(Animal* h : _herbivores){
          _bestHerbivores.push_back(h->deepCopy(this));
        }
      }
    }
  }
  for(int i=0; i<(int)_carnivores.size(); i++){
    if(_carnivores[i]->isDead()){
      _carnivores[i]->free();
      delete _carnivores[i];
      _carnivores.erase(_carnivores.begin()+i);
      i--;
      if((int)_carnivores.size() == SAVE_CARNIVORES){
        for(Animal* c : _carnivores){
          _bestCarnivores.push_back(c->deepCopy(this));
        }
      }
    }
  }
  if(_herbivores.size() == 0){
    _done = true;
    return true;
  }
  return false;
}

void Map::killHerbivore(Animal* target){
  for(int i=0; i<(int)_herbivores.size(); i++){
    if(_herbivores[i] == target){
      _herbivores[i]->free();
      delete _herbivores[i];
      _herbivores.erase(_herbivores.begin()+i);
      return;
    }
  }
}

void Map::killCarnivore(Animal* target){
  for(int i=0; i<(int)_carnivores.size(); i++){
    if(_carnivores[i] == target){
      _carnivores[i]->free();
      delete _carnivores[i];
      _carnivores.erase(_carnivores.begin()+i);
      return;
    }
  }
}

void Map::killPlant(Plant* target){
  for(int i=0; i<(int)_plants.size(); i++){
    if(_plants[i] == target){
      delete _plants[i];
      _plants.erase(_plants.begin()+i);
      return;
    }
  }
}

bool Map::eatPlant(int x, int y){
  for(Plant* p : _plants){
    if(p->distance(x, y) < EAT_PLANT_RANGE){
      killPlant(p);
      return true;
    }
  }
  return false;
}

bool Map::eatHerbivore(int x, int y){
  for(Animal* h : _herbivores){
    if(h->distance(x, y) < EAT_HERBIVORE_RANGE){
      killHerbivore(h);
      return true;
    }
  }
  return false;
}

void Map::draw(MapWindow* window){
  for(Plant* p : _plants)
    p->draw(window);
  for(Animal* h : _herbivores)
    h->draw(window);
  for(Animal* c : _carnivores)
    c->draw(window);
  Animal* a = getSelectedAnimal();
  if(a)
    a->draw(window, true);
}

int Map::closestEntity(int type, int dir, int x, int y){
  int minDist = SENSORS_MAX_DIST;
  switch(type){
    case CARNIVORE:
      for(Animal* c: _carnivores){
        if(c->isInDirection(x, y, dir)){
          int dist = c->distance(x, y);
          minDist = min(minDist, dist);
        }
      }
      break;
    case HERBIVORE:
      for(Animal* h: _herbivores){
        if(h->isInDirection(x, y, dir)){
          int dist = h->distance(x, y);
          minDist = min(minDist, dist);
        }
      }
      break;
    case PLANT:
      for(Entity* p: _plants){
        if(p->isInDirection(x, y, dir)){
          int dist = p->distance(x, y);
          minDist = min(minDist, dist);
        }
      }
      break;
  }
  return minDist;
}

void Map::output(string tab, int level){
  int nextLevel = level-1;
  if(level == OUTPUT_ALL)
    nextLevel = OUTPUT_ALL;
  switch(level){
    case OUTPUT_ONELINE:
      cout << tab << "Address: " << this << " Generation: " << _generation << " Step: " << _step << " Generation done: " << _done << " Carnivores: " << _carnivores.size() << " Herbivores: " << _herbivores.size() << " Plants: " << _plants.size();
      break;
    case OUTPUT_ALL:
    case OUTPUT_DEEP:
    case OUTPUT_OVERVIEW:
      cout << tab << "Address: " << this << endl;
      cout << tab << "Generation: " << _generation << endl;
      cout << tab << "Step: " << _step << endl;
      cout << tab << "Generation done: " << _done << endl;
      cout << tab << "Carnivores: " << _carnivores.size() << endl;
      for(int i=0; i<(int)_carnivores.size(); i++){
        _carnivores[i]->output(tab+to_string(i)+": ", nextLevel);
        if(nextLevel != OUTPUT_ONELINE)
          cout << tab+"  " << "----------";
        cout << endl;
      }
      cout << tab << "Herbivores: " << _herbivores.size() << endl;
      for(int i=0; i<(int)_herbivores.size(); i++){
        _herbivores[i]->output(tab+to_string(i)+": ", nextLevel);
        if(nextLevel != OUTPUT_ONELINE)
          cout << tab+"  " << "----------";
        cout << endl;
      }
      cout << tab << "Plants: " << _plants.size() << endl;
      cout << tab << "Best herbivores: " << _bestHerbivores.size() << endl;
      for(int i=0; i<(int)_bestHerbivores.size(); i++){
        _bestHerbivores[i]->output(tab+to_string(i)+": ", nextLevel);
        if(nextLevel != OUTPUT_ONELINE)
          cout << tab+"  " << "----------";
        cout << endl;
      }
      cout << tab << "Best carnivores: " << _bestCarnivores.size() << endl;
      for(int i=0; i<(int)_bestCarnivores.size(); i++){
        _bestCarnivores[i]->output(tab+to_string(i)+": ", nextLevel);
        if(nextLevel != OUTPUT_ONELINE)
          cout << tab+"  " << "----------";
        cout << endl;
      }
  }
}

Map* Map::deepCopy(){
  Map* ret = new Map();
  for(Animal* a : _bestCarnivores)
    ret->_bestCarnivores.push_back(a->deepCopy(ret));
  for(Animal* a : _bestHerbivores)
    ret->_bestHerbivores.push_back(a->deepCopy(ret));
  for(Animal* a : _carnivores)
    ret->_carnivores.push_back(a->deepCopy(ret));
  for(Animal* a : _herbivores)
    ret->_herbivores.push_back(a->deepCopy(ret));
  for(Plant* p : _plants)
    ret->_plants.push_back(p->deepCopy(ret));
  ret->_done = _done;
  ret->_step = _step;
  ret->_generation = _generation;
  return ret;
}

void Map::free(){
  deleteEnteties();
  deleteBestEnteties();
}

void Map::changeSelectedAnimal(bool add){
  if(add)
    selectedAnimalIndex++;
  else
    selectedAnimalIndex--;
  int animalCount;
  switch(selectedAnimalType){
    case HERBIVORE_NEURON:
      animalCount = herbivores().size();
      break;
    case CARNIVORE_NEURON:
      animalCount = carnivores().size();
      break;
    case BEST_HERBIVORE_NEURON:
      animalCount = bestHerbivores().size();
      break;
    case BEST_CARNIVORE_NEURON:
      animalCount = bestCarnivores().size();
      break;
  }
  if(selectedAnimalIndex>=animalCount)
    selectedAnimalIndex = 0;
  if(selectedAnimalIndex<0)
    selectedAnimalIndex = animalCount-1;
}

void Map::changeSelectedAnimalType(bool add){
  selectedAnimalIndex = 0;
  if(add)
    selectedAnimalType++;
  else
    selectedAnimalType--;
  if(selectedAnimalType<0)
    selectedAnimalType = DRAW_NEURON_TYPE_COUNT-1;
  if(selectedAnimalType>=DRAW_NEURON_TYPE_COUNT)
    selectedAnimalType = 0;
}

Animal* Map::getSelectedAnimal(){
  switch(selectedAnimalType){
    case HERBIVORE_NEURON:
      if(selectedAnimalIndex>=0 && selectedAnimalIndex<(int)_herbivores.size())
        return _herbivores[selectedAnimalIndex];
      break;
    case CARNIVORE_NEURON:
      if(selectedAnimalIndex>=0 && selectedAnimalIndex<(int)_carnivores.size())
        return _carnivores[selectedAnimalIndex];
      break;
    case BEST_HERBIVORE_NEURON:
      if(selectedAnimalIndex>=0 && selectedAnimalIndex<(int)_bestHerbivores.size())
        return _bestHerbivores[selectedAnimalIndex];
      break;
    case BEST_CARNIVORE_NEURON:
      if(selectedAnimalIndex>=0 && selectedAnimalIndex<(int)_bestCarnivores.size())
        return _bestCarnivores[selectedAnimalIndex];
      break;
  }
  return NULL;
}

void Map::addHerbivoresToHistory(){

}
