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
        Genetico solucion(instancia);

        std::ofstream output(ficheroSalida.c_str());
        output << solucion.max_val << '\n';
        while (!solucion.fitness_vals.empty()) {
            output << solucion.fitness_vals.front() << " " 
                   << solucion.penalty_vals.front() << '\n';
            solucion.fitness_vals.pop();
            solucion.penalty_vals.pop();
        }
    } else if (metodo == "Memetico") {
        Genetico solucion(instancia, true);

        std::ofstream output(ficheroSalida.c_str());
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