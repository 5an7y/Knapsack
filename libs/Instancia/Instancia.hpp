#pragma once

#include <vector>
#include <string>

struct objeto {
    int64_t valor;
    int64_t peso;
};

class Instancia {
    public:
        Instancia(const std::string& fichero, const int duracion_min);

        std::vector<objeto> objetos;
        int N, duracion_min;
        int64_t max_peso;
};