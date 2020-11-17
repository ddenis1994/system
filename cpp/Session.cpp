
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
    return !this->checkEnd();
}

bool Session::checkEnd() {
    return true;
}


void Session::addAgent(const Agent &agent) {
    this->agents.push_back((Agent *const) &agent);
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

void Session::enqueueInfected(int n) {
    this->infected.push(n);
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

Graph Session::getGraph() const {
    return g;
}

std::queue<int> &Session::getInfected() {
    return this->infected;
}

bool Session::checkIfNodeInfected(int node) const {
    std::queue<int> copy = std::queue<int>(infected);
    while (!copy.empty()) {
        int infectedNode = copy.front();
        if (infectedNode == node) return true;
        copy.pop();
    }
    return false;
}

int Session::getLastInfected() const {
    return infected.front();
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


