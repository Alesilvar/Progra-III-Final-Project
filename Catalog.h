#ifndef PROGRA_III_FINAL_PROJECT_CATALOG_H
#define PROGRA_III_FINAL_PROJECT_CATALOG_H

#include <unordered_set>
#include <unordered_map>
#include <string>
#include "Movie.h"

using std::unordered_set, std::unordered_map, std::string;

class Catalog {
private:
    unordered_set<int> watchLater;
    unordered_set<int> likes;
    unordered_map<string, double> tagPreferences;

    Catalog() = default;
    ~Catalog() = default;

public:
    static Catalog &getInstance();

    void addToWatchLater(const Movie &movie);
    void addToLikes(const Movie &movie);

    const unordered_set<int> &getWatchLater() const;
    const unordered_set<int> &getLikes() const;
    const unordered_map<string, double> &getTagPreferences() const;
};

#endif //PROGRA_III_FINAL_PROJECT_CATALOG_H
