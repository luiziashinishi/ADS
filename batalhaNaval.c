#include <stdio.h>
#define TAMANHO 10
#define TAM_HAB 5

#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Inicializa o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Posiciona um navio horizontal de tamanho 3
void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < 3; i++) {
        if (coluna + i < TAMANHO) {
            tabuleiro[linha][coluna + i] = NAVIO;
        }
    }
}

// Imprime o tabuleiro com caracteres representativos
void imprimirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == AGUA)
                printf(" .");
            else if (tabuleiro[i][j] == NAVIO)
                printf(" N");
            else if (tabuleiro[i][j] == HABILIDADE)
                printf(" *");
            else
                printf(" ?");
        }
        printf("\n");
    }
}

// Gera matriz de habilidade Cone (5x5) com origem no topo
void gerarMatrizCone(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= 2 - i && j <= 2 + i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Gera matriz de habilidade Cruz (5x5) com cruz no centro
void gerarMatrizCruz(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Gera matriz de habilidade Octaedro (5x5) em forma de losango
void gerarMatrizOctaedro(int habilidade[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Aplica a habilidade ao tabuleiro, usando ponto de origem (centro)
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int offset = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int linhaTab = origemLinha - offset + i;
            int colunaTab = origemColuna - offset + j;

            if (linhaTab >= 0 && linhaTab < TAMANHO && colunaTab >= 0 && colunaTab < TAMANHO) {
                if (habilidade[i][j] == 1 && tabuleiro[linhaTab][colunaTab] == AGUA) {
                    tabuleiro[linhaTab][colunaTab] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    // 1. Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // 2. Posiciona alguns navios
    posicionarNavio(tabuleiro, 2, 3); // Exemplo horizontal
    posicionarNavio(tabuleiro, 6, 6); // Outro navio

    // 3. Gera matrizes de habilidades
    gerarMatrizCone(cone);
    gerarMatrizCruz(cruz);
    gerarMatrizOctaedro(octaedro);

    // 4. Aplica as habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, 4, 4);       // Cone no meio superior
    aplicarHabilidade(tabuleiro, cruz, 1, 1);       // Cruz no canto superior esquerdo
    aplicarHabilidade(tabuleiro, octaedro, 7, 2);   // Octaedro no lado inferior esquerdo

    // 5. Exibe o tabuleiro
    printf("Legenda: . = água | N = navio | * = habilidade\n\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}
