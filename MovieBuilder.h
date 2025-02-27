//
// Created by Alessandra on 27/02/2025.
//

#ifndef PROGRA_III_FINAL_PROJECT_MOVIEBUILDER_H
#define PROGRA_III_FINAL_PROJECT_MOVIEBUILDER_H

#include <string>
#include <unordered_set>
#include "Movie.h"

class MovieBuilder {
private:
    int id;
    std::string title;
    std::string plot;
    std::unordered_set<std::string> tags;

public:
    MovieBuilder();

    MovieBuilder &setId(const std::string &i);
    MovieBuilder &setTitle(const std::string &t);
    MovieBuilder &setPlot(const std::string &p);
    MovieBuilder &setTags(const std::string &ts);

    Movie build();
    void reset();

    const int &getId() const;
    const std::string &getTitle() const;
    const std::string &getPlot() const;
    const std::unordered_set<std::string> &getTags() const;
};

#endif //PROGRA_III_FINAL_PROJECT_MOVIEBUILDER_H
