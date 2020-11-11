//
// Created by denis on 08/11/2020.
//

#include <iostream>
#include "../header/Graph.h"
using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) {
    this->edges=matrix;
    for (int i = 0; i < this->edges.size(); i++)
        infected.push_back(0);
}

void Graph::infectNode(int nodeInd) {
    infected[nodeInd] = 1;
}

bool Graph::isInfected(int nodeInd) {
    return infected[nodeInd] == 1;
}

Graph::Graph() {

}

std::vector<std::vector<int>> Graph::getGraph() {
    return edges;
}

