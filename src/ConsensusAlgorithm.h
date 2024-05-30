#ifndef CONSENSUSALGORITHM_H
#define CONSENSUSALGORITHM_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <omnetpp.h>

using namespace std;
using namespace omnetpp;

struct ContributionMessage : public cMessage {
    int round;
    int value;
};

struct DecisionMessage : public cMessage {
    int value;
};

class ConsensusAlgorithm : public cSimpleModule{
private:
    int id;
    int groupId;
    int nbNodes;
    bool solved;
    int currentRound;
    unordered_map<int, vector<int>> contributions;
    unordered_set<int> contributionIds;

    void publishContribution(int round, int value);
    void publishDecision(int value);
    int genId();
    void cancel(int msgId);
    int getInitialValue();
    int getConsensusValue(const vector<int>& values);
    bool allEqual(const vector<int>& values, int target);
    void decide(int value);

public:
    ConsensusAlgorithm(int nodeId, int group, int nodesCount);
    void startSession(int initialRound, int initialValue);
    void startRound(int round);
    void receiveContribution(int msgId, int round, int value);
    void receiveDecision(int msgId, int value);
};

#endif
