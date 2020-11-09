//
// Created by denis on 08/11/2020.
//

#include <iostream>
#include "../header/Tree.h"
#include "../header/Session.h"

Tree::Tree(int rootLabel) : node(rootLabel) {

}

void Tree::addChild(const Tree &child) {

    children.push_back((Tree *const) &child);
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    Graph graph = session.getGraph();
    Tree *root = makeTreeByType(type, rootLabel);
    makeBfsTree(graph, root, type);
    return root;
}


Tree *Tree::makeBfsTree(Graph graph, Tree *root, TreeType type) {
    int numVertices = (graph.getGraph().size()) - 1;
    bool *visited;
    visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;
    auto queue = std::vector<Tree *>();
    visited[root->node] = true;
    queue.push_back(root);

    while (!queue.empty()) {
        auto currVertex = queue.front();
        queue.erase(queue.begin());
        auto edges = graph.getGraph()[currVertex->node];
        for (int i = 0; i <= numVertices; i++) {
            if (edges[i] == 1) {
                if (!visited[i]) {
                    visited[i] = true;
                    Tree *child = makeTreeByType(type, i);
                    currVertex->addChild(*child);
                    queue.push_back(child);
                }
            }
        }
    }


    return nullptr;
}

Tree *Tree::makeTreeByType(TreeType type, int node) {
    Tree *root;
    switch (type) {
        case Root:
            root = new RootTree(node);
            break;
        case Cycle:
            root = new CycleTree(0, node, 0);
            break;
        case MaxRank:
            root = new MaxRankTree(node);
            break;
        default:
            return nullptr;

    }
    return root;
}

int Tree::getNode() const {
    return node;
}

const std::vector<Tree *> &Tree::getChildren() const {
    return children;
}


int CycleTree::traceTree() {
    return 0;
}

CycleTree::CycleTree(int rootLabel1, int rootLabel, int currCycle) : Tree(rootLabel1) {

}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {

}

int MaxRankTree::traceTree() {
    return searchForMaxRank(this, this)->getNode();
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {

}


MaxRankTree *MaxRankTree::searchForMaxRank( MaxRankTree *node, MaxRankTree *maxNode) {
    if (node->getChildren().empty())
        return node;
    std::vector<MaxRankTree *>children = (const std::vector<MaxRankTree *, std::allocator<MaxRankTree *>> &) node->getChildren();
    const auto childCount = children.size() - 1;
    for (int i = 0; i <= childCount; i++) {
        MaxRankTree * child = searchForMaxRank(children[i], maxNode);
        if (child->getChildren().size() > node->getChildren().size())
            maxNode = child;
        else
            maxNode=node;
    }
    return maxNode;
}

int RootTree::traceTree() {
    return this->getNode();
}
