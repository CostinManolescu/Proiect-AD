#ifndef MOBILEHOST_H
#define MOBILEHOST_H

#include <omnetpp.h>
#include "ConsensusAlgorithm.h"

using namespace omnetpp;

class MobileHost : public cSimpleModule
{
private:
    ConsensusAlgorithm *consensusAlgorithm;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

public:
    MobileHost();
};

#endif // MOBILEHOST_H
