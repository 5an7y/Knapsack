#include "Utilidades.hpp"

FitnessInfo::FitnessInfo(){}

FitnessInfo::FitnessInfo(
    const Instancia& instancia, 
    const std::vector<bool>& sol,
    const int iteracion
) {
    int N = instancia.N;
    const auto& obj = instancia.objetos;

    for (int i = 0; i < N; i++) {
        valor_total += sol[i] * obj[i].valor;
        peso_total += sol[i] * obj[i].peso;
    }

    recalcular_fitness(instancia, iteracion);
}

void FitnessInfo::recalcular_fitness(
    const Instancia& instancia,
    const int64_t penalti
) {
    auto max_peso = instancia.max_peso;
    if (peso_total > max_peso && penalti == -1) 
        fitness = 0;
    else if (peso_total > max_peso)
        fitness = valor_total - (peso_total - max_peso) * penalti;
    else
        fitness = valor_total;
}