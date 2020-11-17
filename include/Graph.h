#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    Graph();
    Graph(const Graph& graph);
    ~Graph();
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    std::vector<std::vector<int>> getGraph() const;

private:
    std::vector<std::vector<int>> edges;
    std::vector<int> infected;

};

#endif