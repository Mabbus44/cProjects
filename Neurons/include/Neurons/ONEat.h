#ifndef ONEAT_H
#define ONEAT_H

#include "Neurons/OutputNeuron.h"
#include "Constants.h"

class ONEat: public OutputNeuron
{
  public:
    ONEat();
    ONEat(Animal* parent);
    virtual ~ONEat();
    virtual Neuron* deepCopy(Animal* parent);

  protected:

  private:
};

#endif // ONEAT_H
