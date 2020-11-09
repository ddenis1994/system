//
// Created by denis on 08/11/2020.
//

#include <iostream>
#include "../header/Session.h"
#include "fstream"
#include "../lib/json.hpp"
#include "../header/Agent.h"

using namespace std;

using json = nlohmann::json;

void Session::simulate() {

}


void Session::addAgent(const Agent &agent) {
    this->agents.push_back((Agent *const) & agent);
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

void Session::enqueueInfected(int) {

}

int Session::dequeueInfected() {
    return 0;
}

TreeType Session::getTreeType() const {
    return Cycle;
}

Session::Session(const std::string &path) {
    ifstream jsonFile(path);
    json jsonData;
    jsonFile >> jsonData;
    setGraph(Graph(jsonData["graph"]));
    vector<pair<string ,int>> agentsVector = jsonData["agents"];
    for (auto item : agentsVector) {
        Agent *virus = Agent::createAgent(item);
        addAgent(*virus);
    }


}

