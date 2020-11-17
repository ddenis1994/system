
#include <iostream>
#include "../header/Session.h"
#include "fstream"
#include "../lib/json.hpp"
#include "../include/Session.h"
#include "../include/Tree.h"
#include "../include/Agent.h"


using namespace std;

using json = nlohmann::json;

void Session::simulate() {
    Tree * a=Tree::createTree(*this,0);
    int v=a->traceTree();
    while (true)
    {
        bool cont = this->cycle();
        if (!cont)
            break;
    }
}
bool Session::cycle() {
    for (Agent* a : this->agents)
        a->act(*this);
    return !this->checkEnd();
}
bool Session::checkEnd() {
    return true;
    delete a;
}


void Session::addAgent(const Agent &agent) {
    this->agents.push_back((Agent *const) & agent);
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

void Session::enqueueInfected(int n) {
    this->infected.push(n);
}

int Session::dequeueInfected() {
    int result = this->infected.front();
    this->infected.pop();
    return result;
}

TreeType Session::getTreeType() const {
    return treeType;
}

Session::Session(const std::string &path) {
    json jsonData=extractFromJsonFilePath(path);
    setGraph(Graph(jsonData["graph"]));
    setTreeType(jsonData["tree"]);
    vector<pair<string ,int>> agentsVector = jsonData["agents"];
    for (auto item : agentsVector) {
        Agent *virus = Agent::createAgent(item);
        addAgent(*virus);
    }
}
Session::~Session()
{
    delete(&g);
    for (Agent* a : agents)
        delete(a);
    delete(&agents);
    delete(&infected);
}
Session::Session(const Session& session)
{
    g = Graph(session.g);
    treeType = session.treeType;
    agents = std::vector<Agent*>(session.agents);
    infected = std::queue<int>(session.infected);
    delete(&session.agents);
}

void Session::setTreeType(const std::string& type) {
    if (type=="R")
        treeType=Root;
    if(type=="M")
        treeType=MaxRank;
    if(type=="C")
        treeType=Cycle;
}

nlohmann::json Session::extractFromJsonFilePath(const string &jsonPath) {
    ifstream jsonFile(jsonPath);
    json jsonData;
    jsonFile >> jsonData;
    return jsonData;
}

Graph Session::getGraph() const {
    return g;
}


