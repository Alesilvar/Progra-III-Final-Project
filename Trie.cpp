#include "trie.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <future>
#include <ranges>

using std::string, std::vector, std::istringstream, std::erase_if, std::ranges::transform,
        std::ranges::sort, std::ranges::unique, std::tolower, std::isalnum, std::future,
        std::shared_future, std::launch, std::async, std::make_unique;

Trie::Trie() : root(NodeFactory::createNode()) {}

void Trie::insertAux(Node *node, const string &word, int movieId, size_t index) {
    if (index == word.length()) {
        node->movieIds.push_back(movieId);
        return;
    }
    char c = word[index];
    if (!node->children.contains(c)) {
        node->children[c] = NodeFactory::createNode().release();
    }
    insertAux(node->children[c], word, movieId, index + 1);
}

void Trie::insert(int movieId, const string &text) const {
    istringstream iss(text);
    string word;
    while (iss >> word) {
        word = normalizeWord(word);
        if (!word.empty()) {
            insertAux(root.get(), word, movieId, 0);
        }
    }
}

void Trie::searchAux(Node *node, const string &word, vector<int> &results, size_t index) {
    if (index == word.length()) {
        results.insert(results.end(), node->movieIds.begin(), node->movieIds.end());
        return;
    }
    char c = word[index];
    if (node->children.contains(c)) {
        searchAux(node->children[c], word, results, index + 1);
    }
}

std::string Trie::normalizeWord(std::string word) {
    erase_if(word, [](char c) { return !isalnum(c); });
    transform(word, word.begin(), [](unsigned char c) { return tolower(c); });
    return word;
}

std::vector<int> Trie::search(const string &text) const {
    vector<int> results;
    vector<string> words;
    istringstream iss(text);
    string word;

    while (iss >> word) {
        word = normalizeWord(word);
        if (!word.empty()) {
            words.emplace_back(std::move(word));
        }
    }

    vector<shared_future<vector<int>>> futures;
    for (const auto &w : words) {
        futures.push_back(async(launch::async, [this, &w]() {
            vector<int> wordResults;
            searchAux(root.get(), w, wordResults, 0);
            return wordResults;
        }));
    }

    for (auto &f : futures) {
        auto res = f.get();
        results.insert(results.end(), std::make_move_iterator(res.begin()), std::make_move_iterator(res.end()));
    }

    sort(results);
    results.erase(unique(results).begin(), results.end());
    return results;
}
