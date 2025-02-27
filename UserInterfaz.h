//
// Created by Alessandra on 27/02/2025.
//

#ifndef PROGRA_III_FINAL_PROJECT_USERINTERFAZ_H
#define PROGRA_III_FINAL_PROJECT_USERINTERFAZ_H

#include <unordered_set>
#include <unordered_map>
#include <string>
#include "Movie.h"

class UserManager {
private:
    std::unordered_set<int> watchLater;
    std::unordered_set<int> likes;
    std::unordered_map<std::string, double> tagPreferences;

    UserManager(); // Constructor privado para Singleton
    ~UserManager() = default;

public:
    static UserManager &getInstance();

    void addToWatchLater(const Movie &movie);
    void addToLikes(const Movie &movie);

    const std::unordered_set<int> &getWatchLater() const;
    const std::unordered_set<int> &getLikes() const;
    const std::unordered_map<std::string, double> &getTagPreferences() const;
};

#endif //PROGRA_III_FINAL_PROJECT_USERINTERFAZ_H
