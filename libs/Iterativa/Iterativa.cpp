#include "Iterativa.hpp"

#include <iostream>
#include <chrono>

#include "Utilidades.hpp"

using namespace std::chrono;

std::vector<bool> generar_solucion(Instancia& instancia) {
    int N = instancia.N;
    std::vector<bool> sol(N);
    for (int i = 0; i < N; i++)
        sol[i] = rand() % 2;
    
    return sol;
}

void busqueda_local(
    const Instancia& instancia,
    std::vector<bool>& solucion,
    const int iteracion
) {
    int mejor_cambio = 0;
    FitnessInfo fitness_act(instancia, solucion, iteracion);
    FitnessInfo fitness_aux, 
                mejor_fitness = fitness_act;

    while (mejor_cambio >= 0) {
        mejor_cambio = -1;

        for (int i = 0; i < instancia.N; i++) {
            if (solucion[i]) {
                fitness_aux.peso_total = fitness_act.peso_total - instancia.objetos[i].peso;
                fitness_aux.valor_total = fitness_act.valor_total - instancia.objetos[i].valor;
            } else {
                fitness_aux.peso_total = fitness_act.peso_total + instancia.objetos[i].peso;
                fitness_aux.valor_total = fitness_act.valor_total + instancia.objetos[i].valor;
            }

            fitness_aux.recalcular_fitness(instancia, iteracion);
            if (fitness_aux.fitness > mejor_fitness.fitness) {
                mejor_cambio = i;
                mejor_fitness = fitness_aux;
            }
        }

        if (mejor_cambio >= 0) {
            solucion[mejor_cambio] = solucion[mejor_cambio] ^ 1;
            fitness_act = mejor_fitness;
        }
    }

    return;
}

void perturbar_solucion(
    const Instancia& instancia,
    std::vector<bool>& solucion,
    const double mutacion_p
) {
    for (int i = 0; i < instancia.N; i++) {
        double r = (double)rand() / RAND_MAX;
        if (r <= mutacion_p)
            solucion[i] = solucion[i] ^ 1;
    } 
    return;
}

Iterativa::Iterativa(
    Instancia& instancia,
    const double mutacion_p,
    const int max_queue
) {
    auto inicio = steady_clock::now();
    
    solucion = generar_solucion(instancia);
    int64_t f = FitnessInfo(instancia, solucion).fitness;
    max_val = f;

    auto act = steady_clock::now();
    auto duracion = duration_cast<minutes>(act - inicio).count();

    int iteracion = 1;
    while (duracion < 60) {
        busqueda_local(instancia, solucion, iteracion);
        
        FitnessInfo fitness_n(instancia, solucion, iteracion);
        FitnessInfo penalizado = fitness_n;
        fitness_n.recalcular_fitness(instancia, -1); // Calcular el fitness real
        if (fitness_vals.size() != max_queue) {
            fitness_vals.push(fitness_n.fitness);
            penalty_vals.push(penalizado.fitness);
        }

        max_val = std::max(max_val, fitness_n.fitness);
        
        perturbar_solucion(instancia, solucion, mutacion_p);
        
        iteracion = iteracion + 1;
        if (iteracion == 1000)
            iteracion = 1;
        
        act = steady_clock::now();
        duracion = duration_cast<minutes>(act - inicio).count();
    }
}