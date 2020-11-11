//
// Created by denis on 08/11/2020.
//

#include <iostream>
#include "../header/Agent.h"
#include "../header/Tree.h"

Agent::Agent() {

}

Agent *Agent::createAgent(std::pair<std::string, int> & agent) {
    std::cout<<agent.first<<std::endl;
    if (agent.first == "V") return new Virus(agent.second);
    else if (agent.first == "C") return new ContactTracer();
    return nullptr;
}


ContactTracer::ContactTracer() {

}

void ContactTracer::act(Session &session) {
    int node = session.dequeueInfected();
    Tree* t = Tree::createTree(session,node);
    int dis = t->traceTree();
}



void Virus::act(Session &session) {
    session.enqueueInfected(nodeInd);
    Graph g = session.getGraph();
    std::vector<int> connected = g.getGraph()[nodeInd];
    for (int i = 0; i < connected.size(); i++)
    {
        if (connected[i] == 0)
            continue;
        if (g.isInfected(i))
            continue;
        g.infectNode(i);
        createAgent(*new std::pair<std::string, int> ("V",i));
    }
}

Virus::Virus(int nodeInd) : nodeInd(nodeInd) 
{

}
