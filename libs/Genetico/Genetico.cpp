#include "Genetico.hpp"

#include <iostream>
#include <chrono>
#include <stdexcept>

using namespace std::chrono;

Genetico::Genetico(
    Instancia &instancia,
    const bool busqueda_local,
    const int tam_pob,
    const double p_cruce,
    const double p_mutacion,
    const Penalty penalty_torneo,
    const Penalty penalty_busqueda_local,
    const int max_queue
): tam_pob(tam_pob), p_cruce(p_cruce), p_mutacion(p_mutacion), instancia(&instancia),
    penalty_torneo(penalty_torneo), penalty_busqueda_local(penalty_busqueda_local)  {
    
    auto inicio = steady_clock::now();
    
    generar_poblacion_inicial();
    calcular_mejor_poblacion();

    auto act = steady_clock::now();
    auto duracion = duration_cast<minutes>(act - inicio).count();
    generacion = 1;
    maximo_generacion = calcular_penalty_fijo(this -> instancia -> objetos) + 20;

    while (duracion < instancia.duracion_min) {
        seleccion_torneo();
        cruza_uniforme();
        mutacion();
        if (busqueda_local)
            aplicar_busqueda_local();
        elitismo();
        
        if (fitness_vals.size() != max_queue) {
            FitnessInfo f_mejor_penalty = f_mejor;
            f_mejor_penalty.recalcular_fitness(*(this -> instancia), penalty_torneo); 
            fitness_vals.push(f_mejor.fitness);
            penalty_vals.push(f_mejor_penalty.fitness);
        }

        generacion += 1;
        if (generacion > maximo_generacion)
            generacion = 0;
        
        act = steady_clock::now();
        duracion = duration_cast<minutes>(act - inicio).count();
    }
    this -> max_val = f_mejor.fitness;
}

void Genetico::generar_poblacion_inicial() {
    const int N = instancia -> N;
    poblacion.resize(tam_pob);
    aux_poblacion.resize(tam_pob);
    f_pob.resize(tam_pob);

    for (int i = 0; i < tam_pob; i++) {
        poblacion[i].resize(N);
        aux_poblacion[i].resize(N);
        for (int j = 0; j < N; j++)
            poblacion[i][j] = rand() % 2;
    }
}

void Genetico::calcular_fitness_poblacion(const Penalty tipo_penalty) {
    int64_t penalty;
    switch (tipo_penalty) {
        case Penalty::Fijo :
            penalty = maximo_generacion - 20;
            break;
        case Penalty::Lineal :
            penalty = generacion;
            break;
        default:
            penalty = -1;
    }

    for (int i = 0; i < tam_pob; i++)
        f_pob[i] = FitnessInfo(*instancia, poblacion[i], tipo_penalty, penalty);
}

void Genetico::seleccion_torneo() {
    calcular_fitness_poblacion(penalty_torneo);
    for (int i = 0; i < tam_pob; i++) {
        int i1 = rand() % tam_pob,
            i2 = rand() % tam_pob;
        
        if (f_pob[i1].fitness < f_pob[i2].fitness)
            aux_poblacion[i] = poblacion[i2];
        else 
            aux_poblacion[i] = poblacion[i1];
    }
    std::swap(aux_poblacion, poblacion);
}

void Genetico::cruza_uniforme() {
    const int N = instancia -> N;

    for (int i = 0; i < tam_pob / 2; i++) {
        int i1 = rand() % tam_pob,
            i2 = rand() % tam_pob;
        bool cruce = ((double)rand() / RAND_MAX <= p_cruce);
        
        for (int j = 0; j < N; j++) {
            if (rand() % 2 && cruce) {
                aux_poblacion[i * 2][j] = poblacion[i1][j];
                aux_poblacion[i * 2 + 1][j] = poblacion[i2][j];
            } else {
                aux_poblacion[i * 2][j] = poblacion[i2][j];
                aux_poblacion[i * 2 + 1][j] = poblacion[i1][j];
            }
        }
    }

    std::swap(aux_poblacion, poblacion);
}

void Genetico::mutacion() {
    const int N = instancia -> N;
    for (int i = 0; i < tam_pob; i++) {
        for (int j = 0; j < N; j++) {
            double r = (double)rand() / RAND_MAX;
            if (r <= p_mutacion)
                poblacion[i][j] = poblacion[i][j] ^ 1;
        }
    }
}

void Genetico::aplicar_busqueda_local() {
    calcular_fitness_poblacion(penalty_busqueda_local);
    for (int i = 0; i < tam_pob; i++)
        _busqueda_local(*(this -> instancia), poblacion[i], f_pob[i]);
}

void Genetico::_busqueda_local(
    const Instancia& instancia,
    std::vector<bool>& solucion,
    FitnessInfo& fitness_act
) {
    int mejor_cambio = 0;
    FitnessInfo fitness_aux, 
                mejor_fitness = fitness_act;
    
    int64_t penalty;
    switch (penalty_busqueda_local) {
        case Penalty::Fijo :
            penalty = maximo_generacion - 20;
            break;
        case Penalty::Lineal :
            penalty = generacion;
            break;

        default:
            penalty = -1;
            break;
    }

    while (mejor_cambio >= 0) {
        mejor_cambio = -1;

        for (int i = 0; i < instancia.N; i++) {
            // Calculamos el cambio en el peso y valor si cambiamos el objeto i
            if (solucion[i]) {
                fitness_aux.peso_total = fitness_act.peso_total - instancia.objetos[i].peso;
                fitness_aux.valor_total = fitness_act.valor_total - instancia.objetos[i].valor;
            } else {
                fitness_aux.peso_total = fitness_act.peso_total + instancia.objetos[i].peso;
                fitness_aux.valor_total = fitness_act.valor_total + instancia.objetos[i].valor;
            }

            fitness_aux.recalcular_fitness(instancia, penalty_busqueda_local, penalty);
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

void Genetico::elitismo() {
    calcular_fitness_poblacion(Penalty::PesoInvertido);
    
    int mejor_idx = -1, peor_idx = 0;

    for (int i = 0; i < tam_pob; i++) {
        if (f_mejor.fitness < f_pob[i].fitness)
            mejor_idx = i;
        if (f_pob[peor_idx].fitness > f_pob[i].fitness)
            peor_idx = i;
    }

    if (mejor_idx >= 0) {
        mejor_elemento = poblacion[mejor_idx];
        f_mejor = f_pob[mejor_idx];
    } else {
        poblacion[peor_idx] = mejor_elemento;
        f_pob[peor_idx] = f_mejor;
    }
}

void Genetico::calcular_mejor_poblacion() {
    calcular_fitness_poblacion(Penalty::PesoInvertido);
    
    int mejor_idx = 0;
    for (int i = 1; i < tam_pob; i++)
        if (f_pob[mejor_idx].fitness < f_pob[i].fitness)
            mejor_idx = i;
    
    mejor_elemento = poblacion[mejor_idx];
    f_mejor = f_pob[mejor_idx];
}