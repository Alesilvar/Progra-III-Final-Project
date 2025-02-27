//
// Created by Alessandra on 27/02/2025.
//

#ifndef PROGRA_III_FINAL_PROJECT_TRIE_H
#define PROGRA_III_FINAL_PROJECT_TRIE_H

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <future>
#include <sstream>

using std::unordered_map, std::vector, std::string, std::tolower, std::isalnum, std::erase_if, std::future,
        std::launch, std::async, std::ranges::transform, std::ranges::sort, std::ranges::unique, std::istringstream;

// Estructura para representar un nodo en una estructura de datos Trie
struct Node {
    unordered_map<char, Node *> children; // Mapa de hijos: clave es el carácter, valor es el puntero al nodo hijo
    vector<int> movieIds; // Vector de ID de películas asociadas con este nodo

    // Destructor que se encarga de liberar la memoria de los nodos hijos
    ~Node();
};

class Trie {
private:
    Node *root;

    // Inserta recursivamente una palabra en el trie
    static void insertAux(Node *node, const string &word, int movieId, size_t index);

    // Busca recursivamente las películas asociadas a una palabra
    static void searchAux(Node *node, const string &word, vector<int> &results, size_t index);

public:
    Trie();
    ~Trie();

    // Inserta un texto asociado a un ID de película
    void insert(int movieId, const string &text) const;

    // Busca un texto y devuelve los IDs de películas asociadas
    [[nodiscard]] vector<int> search(const string &text) const;
};

#endif //PROGRA_III_FINAL_PROJECT_TRIE_H
