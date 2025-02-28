#include <iostream>
#include "Movie.h"
#include "MovieRepository.h"
#include "Catalog.h"


using std::cout, std::cin, std::vector, std::string;

// Muestra información detallada de una película
void displayMovieDetails(const Movie &movie) {
    cout << "Título: " << movie.getTitle() << "\nSinopsis: " << movie.getPlot() << "\nTags: ";
    for (const auto &tag : movie.getTags()) {
        cout << tag << ", ";
    }
    cout << '\n';
}

// Maneja la interacción del usuario con una película
void handleMovieSelection(const Movie &movie) {
    Catalog &catalog = Catalog::getInstance();
    int choice = 0;

    while (choice != 3) {
        cout << "\nSelecciona la película:\n";
        displayMovieDetails(movie);
        cout << "\nOpciones:\n1. Agrega a Tus likes\n2. Agrega a Ver más tarde\n3. Volver\nElige: ";
        cin >> choice;

        switch (choice) {
            case 1:
                catalog.addToLikes(movie);
                cout << "Agregado a Tus likes.\n";
                break;
            case 2:
                catalog.addToWatchLater(movie);
                cout << "Agregado a Ver más tarde.\n";
                break;
            case 3:
                return;
            default:
                cout << "Opción inválida. Intenta de nuevo.\n";
        }
    }
}

// Muestra una lista de películas con paginación
void displayMovies(const vector<Movie> &movies) {
    if (movies.empty()) {
        cout << "No se encontraron películas.\n";
        return;
    }

    size_t page = 0, pageSize = 5;
    while (true) {
        size_t start = page * pageSize;
        size_t end = std::min(start + pageSize, movies.size());

        cout << "\nPelículas:\n";
        for (size_t i = start; i < end; ++i) {
            cout << (i - start + 1) << ". " << movies[i].getTitle() << '\n';
        }

        cout << "\n1. Selecciona una película\n2. Regresar\n3. Salir";
        if (end < movies.size()) cout << "\n4. Siguiente";
        cout << "\nElige: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                int select;
                cout << "Ingresa un número: ";
                cin >> select;
                if (select >= 1 && select <= static_cast<int>(end - start)) {
                    handleMovieSelection(movies[start + select - 1]);
                } else {
                    cout << "Opción inválida.\n";
                }
                break;
            }
            case 2:
                if (page > 0) --page;
                break;
            case 3:
                return;
            case 4:
                if (end < movies.size()) ++page;
                break;
            default:
                cout << "Opción inválida.\n";
        }
    }
}

// Maneja el menú principal del programa
void mainMenu() {
    MovieRepository &repository = MovieRepository::getInstance();
    repository.loadCSV("mpst_full_data.csv");
    const Catalog &catalog = Catalog::getInstance();

    while (true) {
        cout << "\nMenu:\n"
             << "1. Buscar por texto\n"
             << "2. Buscar por tag\n"
             << "3. Tus likes\n"
             << "4. Tus Ver más tarde\n"
             << "5. Recomendaciones\n"
             << "6. Salir\n"
             << "Elige: ";

        int choice;
        cin >> choice;
        cin.ignore(); // Limpia el buffer para evitar problemas con `getline`

        switch (choice) {
            case 1: {
                cout << "Ingresa el texto: ";
                string text;
                getline(cin, text);
                cout << "\nResultados: " << text << '\n';
                displayMovies(repository.searchByText(text));
                break;
            }
            case 2: {
                cout << "Ingresa el tad: ";
                string tag;
                getline(cin, tag);
                cout << "\nResultados: " << tag << '\n';
                displayMovies(repository.searchByTag(tag));
                break;
            }
            case 3:
                cout << "Likes:\n";
                displayMovies(repository.searchByIds(catalog.getLikes()));
                break;
            case 4:
                cout << "Ver más tarde:\n";
                displayMovies(repository.searchByIds(catalog.getWatchLater()));
                break;
            case 5:
                if (catalog.getLikes().empty()) {
                    cout << "Por favor, dale like a alguna película primero.\n";
                    break;
                }
                cout << "Recomendaciones:\n";
                displayMovies(repository.getRecommendations(catalog.getTagPreferences()));
                break;
            case 6:
                cout << "Cargando...\n";
                return;
            default:
                cout << "Opción inválida. Intenta de nuevo.\n";
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
