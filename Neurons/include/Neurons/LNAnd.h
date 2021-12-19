#ifndef LNAND_H
#define LNAND_H

#include "Neurons/LogicNeuron.h"
#include "Constants.h"

class LNAnd: public LogicNeuron
{
  public:
    LNAnd();
    LNAnd(Animal* parent);
    virtual ~LNAnd();
    virtual double compute(int computeId);
    virtual Neuron* deepCopy(Animal* parent);

  protected:

  private:
};

#endif // LNAND_H
