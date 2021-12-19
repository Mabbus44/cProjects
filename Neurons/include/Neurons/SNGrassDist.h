#ifndef SNGrassDist_H
#define SNGrassDist_H

#include "Neurons/SensorNeuron.h"
#include "Constants.h"

class SNGrassDist: public SensorNeuron
{
  public:
    SNGrassDist();
    SNGrassDist(Animal* parent, int type);
    virtual ~SNGrassDist();
    virtual double compute(int computeId);
    virtual Neuron* deepCopy(Animal* parent);

  protected:

  private:
};

#endif // SNGrassDist_H
