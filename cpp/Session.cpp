
#include "fstream"
#include "../lib/json.hpp"
#include "../include/Session.h"
#include "../include/Tree.h"
#include "../include/Agent.h"


using namespace std;

using json = nlohmann::json;

void Session::simulate() {
    while (true) {
        bool cont = this->cycle();
        if (!cont)
            break;
    }
}

bool Session::cycle() {
    auto test = copyAgents();
    for (Agent *a : test)
        a->act(*this);
    for (Agent *a : test)
        delete a;
    return this->checkEnd();
}

bool Session::checkEnd() {

    return g.isAllInfected() || virusStoped();
}


void Session::addAgent(const Agent &agent) {
    this->agents.push_back((Agent *const) &agent);
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

void Session::enqueueInfected(int n) {
    infected.push(n);
}


TreeType Session::getTreeType() const {
    return treeType;
}

Session::Session(const std::string &path) {
    json jsonData = extractFromJsonFilePath(path);
    setGraph(Graph(jsonData["graph"]));
    setTreeType(jsonData["tree"]);
    vector<pair<string, int>> agentsVector = jsonData["agents"];
    for (auto item : agentsVector) {
        Agent *virus = Agent::createAgent(item);
        addAgent(*virus);
    }
}

Session::~Session() {
    delete (&g);
    for (Agent *a : agents)
        delete (a);
    delete (&agents);
    delete (&infected);
}

Session::Session(const Session &session) {
    g = Graph(session.g);
    treeType = session.treeType;
    agents = std::vector<Agent *>(session.agents);
    infected = std::queue<int>(session.infected);
    delete (&session.agents);
}

void Session::setTreeType(const std::string &type) {
    if (type == "R")
        treeType = Root;
    if (type == "M")
        treeType = MaxRank;
    if (type == "C")
        treeType = Cycle;
}

nlohmann::json Session::extractFromJsonFilePath(const string &jsonPath) {
    ifstream jsonFile(jsonPath);
    json jsonData;
    jsonFile >> jsonData;
    return jsonData;
}

const Graph & Session::getGraph() const {
    return g;
}


bool Session::checkIfNodeAgent(int node) const {
    for (auto &agent:agents) {
        auto *d = dynamic_cast<Virus *>(agent);
        if (d && d->testIfAgent(node)) return true;
    }
    return false;
}

std::vector<Agent *> Session::copyAgents() const {
    auto copy = std::vector<Agent *>();
    for (Agent *a : this->agents)
        copy.push_back(a->copy());
    return copy;
}

int Session::dequeueInfected() {
    auto virus=infected.front();
    infected.pop();
    return virus;
}

bool Session::isInfected(const int nodeInd) const {
    return g.isInfected(nodeInd);
}

void Session::infectNode(const int nodeInd) {
    g.infectNode(nodeInd);
}

void Session::disconnectNode(const int nodeId) {
    g.disconnectNodeFromAll(nodeId);
}

vector<int> Session::getNeighboursOfNode(const int i) {
    return g.getGraph()[i];
}

bool Session::virusStoped() {
    //TODO finish the check if virus can infect another node
    return false;
}


