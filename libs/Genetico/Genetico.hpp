#pragma once

#include "Instancia.hpp"
#include "Utilidades.hpp"

#include <queue>

class Genetico {
    public:
        Genetico(
            Instancia &instancia,
            const bool busqueda_local = false,
            const int tam_pob = 1000,
            const double p_cruce = 0.9,
            const double p_mutacion = 0.1,
            const Penalty penalty_torneo = Penalty::Fijo,
            const Penalty penalty_busqueda_local = Penalty::Fijo,
            const int max_queue = 10000
        );
        
        int64_t max_val = 0;
        std::queue<int64_t> fitness_vals, penalty_vals;

    private:
        Penalty penalty_torneo, penalty_busqueda_local;
        
        int tam_pob;
        int64_t generacion, maximo_generacion;
        double p_mutacion, p_cruce;
        Instancia* instancia;
        std::vector<std::vector<bool>> poblacion,
                                       aux_poblacion;
        std::vector<FitnessInfo> f_pob;

        void generar_poblacion_inicial();
        void calcular_fitness_poblacion(const Penalty tipo_penalty);

        void seleccion_torneo();
        void cruza_uniforme();
        void mutacion();
        void aplicar_busqueda_local();
        void elitismo();

        void _busqueda_local(
            const Instancia& instancia,
            std::vector<bool>& solucion,
            FitnessInfo& fitness_act
        );
        
        void calcular_mejor_poblacion();

        std::vector<bool> mejor_elemento;
        FitnessInfo f_mejor;
};