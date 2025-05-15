#include <stdio.h>

// -------------------------------
// Função recursiva para a TORRE
// -------------------------------
void moverTorre(int casas) {
    if (casas == 0) return;
    printf("Direita\n");
    moverTorre(casas - 1);
}

// -------------------------------
// Função recursiva para o BISPO com loops aninhados (vertical + horizontal)
// -------------------------------
void moverBispo(int vertical, int horizontal) {
    if (vertical == 0 || horizontal == 0) return;

    for (int v = 0; v < vertical; v++) {
        for (int h = 0; h < horizontal; h++) {
            printf("Cima Direita\n");
        }
    }
}

// -------------------------------
// Função recursiva para a RAINHA
// -------------------------------
void moverRainha(int casas) {
    if (casas == 0) return;
    printf("Esquerda\n");
    moverRainha(casas - 1);
}

// -------------------------------
// Movimento do CAVALO com loops aninhados complexos
// -------------------------------
void moverCavalo() {
    int movimentos = 1; // Quantidade de "L" a serem feitos
    printf("\nMovimento do Cavalo (2 casas para Cima, 1 para Direita):\n");

    for (int m = 0; m < movimentos; m++) {
        int vertical = 0;
        for (int i = 0; i < 3; i++) {
            if (i == 2) break;  // interrompe antes da terceira repetição
            if (i % 2 == 1) continue;  // pula se for a segunda (i == 1)
            printf("Cima\n");
            vertical++;
        }

        int direita = 0;
        while (direita < 1) {
            printf("Direita\n");
            direita++;
        }
    }
}

// -------------------------------
// Função principal
// -------------------------------
int main() {
    // Quantidade de casas a se mover
    int casasTorre = 5;
    int casasBispo = 1; // 1 vez vertical com 5 horizontais (1x5)
    int casasBispoHorizontal = 5;
    int casasRainha = 8;

    // -------------------------------
    // TORRE
    // -------------------------------
    printf("Movimento da Torre (5 casas para a Direita):\n");
    moverTorre(casasTorre);

    // -------------------------------
    // BISPO (com recursividade + loops aninhados)
    // -------------------------------
    printf("\nMovimento do Bispo (5 casas na Diagonal Cima Direita):\n");
    moverBispo(casasBispo, casasBispoHorizontal);

    // -------------------------------
    // RAINHA
    // -------------------------------
    printf("\nMovimento da Rainha (8 casas para a Esquerda):\n");
    moverRainha(casasRainha);

    // -------------------------------
    // CAVALO
    // -------------------------------
    moverCavalo();

    return 0;
}
