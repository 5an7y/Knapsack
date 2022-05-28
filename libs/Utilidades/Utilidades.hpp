#pragma once

#include "Instancia.hpp"

struct FitnessInfo {
    int64_t fitness = 0;
    int64_t valor_total = 0;
    int64_t peso_total = 0;

    FitnessInfo();
    FitnessInfo(
        const Instancia& instancia, 
        const std::vector<bool>& sol,
        const int iteracion = -1
    );

    void recalcular_fitness(
        const Instancia& instancia,
        const int64_t penalti = -1
    );
};