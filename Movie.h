
#ifndef PROGRA_III_FINAL_PROJECT_MOVIE_H
#define PROGRA_III_FINAL_PROJECT_MOVIE_H

#include <string>
#include <unordered_set>

using std::string, std::unordered_set;

// Clase que representa una película
class Movie {
    int id;
    string title;
    string plot;
    unordered_set<string> tags;

public:
    Movie();
    Movie(int id, string title, string plot, unordered_set<string> tags);
    ~Movie() = default;

    const int &getId() const;
    const string &getTitle() const;
    const string &getPlot() const;
    const unordered_set<string> &getTags() const;
};

#endif //PROGRA_III_FINAL_PROJECT_MOVIE_H
