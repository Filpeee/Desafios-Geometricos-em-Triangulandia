#ifndef ARVORE_HPP
#define ARVORE_HPP

#include <vector>
#include <string>

/**
 * @brief Representa uma árvore no plano cartesiano.
 *
 * Cada árvore é modelada como um ponto bidimensional,
 * armazenando suas coordenadas (x, y) e o índice original (baseado em 1),
 * necessário para a saída no formato exigido pelo enunciado.
 */
struct Ponto {
    double x, y;
    int indiceOriginal; ///< Índice original do ponto (inicia em 1)
};

/**
 * @brief Estrutura que representa o resultado de uma busca pelo triângulo mínimo.
 *
 * Armazena o perímetro do triângulo e os índices dos três pontos que o formam.
 * Inclui funções auxiliares para comparação e inicialização.
 */
struct TriplaResultado {
    double perimetro; ///< Perímetro do triângulo formado
    int idx1, idx2, idx3; ///< Índices dos pontos (em ordem crescente)

    /// @brief Construtor padrão: inicializa com valores inválidos ou infinitos.
    TriplaResultado();

    /// @brief Construtor para criar uma tripla válida.
    TriplaResultado(double p, int i1, int i2, int i3);

    /**
     * @brief Compara se esta tripla é pior (maior perímetro ou não lexicograficamente mínima)
     * que outra.
     * @param outra Outra tripla a ser comparada.
     * @return true se esta tripla é pior que a outra, false caso contrário.
     */
    bool ehPiorQue(const TriplaResultado& outra) const;
};

/**
 * @brief Função principal da Parte 2.
 *
 * Encontra o triângulo de menor perímetro formado por três árvores.
 * Implementa o método de Divisão e Conquista.
 *
 * @param arvores Vetor contendo os pontos (árvores).
 * @return String formatada no padrão: "Parte 2: P A1 A2 A3".
 */
std::string encontrarMenorPerimetro(std::vector<Ponto>& arvores);

/**
 * @brief Função recursiva que encontra o triângulo mínimo por Divisão e Conquista.
 *
 * @param Px Vetor de pontos ordenado por coordenada X.
 * @return A melhor TriplaResultado encontrada no subconjunto.
 */
TriplaResultado encontrarMinimoRecursivo(std::vector<Ponto>& Px);

/**
 * @brief Função de força bruta usada para casos base da recursão.
 *
 * Testa todas as combinações possíveis de 3 pontos.
 *
 * @param pontos Subconjunto pequeno de pontos.
 * @return A TriplaResultado com o menor perímetro encontrado nesse subconjunto.
 */
TriplaResultado calcularPerimetroBruto(std::vector<Ponto>& pontos);

/**
 * @brief Calcula a distância euclidiana entre dois pontos.
 *
 * @param p1 Primeiro ponto.
 * @param p2 Segundo ponto.
 * @return Distância euclidiana entre p1 e p2.
 */
double distancia(const Ponto& p1, const Ponto& p2);

/**
 * @brief Calcula o perímetro formado por três pontos.
 *
 * @param p1 Primeiro ponto.
 * @param p2 Segundo ponto.
 * @param p3 Terceiro ponto.
 * @return Perímetro do triângulo formado pelos três pontos.
 */
double perimetro(const Ponto& p1, const Ponto& p2, const Ponto& p3);

#endif // ARVORE_HPP