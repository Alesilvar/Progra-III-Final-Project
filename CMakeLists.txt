cmake_minimum_required(VERSION 3.30)
project(Progra_III_Final_Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(Progra_III_Final_Project main.cpp
        Movie.cpp
        ManejoDatos.cpp
        MovieBuilder.cpp
        Trie.cpp
        UserInterfaz.cpp)
