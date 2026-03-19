#include "../include/Arvore.hpp"
#include <vector>
#include <cmath>      // sqrt()
#include <limits>     // std::numeric_limits<double>::infinity()
#include <sstream>    // std::stringstream
#include <iomanip>    // std::setprecision, std::fixed
#include <algorithm>  // std::sort

/**
 * @brief Construtor padrão.
 *
 * Inicializa uma tripla com perímetro infinito e índices inválidos,
 * usada como valor inicial para comparação.
 */
TriplaResultado::TriplaResultado() {
    perimetro = std::numeric_limits<double>::infinity();
    idx1 = idx2 = idx3 = -1;
}

/**
 * @brief Construtor para uma tripla válida.
 *
 * Recebe três índices e os armazena em ordem crescente,
 * garantindo a correção das comparações lexicográficas.
 */
TriplaResultado::TriplaResultado(double p, int i1, int i2, int i3) {
    perimetro = p;

    // Ordenação manual dos índices (sem depender de biblioteca)
    int a = i1, b = i2, c = i3, temp;
    if (a > b) { temp = a; a = b; b = temp; }
    if (a > c) { temp = a; a = c; c = temp; }
    if (b > c) { temp = b; b = c; c = temp; }

    idx1 = a; idx2 = b; idx3 = c;
}

/**
 * @brief Compara esta tripla com outra, verificando se é pior.
 *
 * Critério:
 * 1. Menor perímetro é sempre melhor.
 * 2. Se perímetros forem iguais, usa comparação lexicográfica
 *    (índices em ordem crescente).
 *
 * @return true se esta tripla for pior que a outra.
 */
bool TriplaResultado::ehPiorQue(const TriplaResultado& outra) const {
    if (perimetro > outra.perimetro) return true;
    if (perimetro < outra.perimetro) return false;

    if (idx1 > outra.idx1) return true;
    if (idx1 < outra.idx1) return false;

    if (idx2 > outra.idx2) return true;
    if (idx2 < outra.idx2) return false;

    return idx3 > outra.idx3;
}

/**
 * @brief Calcula a distância euclidiana entre dois pontos.
 */
double distancia(const Ponto& p1, const Ponto& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

/**
 * @brief Calcula o perímetro do triângulo formado por três pontos.
 */
double perimetro(const Ponto& p1, const Ponto& p2, const Ponto& p3) {
    return distancia(p1, p2) + distancia(p2, p3) + distancia(p3, p1);
}

/**
 * @brief Caso base (força bruta).
 *
 * Calcula o menor perímetro possível testando todas as combinações
 * de três pontos em O(n³), usado quando o subconjunto é pequeno.
 */
TriplaResultado calcularPerimetroBruto(std::vector<Ponto>& pontos) {
    TriplaResultado melhorTripla;
    int n = static_cast<int>(pontos.size());

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                double pAtual = perimetro(pontos[i], pontos[j], pontos[k]);
                TriplaResultado atual(pAtual,
                                      pontos[i].indiceOriginal,
                                      pontos[j].indiceOriginal,
                                      pontos[k].indiceOriginal);
                if (melhorTripla.ehPiorQue(atual)) {
                    melhorTripla = atual;
                }
            }
        }
    }
    return melhorTripla;
}

/**
 * @brief Passo recursivo do algoritmo de Divisão e Conquista.
 */
TriplaResultado encontrarMinimoRecursivo(std::vector<Ponto>& Px) {
    int n = static_cast<int>(Px.size());
    if (n <= 5) return calcularPerimetroBruto(Px);

    int meio = n / 2;
    Ponto pontoMeio = Px[meio];

    std::vector<Ponto> esquerda(Px.begin(), Px.begin() + meio);
    std::vector<Ponto> direita(Px.begin() + meio, Px.end());

    TriplaResultado melhor = encontrarMinimoRecursivo(esquerda);
    TriplaResultado direitaRes = encontrarMinimoRecursivo(direita);
    if (melhor.ehPiorQue(direitaRes)) melhor = direitaRes;

    double delta = melhor.perimetro;
    std::vector<Ponto> faixa;
    for (const auto& p : Px) {
        if (std::abs(p.x - pontoMeio.x) < delta / 2.0)
            faixa.push_back(p);
    }

    std::sort(faixa.begin(), faixa.end(),
              [](const Ponto& a, const Ponto& b) { return a.y < b.y; });

    int m = static_cast<int>(faixa.size());
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            if (faixa[j].y - faixa[i].y >= delta / 2.0) break;
            for (int k = j + 1; k < m; ++k) {
                if (faixa[k].y - faixa[i].y >= delta / 2.0) break;
                double pAtual = perimetro(faixa[i], faixa[j], faixa[k]);
                TriplaResultado atual(pAtual,
                                      faixa[i].indiceOriginal,
                                      faixa[j].indiceOriginal,
                                      faixa[k].indiceOriginal);
                if (melhor.ehPiorQue(atual)) {
                    melhor = atual;
                    delta = melhor.perimetro;
                }
            }
        }
    }

    return melhor;
}

/**
 * @brief Função principal da Parte 2.
 */
std::string encontrarMenorPerimetro(std::vector<Ponto>& arvores) {
    std::sort(arvores.begin(), arvores.end(),
              [](const Ponto& a, const Ponto& b) { return a.x < b.x; });

    TriplaResultado resultado = encontrarMinimoRecursivo(arvores);

    std::ostringstream ss;
    ss << "Parte 2: " << std::fixed << std::setprecision(4)
       << resultado.perimetro << " "
       << resultado.idx1 << " " << resultado.idx2 << " " << resultado.idx3;

    return ss.str();
}