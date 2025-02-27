//
// Created by Alessandra on 27/02/2025.
//

#ifndef PROGRA_III_FINAL_PROJECT_MOVIE_H
#define PROGRA_III_FINAL_PROJECT_MOVIE_H

#include <string>
#include <unordered_set>

using std::string, std::unordered_set;

class Movie {
private:
    int id;
    string title;
    string plot;
    unordered_set<string> tags;

public:
    // Constructor por defecto
    Movie();

    // Constructor con parámetros
    Movie(int id, string title, string plot, unordered_set<string> tags);

    // Destructor
    ~Movie() = default;

    // Getters
    const int &getId() const;
    const string &getTitle() const;
    const string &getPlot() const;
    const unordered_set<string> &getTags() const;
};


#endif //PROGRA_III_FINAL_PROJECT_MOVIE_H
