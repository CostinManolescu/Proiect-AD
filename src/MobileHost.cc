#include "MobileHost.h"
#include "ConsensusAlgorithm.h"

Define_Module(MobileHost);


MobileHost::MobileHost()
{
    // Initialize consensusAlgorithm in the constructor initializer list
    consensusAlgorithm = new ConsensusAlgorithm(par("nodeId"), par("groupId"), par("totalNodes"));
}

void MobileHost::initialize()
{
    // Initialize the consensus algorithm with initial parameters
    int initialValue = par("initialValue");
    consensusAlgorithm->startSession(0, initialValue);

    // Schedule the first event
    scheduleAt(0, new cMessage("move"));
}

void MobileHost::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getName(), "ContributionMessage") == 0)
    {
        // Handle contribution message
        ContributionMessage *contributionMsg = check_and_cast<ContributionMessage *>(msg);
        consensusAlgorithm->receiveContribution(msg->getId(), contributionMsg->round, contributionMsg->value);
    }
    else if (strcmp(msg->getName(), "DecisionMessage") == 0)
    {
        // Handle decision message
        DecisionMessage *decisionMsg = check_and_cast<DecisionMessage *>(msg);
        consensusAlgorithm->receiveDecision(msg->getId(), decisionMsg->value);
    }
    // Handle other types of messages if needed
}
