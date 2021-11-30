#ifndef SENSORNEURON_H
#define SENSORNEURON_H

#include "Neurons/Neuron.h"
#include "Constants.h"

class SensorNeuron: public Neuron
{
  public:
    SensorNeuron();
    virtual ~SensorNeuron();
    virtual bool freeParentConnection();
    virtual Neuron* addToCopy(Neuron* n);
    virtual void reRollProperties();

  protected:
    void distToResult(int dist);
    int _bestDistance;
    int _maxDistance;

  private:
};

#endif // SENSORNEURON_H
