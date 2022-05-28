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
            const int max_queue = 10000
        );
        
        int64_t max_val = 0;
        std::queue<int64_t> fitness_vals, penalty_vals;

    private:
        int tam_pob;
        double p_mutacion, p_cruce;
        Instancia* instancia;
        std::vector<std::vector<bool>> poblacion,
                                       sig_poblacion;
        std::vector<FitnessInfo> f_pob, f_sig_pob;

        void generar_poblacion_inicial();

        void seleccion_torneo();
        void cruza_uniforme();
        void mutacion(const int generacion);
        void elitismo(const int generacion);

        void busqueda_local();
        FitnessInfo calcular_maximo_poblacion();
};