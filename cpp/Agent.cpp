//
// Created by denis on 08/11/2020.
//

#include <iostream>
#include "../include/Agent.h"


class Tree;

class Graph;

Agent::Agent() {

}

Agent *Agent::createAgent(std::pair<std::string, int> &agent) {
    if (agent.first == "V") return new Virus(agent.second);
    else if (agent.first == "C") return new ContactTracer();
    return nullptr;
}
Agent * Virus::copy() {
    return new Virus(nodeInd);
}


bool Virus::testIfAgent(int node) const {
    return node==nodeInd;
}


ContactTracer::ContactTracer() {

}

void ContactTracer::act(Session &session) {
    int node = session.getLastInfected();
    Tree *t = Tree::createTree(session, node);
    int dis = t->traceTree();
    disconnectNode(session,dis);

}

void ContactTracer::disconnectNode(Session & session, const int nodeId) {
    Graph graph=session.getGraph();
    for (int i = 0; i < graph.getGraph().size(); i++) {
        graph.getGraph()[i][nodeId]=0;
        graph.getGraph()[nodeId][i]=0;
    }
}

Agent *ContactTracer::copy() {
    return new ContactTracer();
}


void Virus::act(Session &session) {
//    session.enqueueInfected(nodeInd);
//    Graph g = session.getGraph();
//    std::vector<int> connected = g.getGraph()[nodeInd];
//    for (int i = 0; i < connected.size(); i++)
//    {
//        if (connected[i] == 0)
//            continue;
//        if (g.isInfected(i))
//            continue;
//        g.infectNode(i);
//        createAgent(*new std::pair<std::string, int> ("V",i));
//    }
    if (!session.checkIfNodeInfected(nodeInd)) session.enqueueInfected(nodeInd);
    auto connected = session.getGraph().getGraph()[nodeInd];
    for (int &connectedNode : connected) {
        if (connectedNode == 1)
            if (!session.checkIfNodeAgent(connectedNode)) {
                Agent *v = new Virus(connectedNode);
                session.addAgent(*v);
                break;
            }
    }

}

Virus::Virus(int nodeInd) : nodeInd(nodeInd) {

}


