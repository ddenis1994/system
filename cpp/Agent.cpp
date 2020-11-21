#include <iostream>
#include "../include/Agent.h"


class Tree;

class Graph;

Agent::Agent() = default;

Agent *Agent::createAgent(std::pair<std::string, int> &agent) {
    if (agent.first == "V") return new Virus(agent.second);
    else if (agent.first == "C") return new ContactTracer();
    return nullptr;
}

Agent *Virus::copy() {
    return new Virus(nodeInd);
}


bool Virus::testIfAgent(int node) const {
    return node == nodeInd;
}


ContactTracer::ContactTracer() = default;

void ContactTracer::act(Session &session) {
    int node = session.dequeueInfected();
    Tree *t = Tree::createTree(session, node);
    int dis = t->traceTree();
    session.disconnectNode(dis);
    delete t;

}

Agent *ContactTracer::copy() {
    return new ContactTracer();
}


void Virus::act(Session &session) {
    if (!session.isInfected(nodeInd)) {
        session.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    auto connected = session.getNeighboursOfNode(nodeInd);
    int nodeToInfect=-1;
    for (int  connectedNode : connected) {
        nodeToInfect++;
        if (connectedNode == 1)
            if (!session.checkIfNodeAgent(nodeToInfect)) {
                Agent *v = new Virus(nodeToInfect);
                session.addAgent(*v);
                return;
            }
    }
}

Virus::Virus(int nodeInd) : nodeInd(nodeInd) {

}

const int Virus::getNodeInd() const {
    return nodeInd;
}


