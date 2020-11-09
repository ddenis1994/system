#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Graph.h"
#include "Session.h"

class Session;

class Tree{
public:
    Tree(int rootLabel);
    void addChild(const Tree& child);
    static Tree* createTree(const Session& session, int rootLabel);
    static Tree *makeBfsTree(Graph graph, Tree *root, TreeType type);
    virtual int traceTree()=0;
private:
    int node{};
    std::vector<Tree*> children;

    static Tree *makeTreeType(TreeType type, int node);
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel1, int rootLabel, int currCycle);
    virtual int traceTree();
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
};

#endif