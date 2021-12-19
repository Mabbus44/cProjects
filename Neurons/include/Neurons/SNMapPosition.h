#ifndef SNMAPPOSITION_H
#define SNMAPPOSITION_H

#include "Neurons/SensorNeuron.h"
#include "Constants.h"

class SNMapPosition: public SensorNeuron
{
  public:
    SNMapPosition();
    SNMapPosition(Animal* parent, int type);
    virtual ~SNMapPosition();

    virtual double compute(int computeId);
    virtual Neuron* deepCopy(Animal* parent);

  protected:
  private:
};

#endif // SNMAPPOSITION_H
