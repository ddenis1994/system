#include <iostream>
#include "../include/Tree.h"

using namespace std;

TreeType Tree::type;

Tree::Tree(int rootLabel) : node(rootLabel) {

}

void Tree::addChild(Tree &child) {
    children.push_back(&child);
}


Tree *Tree::createTree(const Session &session, int rootLabel) {
    Tree::type = session.getTreeType();
    const Graph & graph = session.getGraph();
    Tree *root = makeTreeByType(rootLabel);
    makeBfsTree(graph, root);
    return root;
}


void Tree::makeBfsTree(Graph graph, Tree *root) {
    auto numVertices = (graph.getGraph().size()) - 1;
    bool *visited;
    visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;
    vector<Tree *> queue = std::vector<Tree *>();
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
                    Tree *child = makeTreeByType(i);
                    currVertex->addChild(*child);
                    queue.push_back(child);
                }
            }
        }
    }
    delete[] visited;
}

Tree *Tree::makeTreeByType(int node) {
    Tree *root;
    switch (type) {
        case Root:
            root = new RootTree(node);
            break;
        case Cycle:
            root = new CycleTree(node, 0);
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

vector<Tree *> Tree::getChildren() const {
    return children;
}

//copy constructor
Tree::Tree(const Tree &oldTree) {
    this->node = oldTree.node;
    if (!this->getChildren().empty()) {
        auto nodeChildren = this->getChildren();
        for (auto i = nodeChildren.begin(); i < nodeChildren.end(); ++i) {
            Tree *cloneChild = (*i)->copy();
            this->children.push_back(cloneChild);
        }
    }
}

Tree::~Tree() {
    if (!this->getChildren().empty()) {
        int numOfChildren = this->getChildren().size();
        for (int i = 0; i < numOfChildren; i++) {
            delete this->getChildren()[i];
        }
    }
}

Tree *Tree::copy() {
    Tree *newTree = makeTreeByType(this->getNode());
    newTree->node = this->node;
    const auto oldTreeChildren = this->children;
    if (!oldTreeChildren.empty()) {
        for (auto oldTreeChild = oldTreeChildren.begin(); oldTreeChild < oldTreeChildren.end(); ++oldTreeChild) {
            Tree *cloneChild = (*oldTreeChild)->copy();
            newTree->children.push_back(cloneChild);
        }
    }
    return newTree;
}

int CycleTree::traceTree() {

    return innerTraversTree(*this, currCycle++)->getNode();
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {

}

const CycleTree *CycleTree::innerTraversTree(const Tree &root, int c) {
    //in case last
    if (c < 1)
        return dynamic_cast<const CycleTree *>(&root);
    //return non end;
    if (root.getChildren().empty())
        return new CycleTree(-1, c - 1);
    else {
        auto oldTreeChildren = root.getChildren();
        for (auto oldTreeChild = oldTreeChildren.begin(); oldTreeChild < oldTreeChildren.end(); ++oldTreeChild) {
            const Tree *child = (*oldTreeChild);
            auto childForTest = innerTraversTree(*child, c - 1);
            //found the end
            if (childForTest->getNode() != -1)
                return childForTest;
            delete &childForTest;
            c = childForTest->currCycle;
        }
    }
    return new CycleTree(-1, c);
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {

}

int MaxRankTree::traceTree() {
    return searchForMaxRank()->getNode();
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {

}


const MaxRankTree *MaxRankTree::searchForMaxRank() const {
    if (this->getChildren().empty())
        return this;
    auto children = this->getChildren();
    int maxChildCount = getChildren().size();
    const MaxRankTree *maxChild = this;
    for (auto child = children.begin(); child < children.end(); ++child) {
        auto castedMaxRank = dynamic_cast<MaxRankTree *>(*child);
        auto childToTest = castedMaxRank->searchForMaxRank();
        if (childToTest->getChildren().size() > maxChildCount) {
            maxChildCount = childToTest->getChildren().size();
            maxChild = childToTest;
        }
    }
    return maxChild;

}



int RootTree::traceTree() {
    return this->getNode();
}
