#ifndef ANIMAL_H
#define ANIMAL_H

#include "Enteties/Entity.h"
#include "Neurons/Neuron.h"
#include <vector>
#include "Graphics/SDLWindow.h"

using namespace std;

class Animal: public Entity
{
  public:
    Animal();
    virtual ~Animal();
    void deleteNeuron(int i);
    void generateNeurons();
    void createRandomNeuron(bool connectChildren=false, bool connectParents=false, int copyNeuronId=-1);
    void connectNeuronToParents(Neuron* n);
    void connectNeuronToChildren(Neuron* n);
    void rewireNeuron(int index);
    void mutateNeurons();
    virtual void eat(){}
    void doAction(int computeId);
    void hunger(){_bellyFood--;}
    bool isDead(){return _bellyFood<=0;}
    Animal* deepCopy(Map* parent, int x=-1, int y=-1, int bellyFood=-1, int index=-1);
    bool neuronSanityCheck();
    int closestEntity(int type, int dir);
    void free();
    void prepareDrawNeurons();
    void drawNeurons(NeuronsWindow* window, int xOffset, int yOffset);
    void output(string tab, int level);
    Neuron* getAction(int computeId);
    vector<Neuron*> neurons(){return _neurons;}
    bool selected = false;
    int parentIndex=-1;

  protected:
    vector<Neuron*> _neurons;
    int _bellyFood;

};

#endif // ANIMAL_H
