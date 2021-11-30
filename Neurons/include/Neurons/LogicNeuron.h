#ifndef LOGICNEURON_H
#define LOGICNEURON_H

#include "Neurons/Neuron.h"
#include "Constants.h"

class LogicNeuron: public Neuron
{
  public:
    LogicNeuron();
    virtual ~LogicNeuron();
    virtual Neuron* addToCopy(Neuron* n);

  protected:

  private:
};

#endif // LOGICNEURON_H
