#ifndef PROGRA_III_FINAL_PROJECT_MOVIEREPOSITORY_H
#define PROGRA_III_FINAL_PROJECT_MOVIEREPOSITORY_H

#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Movie.h"
#include "MovieBuilder.h"
#include "Trie.h"

using std::unordered_map, std::string, std::vector, std::ifstream, std::istringstream, std::stringstream, std::pair;

class MovieRepository {
    unordered_map<int, Movie> movies;
    unordered_map<string, unordered_set<int>> tagMap;
    Trie trie;

    MovieRepository() = default;
    ~MovieRepository() = default;

    static vector<string> parseRow(const string &line);

public:
    static MovieRepository &getInstance();

    void loadCSV(const string &path);
    vector<Movie> searchByText(const string &text);
    vector<Movie> searchByTag(const string &tag);
    vector<Movie> searchByIds(const unordered_set<int> &ids);
    vector<Movie> getRecommendations(const unordered_map<string, double> &tagPreferences);
};

#endif //PROGRA_III_FINAL_PROJECT_MOVIEREPOSITORY_H
