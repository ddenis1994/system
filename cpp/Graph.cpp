//
// Created by denis on 08/11/2020.
//

#include <iostream>
#include <utility>
#include "../include/Graph.h"
using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) {
    this->edges=std::move(matrix);
}

void Graph::infectNode(int nodeInd) {
    infected.push_back(nodeInd);
}

bool Graph::isInfected(int nodeInd) const{
    for(auto node:infected)
        if ( node == nodeInd) return true;
    return false;
}

Graph::Graph() {

}
Graph::Graph(const Graph &graph)
{
    edges = graph.edges;
    infected = graph.infected;
}
Graph::~Graph() {
    //no need fo dtor all is in the heap
}

std::vector<std::vector<int>> & Graph::getGraph()  {
    return edges;
}

void Graph::disconnectNodeFromAll(const int node) {
    for (int i = 0; i < edges.size(); i++) {
        edges[i][node] = 0;
        edges[node][i] = 0;
    }
}

bool Graph::isAllInfected() {
    for (auto node:infected){
        if (node==0) return false;
    }
    return true;
}

const vector<int> &Graph::getInfected() const {
    return infected;
}

