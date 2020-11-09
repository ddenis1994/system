//
// Created by denis on 08/11/2020.
//

#include <iostream>
#include "../header/Agent.h"

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

}



void Virus::act(Session &session) {

}

Virus::Virus(int nodeInd) : nodeInd(nodeInd) {

}
