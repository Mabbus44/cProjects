#ifndef ENTITIES_H
#define ENTITIES_H
#include "Constants.h"
#include <stdint.h>

class Entity
{
  public:
    Entity();
    Entity(int x, int y){_posX = x; _posY = y;}
    virtual ~Entity();
    EntityType entityType() {return _entityType;}
    int posX() {return _posX;}
    int posY() {return _posY;}
    void posX(int posX) {_posX = posX;}
    void posY(int posY) {_posY = posY;}

  protected:

    int _posX, _posY;
    EntityType _entityType;
  private:
};

class Animal: public Entity
{
  public:
    Animal(){_factors = new uint8_t[INPUTS_PER_SQUARE * (SENSOR_RADIUS_SQUARES * 2 + 1) * (SENSOR_RADIUS_SQUARES * 2 + 1) * AnimalAction::COUNT];}
    Animal(int x, int y) : Entity(x, y){_factors = new uint8_t[INPUTS_PER_SQUARE * (SENSOR_RADIUS_SQUARES * 2 + 1) * (SENSOR_RADIUS_SQUARES * 2 + 1) * AnimalAction::COUNT];}
    virtual ~Animal(){delete [] _factors;}
    void decideAction(uint8_t* input);
    AnimalAction action() {return _action;}
    void addEnergy(int newEnergy);
    bool removeEnergy(int lostEnergy);

  protected:
    AnimalAction _action;
    uint8_t* _factors;
    int _energy = MAX_ENERGY;

  private:
};

class Carnivore: public Animal
{
  public:
    Carnivore(){_entityType = EntityType::CARNIVORE;}
    Carnivore(int x, int y) : Animal(x, y){_entityType = EntityType::CARNIVORE;}
    virtual ~Carnivore(){}

  protected:

  private:
};

class Herbivore: public Animal
{
  public:
    Herbivore(){_entityType = EntityType::HERBIVORE;}
    Herbivore(int x, int y) : Animal(x, y){_entityType = EntityType::HERBIVORE;}
    virtual ~Herbivore(){}

  protected:

  private:
};

class Plant: public Entity
{
  public:
    Plant(){_entityType = EntityType::PLANT;}
    Plant(int x, int y) : Entity(x, y){_entityType = EntityType::PLANT;}
    virtual ~Plant(){}

  protected:

  private:
};

struct carnivoreMatch
{
    Carnivore* m_value;

    carnivoreMatch(Carnivore* value) : m_value(value) {}

    bool operator()(const Carnivore* ptr) const
    {
        return (ptr == m_value);
    }
};

struct herbivoreMatch
{
    Herbivore* m_value;

    herbivoreMatch(Herbivore* value) : m_value(value) {}

    bool operator()(const Herbivore* ptr) const
    {
        return (ptr == m_value);
    }
};

struct plantMatch
{
    Plant* m_value;

    plantMatch(Plant* value) : m_value(value) {}

    bool operator()(const Plant* ptr) const
    {
        return (ptr == m_value);
    }
};
#endif // ENTITIES_H
