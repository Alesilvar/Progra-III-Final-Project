#include "MovieBuilder.h"
#include <algorithm>

MovieBuilder::MovieBuilder() : id(0) {}

MovieBuilder &MovieBuilder::setId(const string &i) {
    this->id = stoi(i.substr(2)); // Convierte el ID de string a int y lo asigna
    return *this;
}

MovieBuilder &MovieBuilder::setTitle(const string &t) {
    this->title = t;
    return *this;
}

MovieBuilder &MovieBuilder::setPlot(const string &p) {
    string processedPlot = p;
    if (!p.empty() && p.front() == '"' && p.back() == '"') {
        processedPlot = p.substr(1, p.size() - 2);
    }
    this->plot = processedPlot;
    return *this;
}

MovieBuilder &MovieBuilder::setTags(const string &ts) {
    istringstream tagStream(ts);
    string tag;
    while (getline(tagStream, tag, ',')) {
        tag.erase(0, tag.find_first_not_of(' ')); // Elimina espacios iniciales
        tag.erase(tag.find_last_not_of(' ') + 1); // Elimina espacios finales
        this->tags.insert(std::move(tag));
    }
    return *this;
}

Movie MovieBuilder::build() {
    return {id, std::move(title), std::move(plot), std::move(tags)};
}

void MovieBuilder::reset() {
    this->id = 0;
    this->title.clear();
    this->plot.clear();
    this->tags.clear();
}

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
