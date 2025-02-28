#ifndef PROGRA_III_FINAL_PROJECT_TRIE_H
#define PROGRA_III_FINAL_PROJECT_TRIE_H

#include "node.h"
#include <string>
#include <vector>
#include <memory>

class Trie {
private:
    std::unique_ptr<Node> root;

    static void insertAux(Node *node, const std::string &word, int movieId, size_t index);
    static void searchAux(Node *node, const std::string &word, std::vector<int> &results, size_t index);
    static std::string normalizeWord(std::string word);

public:
    Trie();
    void insert(int movieId, const std::string &text) const;
    [[nodiscard]] std::vector<int> search(const std::string &text) const;
};

#endif //PROGRA_III_FINAL_PROJECT_TRIE_H
