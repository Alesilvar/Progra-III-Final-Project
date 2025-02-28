# Proyecto Programacion III: Plataforma de Streaming

## Integrantes

* Alessandra Valeria Silva Rios

## Video de exposición

[Carpeta Drive](https://drive.google.com/drive/folders/1NbzkfU-JEB9smz_uqPJJqI2CYd8MNO5s?usp=drive_link)

## Estructura

#### Main

- **main.cpp**: Archivo principal que ejecuta la lógica del programa.

#### 📌 Catálogo
- **Catalog.cpp / Catalog.h**: Implementa la clase `Catalog`, que gestiona la colección de películas y facilita las búsquedas. Implementa el patrón de diseño Singleton.

#### 🎬 Películas
- **Movie.cpp / Movie.h**: Representa una película con sus atributos como título, director, género, etc.
- **MovieBuilder.cpp / MovieBuilder.h**: Implementa el patrón de diseño Builder para la construcción de objetos `Movie`.
- **MovieRepository.cpp / MovieRepository.h**: Se encarga del almacenamiento y recuperación de películas en la base de datos o estructura de almacenamiento. Implementa el patrón de diseño Singleton.

#### 🔍 Estructuras de búsqueda
- **Trie.cpp / Trie.h**: Implementación de la estructura de datos Trie para búsqueda eficiente de películas por título, sinopsis o etiquetas.
- **Node.cpp / Node.h**: Define los nodos utilizados en el Trie o en otras estructuras del sistema. Implementa el patrón de diseño Factory.


## Referencias

