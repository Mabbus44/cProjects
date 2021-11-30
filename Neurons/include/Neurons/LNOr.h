#ifndef LNOR_H
#define LNOR_H

#include "Neurons/LogicNeuron.h"
#include "Constants.h"

class LNOr: public LogicNeuron
{
  public:
    LNOr();
    LNOr(Animal* parent);
    virtual ~LNOr();
    virtual double compute();
    virtual Neuron* deepCopy(Animal* parent);

  protected:

  private:
};

#endif // LNOR_H
