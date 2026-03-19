#include <iostream>
#include <vector>
#include <string>
#include "../include/Muro.hpp"
#include "../include/Arvore.hpp"

/**
 * @brief Função principal do programa TP2.
 *
 * Lê a entrada padrão no formato descrito no enunciado,
 * resolve as duas partes do problema e imprime a saída
 * formatada conforme especificação.
 */
int main() {
    // Otimização de I/O para grandes entradas
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // --- Parte 1: Leitura das pilhas ---
    int n;
    std::cin >> n;
    std::vector<int> pilhas(n);
    for (int& b : pilhas)
        std::cin >> b;

    // --- Parte 2: Leitura das árvores ---
    int z;
    std::cin >> z;
    std::vector<Ponto> arvores(z);
    for (int i = 0; i < z; ++i) {
        std::cin >> arvores[i].x >> arvores[i].y;
        arvores[i].indiceOriginal = i + 1; // Índice base 1
    }

    // --- Processamento ---
    int alturaMaxima = encontrarAlturaMaxima(pilhas);
    std::string resultadoParte2 = encontrarMenorPerimetro(arvores);

    // --- Saída ---
    std::cout << "Parte 1: " << alturaMaxima << "\n";
    std::cout << resultadoParte2 << "\n";

    return 0;
}