#include "MovieRepository.h"
#include <algorithm>

vector<string> MovieRepository::parseRow(const string &line) {
    vector<string> row;
    istringstream ss(line);
    string cell;
    bool insideQuote = false;

    while (ss.good()) {
        char c = ss.get();
        if (c == '"') {
            insideQuote = !insideQuote;
        } else if (c == ',' && !insideQuote) {
            row.emplace_back(std::move(cell));
            cell.clear();
        } else if (c != EOF) {
            cell += c;
        }
    }
    row.emplace_back(std::move(cell));
    return row;
}

MovieRepository &MovieRepository::getInstance() {
    static MovieRepository instance;
    return instance;
}

void MovieRepository::loadCSV(const string &path) {
    MovieBuilder builder;
    ifstream csv(path);
    string line;

    getline(csv, line);

    while (getline(csv, line)) {
        vector<string> cells = parseRow(line);

        builder.setId(cells[0])
                .setTitle(cells[1])
                .setPlot(cells[2])
                .setTags(cells[3]);

        trie.insert(builder.getId(), builder.getTitle());
        trie.insert(builder.getId(), builder.getPlot());

        for (const auto &tag : builder.getTags()) {
            tagMap[tag].insert(builder.getId());
        }

        movies.emplace(builder.getId(), builder.build());
        builder.reset();
    }
}

vector<Movie> MovieRepository::searchByText(const string &text) {
    const vector<int> ids = trie.search(text);
    vector<Movie> result;
    result.reserve(ids.size());
    for (const int &id : ids) {
        result.push_back(movies.at(id));
    }
    return result;
}

vector<Movie> MovieRepository::searchByTag(const string &tag) {
    vector<Movie> result;
    if (tagMap.contains(tag)) {
        result.reserve(tagMap[tag].size());
        for (const int &id : tagMap[tag]) {
            result.push_back(movies.at(id));
        }
    }
    return result;
}

vector<Movie> MovieRepository::searchByIds(const unordered_set<int> &ids) {
    vector<Movie> result;
    result.reserve(ids.size());
    for (const int &id : ids) {
        result.push_back(movies.at(id));
    }
    return result;
}

vector<Movie> MovieRepository::getRecommendations(const unordered_map<string, double> &tagPreferences) {
    unordered_map<int, double> movieWeights;

    for (const auto &[tag, preference] : tagPreferences) {
        if (tagMap.contains(tag)) {
            for (const int &id : tagMap[tag]) {
                movieWeights[id] += preference / movies.at(id).getTags().size();
            }
        }
    }

    vector<pair<int, double>> sortedWeights(movieWeights.begin(), movieWeights.end());
    std::sort(sortedWeights.begin(), sortedWeights.end(),
              [](const auto &a, const auto &b) { return a.second > b.second; });

    vector<Movie> result;
    result.reserve(sortedWeights.size());
    for (const auto &[id, weight] : sortedWeights) {
        result.push_back(movies.at(id));
    }

    return result;
}
