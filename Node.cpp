#include "node.h"

Node::~Node() {
    for (auto &pair : children) {
        delete pair.second;
    }
}

std::unique_ptr<Node> NodeFactory::createNode() {
    return std::make_unique<Node>();
}