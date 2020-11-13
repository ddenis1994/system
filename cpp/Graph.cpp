//
// Created by denis on 08/11/2020.
//

#include <iostream>
#include "../header/Graph.h"
using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) {
    this->edges=matrix;


}

void Graph::infectNode(int nodeInd) {

}

bool Graph::isInfected(int nodeInd) {
    return false;
}

Graph::Graph() {

}

std::vector<std::vector<int>> Graph::getGraph() const {
    return edges;
}

