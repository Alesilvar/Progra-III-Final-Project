//
// Created by Alessandra on 27/02/2025.
//

#include "UserInterfaz.h"
#include <iostream>

using std::unordered_set, std::unordered_map, std::string, std::cout;

// Constructor privado del Singleton
UserManager::UserManager() = default;

// Retorna la única instancia de UserManager
UserManager &UserManager::getInstance() {
    static UserManager instance;
    return instance;
}

// Agrega una película a la lista de "ver después"
void UserManager::addToWatchLater(const Movie &movie) {
    watchLater.emplace(movie.getId());
    cout << "Added '" << movie.getTitle() << "' to watch later\n";
}

// Agrega una película a la lista de "me gusta" y actualiza preferencias de etiquetas
void UserManager::addToLikes(const Movie &movie) {
    likes.emplace(movie.getId());
    for (const auto &tag: movie.getTags()) {
        tagPreferences[tag]++;
    }
    cout << "Added '" << movie.getTitle() << "' to likes\n";
}

// Retorna la lista de "ver después"
const unordered_set<int> &UserManager::getWatchLater() const {
    return watchLater;
}

// Retorna la lista de "me gusta"
const unordered_set<int> &UserManager::getLikes() const {
    return likes;
}

// Retorna el mapa de preferencias de etiquetas basado en las películas que le gustan al usuario
const unordered_map<string, double> &UserManager::getTagPreferences() const {
    return tagPreferences;
}
