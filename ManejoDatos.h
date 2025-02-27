//
// Created by Alessandra on 27/02/2025.
//

#ifndef PROGRA_III_FINAL_PROJECT_MANEJODATOS_H
#define PROGRA_III_FINAL_PROJECT_MANEJODATOS_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include "Movie.h"
#include "MovieBuilder.h"
#include "Trie.h"

class ManejoDatos {
private:
    std::unordered_map<int, Movie> movies;
    std::unordered_map<std::string, std::unordered_set<int>> tagMap; // Maps tags to movie IDs
    Trie trie;

    ManejoDatos(); // Private constructor for Singleton pattern

    ~ManejoDatos() = default;

    static std::vector<std::string> parseRow(const std::string &line);

public:
    static ManejoDatos &getInstance();

    void loadCSV(const std::string &path);
    std::vector<Movie> searchByText(const std::string &text);
    std::vector<Movie> searchByTag(const std::string &tag);
    std::vector<Movie> searchByIds(const std::unordered_set<int> &ids);
    std::vector<Movie> getRecommendations(const std::unordered_map<std::string, double> &tagPreferences);
};

#endif //PROGRA_III_FINAL_PROJECT_MANEJODATOS_H
