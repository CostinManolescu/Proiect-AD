#include "ConsensusAlgorithm.h"
#include <algorithm> // Include the <algorithm> header

// Constructor implementation
ConsensusAlgorithm::ConsensusAlgorithm(int nodeId, int group, int nodesCount)
    : id(nodeId), groupId(group), nbNodes(nodesCount), solved(false), currentRound(0) {
}


void ConsensusAlgorithm::startSession(int initialRound, int initialValue) {
    currentRound = initialRound;
    contributions.clear();
    contributionIds.clear();
    solved = false;
    publishContribution(currentRound, initialValue);
}

void ConsensusAlgorithm::startRound(int round) {
    if (solved) return;

    currentRound = round;
    contributionIds.clear();
    publishContribution(currentRound, getInitialValue());
}

void ConsensusAlgorithm::receiveContribution(int msgId, int round, int value) {
    if (solved) return;

    if (round > currentRound) {
        cancel(msgId);
        return;
    }

    if (round < currentRound) {
        cancel(msgId);
        return;
    }

    contributions[round].push_back(value);
    contributionIds.insert(msgId);

    if (contributions[round].size() >= (2 * nbNodes / 3)) {
        int consensusValue = getConsensusValue(contributions[round]);
        if (allEqual(contributions[round], consensusValue)) {
            decide(consensusValue);
            startRound(currentRound + 1);
        }
    }
}

void ConsensusAlgorithm::receiveDecision(int msgId, int value) {
    if (solved) return;

    solved = true;
    publishDecision(value);
}

void ConsensusAlgorithm::publishContribution(int round, int value) {
    int msgId = genId();
    ContributionMessage *msg = new ContributionMessage();
    msg->setName("ContributionMessage");
    msg->round = round;
    msg->value = value;
    send(msg, "out"); // Send the message to other nodes
    // publish(msgId, groupId, id, ContributionMessage{round, value});
}

void ConsensusAlgorithm::publishDecision(int value) {
    int msgId = genId();
    DecisionMessage *msg = new DecisionMessage();
    msg->setName("DecisionMessage");
    msg->value = value;
    send(msg, "out"); // Send the message to other nodes
    // publish(msgId, groupId, id, DecisionMessage{value});
}

int ConsensusAlgorithm::genId() {
    static int messageId = 0;
    return messageId++;
}

void ConsensusAlgorithm::cancel(int msgId) {
    // cancel(msgId);
}

int ConsensusAlgorithm::getInitialValue() {
    // In a real implementation, this might involve some logic to determine the initial value
    return id;
}

int ConsensusAlgorithm::getConsensusValue(const vector<int>& values) {
    // In this simple example, just return the most frequent value
    unordered_map<int, int> countMap;
    for (int value : values) {
        countMap[value]++;
    }

    int maxCount = 0;
    int consensusValue = values[0];
    for (const auto& pair : countMap) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            consensusValue = pair.first;
        }
    }

    return consensusValue;
}

bool ConsensusAlgorithm::allEqual(const vector<int>& values, int target) {
    return all_of(values.begin(), values.end(), [target](int value) { return value == target; });
}

void ConsensusAlgorithm::decide(int value) {
    solved = true;
    publishDecision(value);
}
