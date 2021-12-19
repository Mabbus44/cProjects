#ifndef SNCarnivoreDist_H
#define SNCarnivoreDist_H

#include "Neurons/SensorNeuron.h"
#include "Constants.h"

class SNCarnivoreDist: public SensorNeuron
{
  public:
    SNCarnivoreDist();
    SNCarnivoreDist(Animal* parent, int type);
    virtual ~SNCarnivoreDist();
    virtual double compute(int computeId);
    virtual Neuron* deepCopy(Animal* parent);

  protected:

  private:
};

#endif // SNCarnivoreDist_H
