#include "Genetico.hpp"

#include <iostream>
#include <chrono>

using namespace std::chrono;

Genetico::Genetico(
    Instancia &instancia,
    const bool busqueda_local,
    const int tam_pob,
    const double p_cruce,
    const double p_mutacion,
    const int max_queue
): tam_pob(tam_pob), p_cruce(p_cruce), p_mutacion(p_mutacion), instancia(&instancia) {
    auto inicio = steady_clock::now();
    
    generar_poblacion_inicial();

    auto act = steady_clock::now();
    auto duracion = duration_cast<minutes>(act - inicio).count();
    int generacion = 1000;

    while (duracion < 60) {
        seleccion_torneo();
        cruza_uniforme();
        mutacion(generacion);
        elitismo(generacion);
        
        auto fitness_n = calcular_maximo_poblacion();
        auto penalizado = fitness_n;
        
        fitness_n.recalcular_fitness(*(this -> instancia), -1); // Calcular el fitness real
        if (fitness_vals.size() != max_queue) {
            fitness_vals.push(fitness_n.fitness);
            penalty_vals.push(penalizado.fitness);
        }
        
        max_val = std::max(max_val, fitness_n.fitness);
        
        //generacion += 1;
        //if (generacion == 5000)
        //    generacion = 1;
        
        act = steady_clock::now();
        duracion = duration_cast<minutes>(act - inicio).count();
    }
}

void Genetico::generar_poblacion_inicial() {
    const int N = instancia -> N;
    poblacion.resize(tam_pob);
    sig_poblacion.resize(tam_pob);
    f_pob.resize(tam_pob);
    f_sig_pob.resize(tam_pob);

    for (int i = 0; i < tam_pob; i++) {
        poblacion[i].resize(N);
        sig_poblacion[i].resize(N);
        for (int j = 0; j < N; j++)
            poblacion[i][j] = rand() % 2;
        
        f_pob[i] = FitnessInfo(*instancia, poblacion[i], 1);
    }
}

void Genetico::seleccion_torneo() {
    for (int i = 0; i < tam_pob; i++) {
        int i1 = rand() % tam_pob,
            i2 = rand() % tam_pob;
        if (f_pob[i1].fitness < f_pob[i2].fitness)
            sig_poblacion[i] = poblacion[i2];
        else 
            sig_poblacion[i] = poblacion[i1];
    }
}

void Genetico::cruza_uniforme() {
    std::vector<std::vector<bool>> vec;
    const int N = instancia -> N;
    vec.resize(tam_pob);

    for (int i = 0; i < tam_pob / 2; i++) {
        vec[i * 2].resize(N);
        vec[i * 2 + 1].resize(N);
        int i1 = rand() % tam_pob,
            i2 = rand() % tam_pob;
        bool cruce = ((double)rand() / RAND_MAX <= p_cruce);
        
        for (int j = 0; j < N; j++) {
            if (rand() % 2 && cruce) {
                vec[i * 2][j] = sig_poblacion[i1][j];
                vec[i * 2 + 1][j] = sig_poblacion[i2][j];
            } else {
                vec[i * 2][j] = sig_poblacion[i2][j];
                vec[i * 2 + 1][j] = sig_poblacion[i1][j];
            }
        }
    }

    std::swap(vec, sig_poblacion);
}

void Genetico::mutacion(const int iteracion) {
    const int N = instancia -> N;
    for (int i = 0; i < tam_pob; i++) {
        for (int j = 0; j < N; j++) {
            double r = (double)rand() / RAND_MAX;
            if (r <= p_mutacion)
                sig_poblacion[i][j] = sig_poblacion[i][j] ^ 1;
        }
        f_sig_pob[i] = FitnessInfo(*instancia, sig_poblacion[i], iteracion);
    }
}

void Genetico::elitismo(const int iteracion) {
    int max_fitness_pob = 0;
    int max_fitness_sig_pob = 0,
        min_fitness_sig_pob = 0;

    for (int i = 1; i < tam_pob; i++) {
        if (f_pob[max_fitness_pob].fitness < f_pob[i].fitness)
            max_fitness_pob = i;
        if (f_sig_pob[max_fitness_sig_pob].fitness < f_sig_pob[i].fitness)
            max_fitness_sig_pob = i;
        if (f_sig_pob[min_fitness_sig_pob].fitness > f_sig_pob[i].fitness)
            min_fitness_sig_pob = i;
    }

    if (f_pob[max_fitness_pob].fitness > f_sig_pob[max_fitness_sig_pob].fitness) {
        std::swap(sig_poblacion[min_fitness_sig_pob], poblacion[max_fitness_pob]);
        f_sig_pob[min_fitness_sig_pob] = FitnessInfo(*instancia, sig_poblacion[min_fitness_sig_pob], iteracion);
    }

    std::swap(f_pob, f_sig_pob);
    std::swap(poblacion, sig_poblacion);
}

FitnessInfo Genetico::calcular_maximo_poblacion() {
    auto ans = f_pob[0];
    for (int i = 1; i < tam_pob; i++)
        if (ans.fitness < f_pob[i].fitness)
            ans = f_pob[i];
    
    return ans;
}