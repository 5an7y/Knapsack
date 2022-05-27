#pragma once

#include <vector>
#include <string>

struct objeto {
    int64_t valor;
    int64_t peso;
};

class Instancia {
    public:
        Instancia(const std::string& fichero);

        std::vector<objeto> objetos;
        int N;
        int64_t max_peso;
};