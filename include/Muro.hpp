#ifndef MURO_HPP
#define MURO_HPP

#include <vector>

/**
 * @brief Função principal da Parte 1.
 *
 * Determina a altura máxima do triângulo isósceles que pode ser formado
 * com as pilhas existentes, sem adicionar blocos.
 *
 * A função utiliza um algoritmo guloso aliado a busca binária para encontrar
 * a maior altura viável. O vetor de pilhas é ordenado internamente.
 *
 * @param pilhas Vetor contendo as alturas das pilhas (modificado internamente).
 * @return Altura máxima H do triângulo possível.
 */
int encontrarAlturaMaxima(std::vector<int>& pilhas);

/**
 * @brief Verifica, de forma gulosa, se é possível construir um triângulo
 * isósceles de altura H com as pilhas disponíveis.
 *
 * Assume que o vetor de pilhas já foi ordenado em ordem decrescente.
 *
 * @param H Altura desejada do triângulo.
 * @param pilhasOrdenadas Vetor de pilhas ordenado em ordem decrescente.
 * @return true se é possível formar o triângulo, false caso contrário.
 */
bool ehPossivelConstruir(int H, std::vector<int>& pilhasOrdenadas);

#endif // MURO_HPP