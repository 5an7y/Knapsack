#pragma once

#include "Instancia.hpp"

enum class Penalty {
    Ninguno,
    Fijo,
    Lineal,
    PesoInvertido
};

struct FitnessInfo {
    int64_t fitness = 0;
    int64_t valor_total = 0;
    int64_t peso_total = 0;

    FitnessInfo();
    FitnessInfo(
        const Instancia& instancia, 
        const std::vector<bool>& sol,
        const Penalty tipo_penalty,
        const int64_t penalty = -1
    );

    void recalcular_fitness(
        const Instancia& instancia,
        const Penalty tipo_penalty,
        const int64_t penalty = -1
    );
};

int64_t calcular_penalty_fijo(const std::vector<objeto>& objetos);