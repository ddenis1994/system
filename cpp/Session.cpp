//
// Created by denis on 08/11/2020.
//

#include <iostream>
#include "../header/Session.h"
#include "fstream"
#include "../lib/json.hpp"
using namespace std;

using json = nlohmann::json;

void Session::simulate() {

}



void Session::addAgent(const Agent &agent) {

}

void Session::setGraph(const Graph &graph) {

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
    ifstream x (path);
    json j;
    x >> j;
    g=Graph(j["graph"]);
}
