#include "Instancia.hpp"

#include <fstream>

Instancia::Instancia(const std::string& fichero, const int duracion_min) {
    std::ifstream input(fichero.c_str());
    input >> N >> max_peso;
    objetos.resize(N);

    for (int i = 0; i < N; i++)
        input >> objetos[i].peso >> objetos[i].valor;
    this -> duracion_min = duracion_min;
}