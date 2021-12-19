#ifndef NEURON_H
#define NEURON_H

#include "Constants.h"
#include <vector>
#include <string>
#include "Graphics/SDLWindow.h"
#include <sstream>
#include <iomanip>

using namespace std;

class Animal;

class Neuron
{
  public:
    Neuron();
    virtual ~Neuron();
    virtual bool connectParent(Neuron* newParent);
    virtual bool connectChild(Neuron* newChild);
    virtual bool freeParentConnection();
    virtual bool freeChildConnection();
    virtual double compute(int computeId)=0;
    virtual Neuron* deepCopy(Animal* parent) = 0;
    virtual Neuron* addToCopy(Neuron* n);
    virtual void reRollProperties();
    bool myOffspring(Neuron*);
    void disconnect2way();
    void disconnectParent(Neuron* parent);
    void disconnectChild(Neuron* child);
    void disconnectRandomParent2way();
    void disconnectRandomChild2way();
    void replaceParent(Neuron* oldParent, Neuron* newParent);
    void replaceChild(Neuron* oldChild, Neuron* newChild);
    void replaceNeuron(Neuron* oldNeuron);
    bool inList(vector<Neuron*>& neuronList);
    void draw(NeuronsWindow* window, int xOffset, int yOffset);
    void output(string tab, int level);
    void resetLevelColumn() {_level =0; _column=0;}
    void setLevel(int level); int getLevel(){return _level;}
    void setColumn(vector<int>& columns); int getColumn(){return _column;}
    void multiplyColumn(vector<int>& columnDists);
    vector<Neuron*>& parents(){return _parents;}
    vector<Neuron*>& children(){return _children;}
    int family() {return _family;}
    int type(){return _type;}
    Animal* parent(){return _parent;}
    int index;

  protected:
    double _postCompute();
    int _level;
    int _column;
    int _family;
    int _type;
    int _computeId=0;
    double _computeResult;
    double _factor;
    double _bonus;
    Animal* _parent;
    vector<Neuron*> _parents;
    vector<Neuron*> _children;
};

#endif // NEURON_H
