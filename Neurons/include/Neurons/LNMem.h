#ifndef LNMEM_H
#define LNMEM_H

#include "Neurons/LogicNeuron.h"
#include "Constants.h"

class LNMem: public LogicNeuron
{
  public:
    LNMem();
    LNMem(Animal* parent);
    virtual ~LNMem();
    virtual bool freeParentConnection();
    virtual bool freeChildConnection();
    virtual double compute(int computeId);
    void computeMem(int computeId);
    virtual Neuron* deepCopy(Animal* parent);

  protected:

  private:
};

#endif // LNMEM_H
