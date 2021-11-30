#ifndef OUTPUTNEURON_H
#define OUTPUTNEURON_H

#include "Neurons/Neuron.h"
#include "Constants.h"

class OutputNeuron: public Neuron
{
  public:
    OutputNeuron();
    virtual ~OutputNeuron();
    virtual bool freeChildConnection();
    virtual double compute();
    virtual Neuron* addToCopy(Neuron* n);

  protected:

  private:
};

#endif // OUTPUTNEURON_H
