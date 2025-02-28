#ifndef PROGRA_III_FINAL_PROJECT_MOVIEBUILDER_H
#define PROGRA_III_FINAL_PROJECT_MOVIEBUILDER_H

#include <string>
#include <unordered_set>
#include <sstream>
#include "Movie.h"

using std::string, std::unordered_set, std::istringstream;

class MovieBuilder {
    int id;
    string title;
    string plot;
    unordered_set<string> tags;
public:
    MovieBuilder();
    MovieBuilder &setId(const string &i);
    MovieBuilder &setTitle(const string &t);
    MovieBuilder &setPlot(const string &p);
    MovieBuilder &setTags(const string &ts);
    Movie build();
    void reset();

    const int &getId() const;
    const string &getTitle() const;
    const string &getPlot() const;
    const unordered_set<string> &getTags() const;
};

#endif //PROGRA_III_FINAL_PROJECT_MOVIEBUILDER_H
