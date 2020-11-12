#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Graph.h"
#include "Session.h"

class Session;

class Tree{
public:
    Tree(int rootLabel);
    void addChild(Tree& child);
    Tree (const Tree & oldTree);
    static Tree* createTree(const Session& session, int rootLabel);
    Tree * copy();
    virtual ~Tree();
    int getNode() const;
    virtual int traceTree()=0;
    std::vector<Tree *> & getChildren() ;
    static TreeType type;

private:

    std::vector<Tree*> children;
    int node{};
    static Tree *makeBfsTree(Graph graph, Tree *root);
    static Tree *makeTreeByType( int node);
};

class CycleTree: public Tree{
public:
    CycleTree( int rootLabel, int currCycle);
    virtual int traceTree();
private:
    CycleTree & innerTraversTree(CycleTree & root,int c);
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();

private:
     static const MaxRankTree & searchForMaxRank(  MaxRankTree & node) ;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();


};

class Max{
    int children;
    int node;
};

#endif