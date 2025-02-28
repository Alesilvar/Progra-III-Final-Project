#ifndef PROGRA_III_FINAL_PROJECT_NODE_H
#define PROGRA_III_FINAL_PROJECT_NODE_H

#include <unordered_map>
#include <vector>
#include <memory>

struct Node {
    std::unordered_map<char, Node *> children;
    std::vector<int> movieIds;

    ~Node();
};

class NodeFactory {
public:
    static std::unique_ptr<Node> createNode();
};

#endif //PROGRA_III_FINAL_PROJECT_NODE_H
