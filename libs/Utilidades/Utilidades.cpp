#include "Utilidades.hpp"

FitnessInfo::FitnessInfo(){}

FitnessInfo::FitnessInfo(
    const Instancia& instancia, 
    const std::vector<bool>& sol,
    const Penalty tipo_penalty,
    const int64_t penalty
) {
    const int N = instancia.N;
    const auto& obj = instancia.objetos;

    for (int i = 0; i < N; i++) {
        valor_total += sol[i] * obj[i].valor;
        peso_total += sol[i] * obj[i].peso;
    }

    recalcular_fitness(instancia, tipo_penalty, penalty);
}

void FitnessInfo::recalcular_fitness(
    const Instancia& instancia,
    const Penalty tipo_penalty,
    const int64_t penalty
) {
    const int64_t max_peso = instancia.max_peso;
    fitness = valor_total;

    if (peso_total > max_peso) {
        switch (tipo_penalty) {
            case Penalty::Ninguno :
                fitness = 0;
                break;
            
            case Penalty::Lineal :
                fitness -= (peso_total - max_peso) * penalty;
                break;
            
            case Penalty::Fijo :
                fitness -= (peso_total - max_peso) * penalty;
                break; 
            
            case Penalty::PesoInvertido :
                fitness = -peso_total;
                break; 

            default:
                break;     
        }
    }
}

int64_t calcular_penalty_fijo(const std::vector<objeto>& objetos) {
    int64_t penalty = 0;
    for (const auto& objeto: objetos)
        penalty = std::max(objeto.valor / objeto.peso + 1, penalty);
    return penalty;
}