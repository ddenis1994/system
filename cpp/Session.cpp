
#include <iostream>
#include "../header/Session.h"
#include "fstream"
#include "../header/Agent.h"
#include "../header/Tree.h"

using namespace std;

using json = nlohmann::json;

void Session::simulate() {
    Tree * a=Tree::createTree(*this,0);
    int v=a->traceTree();
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


