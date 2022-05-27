#include "SolucionDP.hpp"

SolucionDP::SolucionDP(Instancia& instancia) {
    int N = instancia.N,
        M = instancia.max_peso;
    std::vector<int64_t> ant(M + 1), sig(M + 1);
    const auto& objetos = instancia.objetos;
    
    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= M; j++) {
            int64_t wj = objetos[i].peso;
            int64_t pj = objetos[i].valor;
            sig[j] =  (
                (j >= wj) ? 
                std::max(ant[j - wj] + pj, ant[j]) : ant[j] 
            );
        }
        swap(sig, ant);
    }

    solucion = ant[M];
}