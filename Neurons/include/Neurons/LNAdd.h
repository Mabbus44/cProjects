#ifndef LNADD_H
#define LNADD_H

#include "Neurons/LogicNeuron.h"
#include "Constants.h"

class LNAdd: public LogicNeuron
{
  public:
    LNAdd();
    LNAdd(Animal* parent);
    virtual ~LNAdd();
    virtual double compute(int computeId);
    virtual Neuron* deepCopy(Animal* parent);

  protected:

  private:
};

#endif // LNADD_H
