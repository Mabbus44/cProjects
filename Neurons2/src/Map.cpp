#include "Map.h"

bool EntitySpawner::loadSettings(Value input){
  if(input["spawnerType"] == "evenDistribution")
    _spawnerType = SpawnerType::EVEN_DISTROBUTION;
  else{
    cout << "Error: Invalid spawnertype in entitySpawner " << input << endl;
    return false;
  }
  if(input["entityType"] == "carnivore")
    _entityType = EntityType::CARNIVORE;
  else if(input["entityType"] == "herbivore")
    _entityType = EntityType::HERBIVORE;
  else if(input["entityType"] == "plant")
    _entityType = EntityType::PLANT;
  else{
    cout << "Error: Invalid entityType in entitySpawner " << input << endl;
    return false;
  }
  if(input["entityCount"].isIntegral() && input["minX"].isIntegral() && input["maxX"].isIntegral() && input["minY"].isIntegral() &&
        input["maxY"].isIntegral()){
    _entityCount = input["entityCount"].asInt();
    _minX = input["minX"].asInt();
    _maxX = input["maxX"].asInt();
    _minY = input["minY"].asInt();
    _maxY = input["maxY"].asInt();
  }else{
    cout << "Error: Missing required value (entityCount, minX, maxX, minY or maxY) in entitySpawner " << input << endl;
    return false;
  }
  return true;
}

int EntitySpawner::maxX(int mapMax){
  if(_maxX == -1 || _maxX > mapMax)
    return mapMax;
  else
    return _maxX;
}

int EntitySpawner::maxY(int mapMax){
  if(_maxY == -1 || _maxY > mapMax)
    return mapMax;
  else
    return _maxY;
}

int EntitySpawner::sizeX(int mapMax){
  if(_maxX == -1 || _maxX > mapMax)
    return mapMax-_minX+1;
  else
    return _maxX-_minX+1;
}

int EntitySpawner::sizeY(int mapMax){
  if(_maxY == -1 || _maxY > mapMax)
    return mapMax-_minY+1;
  else
    return _maxY-_minY+1;
}


Map::Map()
{
  //ctor
}

Map::~Map()
{
  cout << "~Map" << endl;
  free();
}

bool Map::resetMap(){
  if(!_validConfig){
    cout << "Error: Cannot reset map, config not valid" << endl;
    return false;
  }
  clearMap();
  vector<Entity*> row = vector<Entity*>(_sizeX, nullptr);
  //cout << "Col: " << _sizeX << endl;
  _map = vector<vector<Entity*>>(_sizeY, row);
  //cout << "Row: " << _sizeY << endl;

  int carnivoreCount = 0;
  int herbivoreCount = 0;
  int plantCount = 0;

  for(EntitySpawner* e: _entitySpawners){
    if(e->entityType() == EntityType::CARNIVORE)
      carnivoreCount += e->entityCount();
    else if(e->entityType() == EntityType::HERBIVORE)
      herbivoreCount += e->entityCount();
    else if(e->entityType() == EntityType::PLANT)
      plantCount += e->entityCount();
  }

  //cout << "Making space for " << carnivoreCount << " carnivores" << endl;
  //cout << "Making space for " << herbivoreCount << " herbivores" << endl;
  //cout << "Making space for " << plantCount << " plants" << endl;
  _carnivores = vector<Carnivore*>(carnivoreCount, nullptr);
  _herbivores = vector<Herbivore*>(herbivoreCount, nullptr);
  _plants = vector<Plant*>(plantCount, nullptr);

  int carnivoreId = 0;
  int herbivoreId = 0;
  int plantId = 0;
  for(EntitySpawner* spawner: _entitySpawners){
    //cout << "Running spawner" << endl;
    int entityCount = spawner->entityCount();
    for(int eId=0; eId < entityCount; eId++){
      int retries = 0;
      bool entityCreated = false;
      while(!entityCreated && retries < 3){
        int posX = spawner->minX() + (rand() % spawner->sizeX(_sizeX-1));
        int posY = spawner->minY() + (rand() % spawner->sizeY(_sizeY-1));
        //cout << "Tries to create entity " << eId << " at (" << posX << ", " << posY << ")" << endl;
        if(_map[posX][posY] == nullptr){
          Entity* e;
          if(spawner->entityType() == EntityType::CARNIVORE){
            //cout << "Add carnivore " << carnivoreId << endl;
            e = new Carnivore(posX, posY);
            _carnivores[carnivoreId++] = (Carnivore*)e;
          }else if(spawner->entityType() == EntityType::HERBIVORE){
            //cout << "Add erbivore " << herbivoreId << endl;
            e = new Herbivore(posX, posY);
            _herbivores[herbivoreId++] = (Herbivore*)e;
          }else if(spawner->entityType() == EntityType::PLANT){
            //cout << "Add plant " << plantId << endl;
            e = new Plant(posX, posY);
            _plants[plantId++] = (Plant*)e;
          }
          _map[posX][posY] = e;
          entityCreated = true;
        }else{
          retries++;
        }
      }
    }
  }

  cout << "Map set up" << endl;
  _mapSetUp = true;
  return true;
}

bool Map::loadMapSettings(string fileName){
  ifstream file(fileName);
  if(file.fail()){
    cout << "Error: could not open file " << fileName << endl;
    return _validConfig;
  }
  Value fileContents;
  try{
    file >> fileContents;
  }
  catch(exception& e){
    cout << "Error: Invalid json format in file " << fileName << endl;
    cout << e.what() << endl;
    return _validConfig;
  }
  free();
  if(fileContents.isMember("entitySpawners") && fileContents["entitySpawners"].isArray()){
    Value entitySpawnersInput = fileContents["entitySpawners"];
    for(Value::ArrayIndex spawnerId = 0; spawnerId < entitySpawnersInput.size(); spawnerId++){
      EntitySpawner* e = new EntitySpawner();
      if(e->loadSettings(entitySpawnersInput[spawnerId]))
        _entitySpawners.push_back(e);
      else
        delete e;
    }
  }
  if(fileContents["sizeX"].isIntegral() && fileContents["sizeY"].isIntegral() && fileContents["sizeX"].asInt() > 0 &&
        fileContents["sizeY"].asInt() > 0){
    _sizeX = fileContents["sizeX"].asInt();
    _sizeY = fileContents["sizeY"].asInt();
  }else{
    cout << "Error: Missing or invalid required value (sizeX, sizeY) in map settings " << fileContents << endl;
    return _validConfig;
  }
  _validConfig = true;
  cout << "Mapsettings loaded successfully" << endl;
  return _validConfig;
}

bool Map::tick(){
  decideAcitons();
  performActions();
  return false;
}

void Map::draw(MapWindow* window, EntityType entityType, int entityId){
  Entity* selected = nullptr;
  if(entityId >= 0){
    if(entityType == EntityType::PLANT){
      if(entityId < (int)_plants.size())
        selected = _plants[entityId];
    }
    if(entityType == EntityType::HERBIVORE){
      if(entityId < (int)_herbivores.size())
        selected = _herbivores[entityId];
    }
    if(entityType == EntityType::CARNIVORE){
      if(entityId < (int)_carnivores.size())
        selected = _carnivores[entityId];
    }
  }
  for(Entity* e : _plants)
    window->drawPixel(e->posX(), e->posY(), 0, 0xFF, 0, e == selected);
  for(Entity* e : _herbivores)
    window->drawPixel(e->posX(), e->posY(), 0, 0, 0xFF, e == selected);
  for(Entity* e : _carnivores)
    window->drawPixel(e->posX(), e->posY(), 0xFF, 0, 0, e == selected);
}

void Map::free(){
  cout << "Map::free()" << endl;
  _validConfig = false;
  clearMap();
  for(EntitySpawner* s: _entitySpawners)
    delete s;
  _entitySpawners.clear();
}

void Map::clearMap(){
  cout << "Clearing map" << endl;
  _mapSetUp = false;
  _map.clear();
  for(Carnivore* e: _carnivores)
    delete e;
  _carnivores.clear();
  for(Herbivore* e: _herbivores)
    delete e;
  _herbivores.clear();
  for(Plant* e: _plants)
    delete e;
  _plants.clear();
}

uint8_t* Map::inputFromArea(int posX, int posY){
  uint8_t* input = new uint8_t[INPUTS_PER_SQUARE * (SENSOR_RADIUS_SQUARES * 2 + 1) * (SENSOR_RADIUS_SQUARES * 2 + 1)];
  int inputPos = 0;
  posX -= SENSOR_RADIUS_SQUARES;
  if(posX < 0)
    posX = posX % _sizeX;
  posY -= SENSOR_RADIUS_SQUARES;
  if(posY < 0)
    posY = posY % _sizeY;
  int row = 0;
  int rowCount = SENSOR_RADIUS_SQUARES * 2 + 1;
  while(row<rowCount){
    inputFromSquare(posX, posY, input, inputPos);
    inputPos += INPUTS_PER_SQUARE;
    posX++;
    if(posX == _sizeX){
      posX = 0;
      posY++;
      if(posY == _sizeY){
        posY = 0;
        row++;
      }
    }
  }
  return input;
}

void Map::inputFromSquare(int posX, int posY, uint8_t* input, int inputPos){
  if(_map[posX][posY] == nullptr){
    input[inputPos] = 255;
    input[inputPos+1] = 0;
    input[inputPos+2] = 0;
    input[inputPos+3] = 0;
  }else if(_map[posX][posY]->entityType() == EntityType::CARNIVORE){
    input[inputPos] = 0;
    input[inputPos+1] = 255;
    input[inputPos+2] = 0;
    input[inputPos+3] = 0;
  }else if(_map[posX][posY]->entityType() == EntityType::HERBIVORE){
    input[inputPos] = 0;
    input[inputPos+1] = 0;
    input[inputPos+2] = 255;
    input[inputPos+3] = 0;
  }else if(_map[posX][posY]->entityType() == EntityType::PLANT){
    input[inputPos] = 0;
    input[inputPos+1] = 0;
    input[inputPos+2] = 0;
    input[inputPos+3] = 255;
  }
}

void Map::decideAcitons(){
  for(Carnivore* c: _carnivores)
    c->decideAction(inputFromArea(c->posX(), c->posY()));
  for(Herbivore* h: _herbivores)
    h->decideAction(inputFromArea(h->posX(), h->posY()));
}

void Map::performActions(){
  for(Carnivore* c: _carnivores)
    performAction((Animal*)c);
  for(Herbivore* h: _herbivores)
    performAction((Animal*)h);
}

void Map::performAction(Animal* animal){
  AnimalAction action = animal->action();
  switch(action){
    case AnimalAction::EAT:
      eat(animal);
      break;
    case AnimalAction::MOVE_DOWN:
    case AnimalAction::MOVE_LEFT:
    case AnimalAction::MOVE_RIGHT:
    case AnimalAction::MOVE_UPP:
      animalMove(animal, action);
      break;
    case AnimalAction::NOTHING:
      if(!animal->removeEnergy(1))
        kill(animal);
      break;
    case AnimalAction::COUNT:
      cout << "Error: AnimalAction::COUNT should not be used" << endl;
      break;
  }
}

void Map::eat(Animal* animal){
  EntityType entityType = animal->entityType();
  EntityType preyType;
  Animal* prey;
  if(entityType == EntityType::CARNIVORE)
    preyType = EntityType::HERBIVORE;
  else if(entityType == EntityType::HERBIVORE)
    preyType = EntityType::PLANT;
  prey = (Animal*)(findEntity(animal->posX(), animal->posY(), 3, preyType));
  if(prey == nullptr)
    return;
  kill(prey);
  if(entityType == EntityType::CARNIVORE)
    animal->addEnergy(300);
  else if(entityType == EntityType::HERBIVORE)
    animal->addEnergy(100);
}

void Map::kill(Entity* entity){
  _map[entity->posX()][entity->posY()] = nullptr;
  if(entity->entityType() == EntityType::CARNIVORE)
    _carnivores.erase(find_if(_carnivores.begin(), _carnivores.end(), carnivoreMatch((Carnivore*)entity)));
  else if(entity->entityType() == EntityType::HERBIVORE)
    _herbivores.erase(find_if(_herbivores.begin(), _herbivores.end(), herbivoreMatch((Herbivore*)entity)));
  else if(entity->entityType() == EntityType::PLANT)
    _plants.erase(find_if(_plants.begin(), _plants.end(), plantMatch((Plant*)entity)));
  delete entity;
}

void Map::animalMove(Animal* animal, AnimalAction moveAction){
  int oldPosX = animal->posX();
  int oldPosY = animal->posY();
  int newPosX, newPosY;
  switch(moveAction){
    case AnimalAction::MOVE_DOWN:
      newPosX = oldPosX;
      newPosY = oldPosY + 1;
      if(newPosY == _sizeY)
        newPosY = 0;
      break;
    case AnimalAction::MOVE_LEFT:
      newPosX = oldPosX - 1;
      newPosY = oldPosY;
      if(newPosX < 0)
        newPosX = _sizeX-1;
      if(_map[newPosX][oldPosY] == nullptr){
        _map[newPosX][oldPosY] = animal;
        _map[oldPosX][oldPosY] = nullptr;
        animal->posX(newPosX);
      }
      break;
    case AnimalAction::MOVE_RIGHT:
      newPosX = oldPosX + 1;
      newPosY = oldPosY;
      if(newPosX == _sizeX)
        newPosX = 0;
      if(_map[newPosX][oldPosY] == nullptr){
        _map[newPosX][oldPosY] = animal;
        _map[oldPosX][oldPosY] = nullptr;
        animal->posX(newPosX);
      }
      break;
    case AnimalAction::MOVE_UPP:
      newPosX = oldPosX;
      newPosY = oldPosY - 1;
      if(newPosY < 0)
        newPosY = _sizeY-1;
      if(_map[oldPosX][newPosY] == nullptr){
        _map[oldPosX][newPosY] = animal;
        _map[oldPosX][oldPosY] = nullptr;
        animal->posY(newPosY);
      }
    default:
      cout << "Error: non move action sent to move function" << endl;
      break;
  }
  if(_map[newPosX][newPosY] != nullptr){
    if(!animal->removeEnergy(1))
      kill(animal);
    return;
  }
  _map[newPosX][newPosY] = animal;
  _map[oldPosX][oldPosY] = nullptr;
  animal->posX(newPosX);
  animal->posY(newPosY);
  if(!animal->removeEnergy(10))
    kill(animal);
}

Entity* Map::findEntity(int posX, int posY, int radius, EntityType entityType){
  int sideLen = 2; // Side len is actually 3, but the corners is shared between two sides, so we just look at 2 squares per side
  for(int r = 0; r < radius; r++){
    posX++;
    if(posX == _sizeX)
      posX = 0;
    posY--;
    if(posY < 0)
      posY = _sizeY - 1;
    for(int dy = 0; dy < sideLen; dy++){
      if(_map[posX][posY] != nullptr && _map[posX][posY]->entityType() == entityType)
        return _map[posX][posY];
      posY++;
      if(posY == _sizeY)
        posY = 0;
    }
    for(int dx = 0; dx < sideLen; dx++){
      if(_map[posX][posY] != nullptr && _map[posX][posY]->entityType() == entityType)
        return _map[posX][posY];
      posX--;
      if(posX < 0)
        posX = _sizeX - 1;
    }
    for(int dy = 0; dy < sideLen; dy++){
      if(_map[posX][posY] != nullptr && _map[posX][posY]->entityType() == entityType)
        return _map[posX][posY];
      posY--;
      if(posY < 0)
        posY = _sizeY - 1;
    }
    for(int dx = 0; dx < sideLen; dx++){
      if(_map[posX][posY] != nullptr && _map[posX][posY]->entityType() == entityType)
        return _map[posX][posY];
      posX++;
      if(posX == _sizeX)
        posX = 0;
    }
    sideLen += 2;
  }
  return nullptr;
}

void Map::output(string tab, OutputLevel level){
  switch(level){
    case OutputLevel::OUTPUT_ONELINE:
    case OutputLevel::OUTPUT_ALL:
    case OutputLevel::OUTPUT_DEEP:
    case OutputLevel::OUTPUT_OVERVIEW:
      cout << tab << "Address: " << this << " Carnivores: " << _carnivores.size() << " Herbivores: " << _herbivores.size() << " Plants: " << _plants.size();
      break;
  }
}
