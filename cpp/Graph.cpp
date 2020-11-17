//
// Created by denis on 08/11/2020.
//

#include <iostream>
#include "../include/Graph.h"
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
Graph::Graph(const Graph &graph)
{
    edges = graph.edges;
    infected = graph.infected;
}
Graph::~Graph() {
    for (std::vector<int> v : edges)
    {
        delete(&v);
    }
    delete(&edges);
    delete(&infected);
}

std::vector<std::vector<int>> Graph::getGraph() const {
    return edges;
}

