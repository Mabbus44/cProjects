#ifndef MAP_H
#define MAP_H
#include <iostream>
#include "Includes.h"
#include "Graphics/SDLWindow.h"


class Map
{
  public:
    Map();
    virtual ~Map();
    void init();
    bool oneTick();
    int closestEntity(int type, int dir, int x, int y);
    void killCarnivore(Animal* target);
    void killHerbivore(Animal* target);
    void killPlant(Plant* target);
    bool eatHerbivore(int x, int y);
    bool eatPlant(int x, int y);
    void restart();
    void draw(SDLWindow* window);
    void output(string tab, int level);
    Map* deepCopy();
    void deleteEnteties();
    void deleteBestEnteties();
    void free();
    vector<Animal*> carnivores(){return _carnivores;}
    vector<Animal*> herbivores(){return _herbivores;}
    vector<Plant*> plants(){return _plants;}
    vector<Animal*> bestCarnivores(){return _bestCarnivores;}
    vector<Animal*> bestHerbivores(){return _bestHerbivores;}
    SDLWindow* mapDrawnBy = NULL;
    SDLWindow* neuronsDrawnBy = NULL;
    bool runningLogic = false;    //Set to true by consoleHandler while running simulation on map.
    bool allowDrawMap = true;     //If runningLogic, map is only allowed to draw if true. ConsoleHandler is only allowed to simulate if false.
    bool allowDrawNeurons = true;  //If runningLogic, map is only allowed to draw if true. ConsoleHandler is only allowed to simulate if false.

  protected:
    vector<Animal*> _carnivores;
    vector<Animal*> _herbivores;
    vector<Plant*> _plants;
    vector<Animal*> _bestCarnivores;
    vector<Animal*> _bestHerbivores;
    bool _done;
    int _step;
    int _generation;

  private:
};

#endif // MAP_H
