#ifndef PROGRA_III_FINAL_PROJECT_TRIE_H
#define PROGRA_III_FINAL_PROJECT_TRIE_H

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <future>
#include <sstream>
#include "Node.h"

using std::unordered_map, std::vector, std::string, std::tolower, std::isalnum, std::erase_if, std::future,
        std::launch, std::async, std::ranges::transform, std::ranges::sort, std::ranges::unique, std::istringstream;

class Trie {
private:
    Node *root;

    static void insertAux(Node *node, const string &word, int movieId, size_t index);
    static void searchAux(Node *node, const string &word, vector<int> &results, size_t index);

public:
    Trie();
    ~Trie();

    void insert(int movieId, const string &text) const;
    [[nodiscard]] vector<int> search(const string &text) const;
};

#endif //PROGRA_III_FINAL_PROJECT_TRIE_H
