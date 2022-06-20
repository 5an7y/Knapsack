#include <iostream>
#include <chrono>
#include <fstream>

#include "Instancia.hpp"
#include "SolucionDP.hpp"
#include "Iterativa.hpp"
#include "Genetico.hpp"

using namespace std;
using namespace chrono;


int main(int argc, char *argv[]) {
    if (argc < 6) {
        throw invalid_argument(
            "El programa debe recibir 2 argumentos:\n"
            "1- Nombre del fichero de entrada\n"
            "2- Nombre del fichero de salida\n"
            "3- Metodo de optimizacion."
        );
    }

    // Parsing de los argumentos
    string ficheroEntrada(argv[1]);
    string ficheroSalida(argv[2]);
    string metodo(argv[3]);
    int semillarand = stoi(argv[4]);
    int duracion_min = stoi(argv[5]);

    // Iniciar la instancia
    srand(semillarand);
    Instancia instancia(ficheroEntrada, duracion_min);

    if (metodo == "DP") {
        SolucionDP solucion(instancia);
    } else if (metodo == "Iterativa") {
        Iterativa solucion(instancia);

        std::ofstream output(ficheroSalida.c_str());
        output << solucion.max_val << '\n';
        while (!solucion.fitness_vals.empty()) {
            output << solucion.fitness_vals.front() << " " 
                   << solucion.penalty_vals.front() << '\n';
            solucion.fitness_vals.pop();
            solucion.penalty_vals.pop();
        }
    } else if (metodo == "Genetico") {
        string penalty_torneo_arg(argv[6]);
        Penalty penalty_torneo;

        if (penalty_torneo_arg == "Fijo") 
            penalty_torneo = Penalty::Fijo;
        else if (penalty_torneo_arg == "Lineal")
            penalty_torneo = Penalty::Lineal;
        else if (penalty_torneo_arg == "PesoInvertido")
            penalty_torneo = Penalty::PesoInvertido;
        else if (penalty_torneo_arg == "Ninguno")
            penalty_torneo = Penalty::Ninguno;
        else
            throw std::invalid_argument("No se dio una opcion valida para el penalty del torneo.");
        
        Genetico solucion(
            instancia,                        // Instancia
            false,                            // Busqueda Local
            200,                              // Tamanio poblacion
            0.9,                              // Probabilidad de cruce
            10.0 / (double) instancia.N,      // Probabilidad de mutacion
            penalty_torneo                    // Penalty del torneo
        );

        ofstream output(ficheroSalida.c_str());
        output << solucion.max_val << '\n';
        while (!solucion.fitness_vals.empty()) {
            output << solucion.fitness_vals.front() << " " 
                   << solucion.penalty_vals.front() << '\n';
            solucion.fitness_vals.pop();
            solucion.penalty_vals.pop();
        }
        
    } else if (metodo == "Memetico") {
        string penalty_torneo_arg(argv[6]);
        Penalty penalty_torneo;

        if (penalty_torneo_arg == "Fijo") 
            penalty_torneo = Penalty::Fijo;
        else if (penalty_torneo_arg == "Lineal")
            penalty_torneo = Penalty::Lineal;
        else if (penalty_torneo_arg == "PesoInvertido")
            penalty_torneo = Penalty::PesoInvertido;
        else if (penalty_torneo_arg == "Ninguno")
            penalty_torneo = Penalty::Ninguno;
        else
            throw std::invalid_argument("No se dio una opcion valida para el penalty del torneo.");
        
        string penalty_busqueda_arg(argv[7]);
        Penalty penalty_busqueda;

        if (penalty_busqueda_arg == "Fijo") 
            penalty_busqueda = Penalty::Fijo;
        else if (penalty_busqueda_arg == "Lineal")
            penalty_busqueda = Penalty::Lineal;
        else if (penalty_busqueda_arg == "PesoInvertido")
            penalty_busqueda = Penalty::PesoInvertido;
        else if (penalty_busqueda_arg == "Ninguno")
            penalty_busqueda = Penalty::Ninguno;
        else
            throw std::invalid_argument("No se dio una opcion valida para el penalty de la busqueda. [" + penalty_busqueda_arg + "]");

        Genetico solucion(
            instancia,                        // Instancia
            true,                             // Busqueda Local
            200,                              // Tamanio poblacion
            0.9,                              // Probabilidad de cruce
            10.0 / (double) instancia.N,      // Probabilidad de mutacion
            penalty_torneo,                   // Penalty del torneo
            penalty_busqueda                  // Penalty de la busqueda local
        );

        ofstream output(ficheroSalida.c_str());
        output << solucion.max_val << '\n';
        while (!solucion.fitness_vals.empty()) {
            output << solucion.fitness_vals.front() << " " 
                   << solucion.penalty_vals.front() << '\n';
            solucion.fitness_vals.pop();
            solucion.penalty_vals.pop();
        }
    }
      
    return 0;
}