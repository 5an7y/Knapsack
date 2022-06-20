#pragma once

#include "Instancia.hpp"
#include "Utilidades.hpp"

#include <queue>

class Iterativa {
    public:
        Iterativa(
            Instancia& instancia,
            const Penalty tipo_penalty = Penalty::Lineal,
            const double mutacion_p = 0.1,
            const int max_stack = 10000
        );

        int64_t max_val;
        std::vector<bool> solucion;
        std::queue<int64_t> fitness_vals;
        std::queue<int64_t> penalty_vals;
};