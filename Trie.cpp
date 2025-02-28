#include "Trie.h"

void Trie::insertAux(Node *node, const string &word, int movieId, size_t index) {
    if (index == word.length()) {
        node->movieIds.push_back(movieId);
        return;
    }
    const char c = word[index];
    if (!node->children.contains(c)) {
        node->children[c] = NodeFactory::createNode();
    }
    insertAux(node->children[c], word, movieId, index + 1);
}

void Trie::searchAux(Node *node, const string &word, vector<int> &results, size_t index) {
    if (index == word.length()) {
        results.insert(results.end(), node->movieIds.begin(), node->movieIds.end());
        return;
    }
    const char c = word[index];
    if (node->children.contains(c)) {
        searchAux(node->children[c], word, results, index + 1);
    }
}

Trie::Trie() : root(NodeFactory::createNode()) {}

Trie::~Trie() {
    delete root;
}

void Trie::insert(int movieId, const string &text) const {
    istringstream iss(text);
    string word;
    while (iss >> word) {
        erase_if(word, [](const char c) { return !isalnum(c); });
        transform(word, word.begin(), [](const unsigned char c) { return tolower(c); });
        if (!word.empty()) {
            insertAux(root, word, movieId, 0);
        }
    }
}

vector<int> Trie::search(const string &text) const {
    vector<int> results;
    vector<string> words;
    istringstream iss(text);
    string word;

    while (iss >> word) {
        erase_if(word, [](const char c) { return !isalnum(c); });
        transform(word, word.begin(), [](const unsigned char c) { return tolower(c); });
        if (!word.empty()) {
            words.emplace_back(word);
        }
    }

    vector<future<vector<int>>> futures;
    for (const auto &w: words) {
        futures.push_back(async(launch::async, [this, &w]() {
            vector<int> wordResults;
            searchAux(root, w, wordResults, 0);
            return wordResults;
        }));
    }

    for (auto &f: futures) {
        const auto &res = f.get();
        results.insert(results.end(), res.begin(), res.end());
    }

    sort(results);
    results.erase(unique(results).begin(), results.end());
    return results;
}
