//
// Created by Alessandra on 27/02/2025.
//

#include "Trie.h"

// Destructor que libera la memoria de los nodos hijos
Node::~Node() {
    for (auto &pair : children) { // Itera sobre cada par clave-valor en el mapa de hijos
        delete pair.second; // Elimina el nodo hijo apuntado por el puntero
    }
}

// Constructor
Trie::Trie() : root(new Node()) {}

// Destructor
Trie::~Trie() {
    delete root;
}

// Inserta recursivamente una palabra en el trie
void Trie::insertAux(Node *node, const string &word, int movieId, size_t index) {
    if (index == word.length()) {
        node->movieIds.push_back(movieId);
        return;
    }
    const char c = word[index];
    if (!node->children.contains(c)) {
        node->children[c] = new Node();
    }
    insertAux(node->children[c], word, movieId, index + 1);
}

// Busca recursivamente las películas asociadas a una palabra
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

// Inserta un texto asociado a un ID de película, procesando cada palabra del texto
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

// Busca un texto y devuelve los IDs de películas asociadas
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
