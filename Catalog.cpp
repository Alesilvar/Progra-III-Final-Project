#include "Catalog.h"
#include <iostream>

using std::cout;

Catalog &Catalog::getInstance() {
    static Catalog instance;
    return instance;
}

void Catalog::addToWatchLater(const Movie &movie) {
    watchLater.emplace(movie.getId());
    cout << "Added '" << movie.getTitle() << "' to watch later\n";
}

void Catalog::addToLikes(const Movie &movie) {
    likes.emplace(movie.getId());
    for (const auto &tag: movie.getTags()) {
        tagPreferences[tag]++;
    }
    cout << "Added '" << movie.getTitle() << "' to likes\n";
}

const unordered_set<int> &Catalog::getWatchLater() const {
    return watchLater;
}

const unordered_set<int> &Catalog::getLikes() const {
    return likes;
}

const unordered_map<string, double> &Catalog::getTagPreferences() const {
    return tagPreferences;
}
