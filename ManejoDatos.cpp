//
// Created by Alessandra on 27/02/2025.
//
#include "ManejoDatos.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using std::unordered_map, std::unordered_set, std::string, std::vector, std::ifstream,
        std::istringstream, std::stringstream, std::pair, std::stoi;

// Private Constructor for Singleton pattern
ManejoDatos::ManejoDatos() = default;

// Parses a CSV row and returns a vector of strings
std::vector<std::string> ManejoDatos::parseRow(const string &line) {
    vector<string> row;
    stringstream ss(line);
    bool insideQuote = false;
    string cell;

    for (const auto &c: line) {
        if (c == '"') {
            insideQuote = !insideQuote;
        } else if (c == ',' && !insideQuote) {
            row.emplace_back(std::move(cell));
            cell.clear();
        } else {
            cell += c;
        }
    }
    row.emplace_back(std::move(cell));

    return row;
}

// Returns the singleton instance of the database
ManejoDatos &ManejoDatos::getInstance() {
    static ManejoDatos instance;
    return instance;
}

// Loads movies from a CSV file
void ManejoDatos::loadCSV(const string &path) {
    MovieBuilder builder;
    ifstream csv(path);
    string line;

    // Skip the header
    getline(csv, line);
    line.clear();

    while (getline(csv, line)) {
        vector<string> cells = parseRow(line);

        builder.setId(cells[0])
                .setTitle(cells[1])
                .setPlot(cells[2])
                .setTags(cells[3]);

        trie.insert(builder.getId(), builder.getTitle());
        trie.insert(builder.getId(), builder.getPlot());

        for (const auto &tag: builder.getTags()) {
            tagMap[tag].insert(builder.getId());
        }

        movies.emplace(builder.getId(), std::move(builder.build()));
        builder.reset();
    }
    csv.close();
}

// Searches movies by text
vector<Movie> ManejoDatos::searchByText(const string &text) {
    const vector<int> ids = trie.search(text);
    vector<Movie> result;
    for (const int &id: ids) {
        result.emplace_back(movies[id]);
    }
    return result;
}

// Searches movies by tag
vector<Movie> ManejoDatos::searchByTag(const string &tag) {
    vector<Movie> result;
    if (tagMap.contains(tag)) {
        for (const int &id: tagMap[tag]) {
            result.emplace_back(movies[id]);
        }
    }
    return result;
}

// Searches movies by a set of IDs
vector<Movie> ManejoDatos::searchByIds(const unordered_set<int> &ids) {
    vector<Movie> result;
    for (const int &id: ids) {
        result.emplace_back(movies[id]);
    }
    return result;
}

// Gets movie recommendations based on tag preferences
vector<Movie> ManejoDatos::getRecommendations(const unordered_map<string, double> &tagPreferences) {
    unordered_map<int, double> movieWeights;

    // Iterate over tag preferences
    for (const auto &[tag, preference]: tagPreferences) {
        if (tagMap.contains(tag)) {
            for (const int &id: tagMap[tag]) {
                movieWeights[id] += preference / movies[id].getTags().size();
            }
        }
    }

    // Convert weights to a vector for sorting
    vector<pair<int, double>> sortedWeights(movieWeights.begin(), movieWeights.end());

    // Sort by weight (descending)
    std::sort(sortedWeights.begin(), sortedWeights.end(), [](const pair<int, double> &a, const pair<int, double> &b) {
        return a.second > b.second;
    });

    vector<Movie> result;

    // Add movies to the result vector
    for (const auto &[id, weight]: sortedWeights) {
        result.emplace_back(movies[id]);
    }

    return result;
}
