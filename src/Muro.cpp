#include "../include/Muro.hpp"
#include <vector>

/**
 * @brief Calcula a altura máxima do triângulo isósceles possível.
 *
 * A solução usa duas varreduras lineares (esquerda e direita),
 * baseadas em um raciocínio guloso que limita o crescimento
 * de cada lado da forma triangular.
 *
 * Complexidade: O(N)
 */
int encontrarAlturaMaxima(std::vector<int>& pilhas) {
    int n = static_cast<int>(pilhas.size());
    if (n == 0) return 0;

    std::vector<int> L(n), R(n);

    // Construção da rampa à esquerda
    L[0] = 1;
    for (int i = 1; i < n; ++i)
        L[i] = std::min(pilhas[i], L[i - 1] + 1);

    // Construção da rampa à direita
    R[n - 1] = 1;
    for (int i = n - 2; i >= 0; --i)
        R[i] = std::min(pilhas[i], R[i + 1] + 1);

    // Combinação dos resultados: ponto mais alto do triângulo
    int alturaMaxima = 0;
    for (int i = 0; i < n; ++i)
        alturaMaxima = std::max(alturaMaxima, std::min(L[i], R[i]));

    return alturaMaxima;
}