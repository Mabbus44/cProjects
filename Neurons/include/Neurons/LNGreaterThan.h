#ifndef LNGREATERTHAN_H
#define LNGREATERTHAN_H

#include "Neurons/LogicNeuron.h"
#include "Constants.h"

class LNGreaterThan: public LogicNeuron
{
  public:
    LNGreaterThan();
    LNGreaterThan(Animal* parent);
    virtual ~LNGreaterThan();
    virtual double compute(int computeId);
    virtual Neuron* deepCopy(Animal* parent);

  protected:

  private:
};

#endif // LNGREATERTHAN_H
