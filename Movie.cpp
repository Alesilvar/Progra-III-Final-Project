//
// Created by Alessandra on 27/02/2025.
//

#include "Movie.h"

// Constructor por defecto
Movie::Movie() : id(0) {}

// Constructor con parámetros
Movie::Movie(int id, string title, string plot, unordered_set<string> tags)
        : id(id), title(std::move(title)), plot(std::move(plot)), tags(std::move(tags)) {}

// Getters
const int &Movie::getId() const {
    return this->id;
}

const string &Movie::getTitle() const {
    return this->title;
}

const string &Movie::getPlot() const {
    return this->plot;
}

const unordered_set<string> &Movie::getTags() const {
    return this->tags;
}
