#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"
#include "../lib/json.hpp"

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    Session(const std::string& path);
    Session(const Session& session);
    ~Session();
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    Graph getGraph() const;
    void setTreeType(const std::string& type);
    static nlohmann::json extractFromJsonFilePath(const std::string & jsonPath);
    void enqueueInfected(int);
    int getLastInfected()const;
    bool checkIfNodeInfected(int node) const;
    bool checkIfNodeAgent(int node) const ;
    TreeType getTreeType() const;
    std::queue<int> & getInfected();


private:
    Graph g ;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infected;
    bool cycle();
    bool checkEnd();
    std::vector<Agent*> copyAgents() const;

};

#endif