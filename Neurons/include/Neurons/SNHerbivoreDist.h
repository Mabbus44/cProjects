#ifndef SNHerbivoreDist_H
#define SNHerbivoreDist_H

#include "Neurons/SensorNeuron.h"
#include "Constants.h"

class SNHerbivoreDist: public SensorNeuron
{
  public:
    SNHerbivoreDist();
    SNHerbivoreDist(Animal* parent, int type);
    virtual ~SNHerbivoreDist();
    virtual double compute();
    virtual Neuron* deepCopy(Animal* parent);

  protected:

  private:
};

#endif // SNHerbivoreDist_H
