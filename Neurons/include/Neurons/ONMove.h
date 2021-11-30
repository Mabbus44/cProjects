#ifndef ONMOVE_H
#define ONMOVE_H

#include "Neurons/OutputNeuron.h"
#include "Constants.h"

class ONMove: public OutputNeuron
{
  public:
    ONMove();
    ONMove(Animal* parent, int type);
    virtual ~ONMove();
    virtual Neuron* deepCopy(Animal* parent);

  protected:

  private:
};

#endif // ONMOVE_H
