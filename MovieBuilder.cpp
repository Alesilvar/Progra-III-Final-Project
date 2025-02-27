//
// Created by Alessandra on 27/02/2025.
//

#include "MovieBuilder.h"
#include <sstream>

using std::string, std::unordered_set, std::istringstream, std::getline, std::stoi;

// Constructor
MovieBuilder::MovieBuilder() : id(0) {}

// Set ID from a string
MovieBuilder &MovieBuilder::setId(const string &i) {
    this->id = stoi(i.substr(2)); // Convert string ID to int and assign
    return *this; // Allows method chaining
}

// Set movie title
MovieBuilder &MovieBuilder::setTitle(const string &t) {
    this->title = t;
    return *this;
}

// Set movie plot, removing quotes if present
MovieBuilder &MovieBuilder::setPlot(const string &p) {
    string processedPlot = p;
    if (!p.empty() && p.front() == '"' && p.back() == '"') {
        processedPlot = p.substr(1, p.size() - 2);
    }
    this->plot = processedPlot;
    return *this;
}

// Set movie tags from a comma-separated string
MovieBuilder &MovieBuilder::setTags(const string &ts) {
    istringstream tagStream(ts);
    string tag;
    while (getline(tagStream, tag, ',')) {
        tag.erase(0, tag.find_first_not_of(' ')); // Trim leading spaces
        tag.erase(tag.find_last_not_of(' ') + 1); // Trim trailing spaces
        this->tags.insert(std::move(tag));
    }
    return *this;
}

// Build and return a Movie object
Movie MovieBuilder::build() {
    return {id, std::move(title), std::move(plot), std::move(tags)};
}

// Reset builder attributes
void MovieBuilder::reset() {
    this->id = 0;
    this->title.clear();
    this->plot.clear();
    this->tags.clear();
}

// Getters
const int &MovieBuilder::getId() const {
    return this->id;
}

const string &MovieBuilder::getTitle() const {
    return this->title;
}

const string &MovieBuilder::getPlot() const {
    return this->plot;
}

const unordered_set<string> &MovieBuilder::getTags() const {
    return this->tags;
}
