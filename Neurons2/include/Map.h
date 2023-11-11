#ifndef MAP_H
#define MAP_H
#include <iostream>
#include "Graphics/SDLWindow.h"
#include "Entities.h"
#include <fstream>
#include <json/json.h>
#include <list>
#include <algorithm>

using namespace Json;

class EntitySpawner
{
  public:
    EntitySpawner(){}
    virtual ~EntitySpawner(){free();}
    bool loadSettings(Value input);
    void free(){}
    int entityCount() {return _entityCount;}
    EntityType entityType() {return _entityType;};
    int minX() {return _minX;}
    int minY() {return _minY;}
    int maxX(int mapMax);
    int maxY(int mapMax);
    int sizeX(int mapMax);
    int sizeY(int mapMax);

  protected:
  private:
    EntityType _entityType;
    SpawnerType _spawnerType;
    int _entityCount;
    int _minX, _minY, _maxX, _maxY;
};

class Map
{
  public:
    Map();
    virtual ~Map();
    bool resetMap();
    bool loadMapSettings(string fileName);
    bool tick();
    void draw(MapWindow* window, EntityType entityType, int entityId);
    bool validConfig() {return _validConfig;}
    bool pause=false;
    int runManual = 0;
    void output(string tab, OutputLevel level);

  protected:

  private:
    void clearMap();
    void free();
    uint8_t* inputFromArea(int posX, int posY);
    void inputFromSquare(int posX, int posY, uint8_t* input, int inputPos);
    void decideAcitons();
    void performActions();
    void performAction(Animal* animal);
    void eat(Animal* animal);
    void kill(Entity* animal);
    void animalMove(Animal* animal, AnimalAction moveAction);
    Entity* findEntity(int posX, int posY, int radius, EntityType entityType);
    bool _validConfig = false;
    bool _mapSetUp = false;
    int _sizeX, _sizeY;
    vector<vector<Entity*>> _map;
    vector<Carnivore*> _carnivores;
    vector<Herbivore*> _herbivores;
    vector<Plant*> _plants;
    list<EntitySpawner*> _entitySpawners;
};

#endif // MAP_H
