#include <stdio.h>
#include <string.h>

int main() {
    char nomePais1[] = "Brasil";
    int populacao1 = 213000000;
    float area1 = 8515767.0;
    float pib1 = 1900.0;
    int pontosTuristicos1 = 100;
    float densidade1 = populacao1 / area1;

    char nomePais2[] = "Argentina";
    int populacao2 = 45100000;
    float area2 = 2780400.0;
    float pib2 = 500.0;
    int pontosTuristicos2 = 70;
    float densidade2 = populacao2 / area2;

    int opcao1, opcao2;
    int atributosDisponiveis[5] = {1, 2, 3, 4, 5};

    printf("===== SUPER TRUNFO - Comparação Final =====\n");
    printf("Escolha o primeiro atributo para comparar:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turísticos\n");
    printf("5 - Densidade Demográfica\n");
    printf("Opção: ");
    scanf("%d", &opcao1);

    if (opcao1 < 1 || opcao1 > 5) {
        printf("Opção inválida!\n");
        return 1;
    }

    atributosDisponiveis[opcao1 - 1] = 0;

    printf("\nEscolha o segundo atributo (diferente do primeiro):\n");
    for (int i = 0; i < 5; i++) {
        if (atributosDisponiveis[i] != 0) {
            switch (i + 1) {
                case 1: printf("1 - População\n"); break;
                case 2: printf("2 - Área\n"); break;
                case 3: printf("3 - PIB\n"); break;
                case 4: printf("4 - Pontos Turísticos\n"); break;
                case 5: printf("5 - Densidade Demográfica\n"); break;
            }
        }
    }
    printf("Opção: ");
    scanf("%d", &opcao2);

    if (opcao2 < 1 || opcao2 > 5 || opcao2 == opcao1) {
        printf("Opção inválida ou repetida!\n");
        return 1;
    }

    float valor1A = 0, valor2A = 0;
    float valor1B = 0, valor2B = 0;

    switch (opcao1) {
        case 1: valor1A = populacao1; valor2A = populacao2; break;
        case 2: valor1A = area1; valor2A = area2; break;
        case 3: valor1A = pib1; valor2A = pib2; break;
        case 4: valor1A = pontosTuristicos1; valor2A = pontosTuristicos2; break;
        case 5: valor1A = densidade1; valor2A = densidade2; break;
        default: printf("Erro na primeira opção!\n"); return 1;
    }

    switch (opcao2) {
        case 1: valor1B = populacao1; valor2B = populacao2; break;
        case 2: valor1B = area1; valor2B = area2; break;
        case 3: valor1B = pib1; valor2B = pib2; break;
        case 4: valor1B = pontosTuristicos1; valor2B = pontosTuristicos2; break;
        case 5: valor1B = densidade1; valor2B = densidade2; break;
        default: printf("Erro na segunda opção!\n"); return 1;
    }

    printf("\nComparação entre %s e %s:\n", nomePais1, nomePais2);
    printf("Atributo 1: ");
    switch (opcao1) {
        case 1: printf("População\n"); break;
        case 2: printf("Área\n"); break;
        case 3: printf("PIB\n"); break;
        case 4: printf("Pontos Turísticos\n"); break;
        case 5: printf("Densidade Demográfica\n"); break;
    }
    printf("%s: %.2f\n", nomePais1, valor1A);
    printf("%s: %.2f\n", nomePais2, valor2A);
    int vencedorA = (opcao1 == 5) ? (valor1A < valor2A ? 1 : (valor2A < valor1A ? 2 : 0)) : (valor1A > valor2A ? 1 : (valor2A > valor1A ? 2 : 0));
    printf("Resultado Atributo 1: %s\n", vencedorA == 1 ? nomePais1 : vencedorA == 2 ? nomePais2 : "Empate");

    printf("\nAtributo 2: ");
    switch (opcao2) {
        case 1: printf("População\n"); break;
        case 2: printf("Área\n"); break;
        case 3: printf("PIB\n"); break;
        case 4: printf("Pontos Turísticos\n"); break;
        case 5: printf("Densidade Demográfica\n"); break;
    }
    printf("%s: %.2f\n", nomePais1, valor1B);
    printf("%s: %.2f\n", nomePais2, valor2B);
    int vencedorB = (opcao2 == 5) ? (valor1B < valor2B ? 1 : (valor2B < valor1B ? 2 : 0)) : (valor1B > valor2B ? 1 : (valor2B > valor1B ? 2 : 0));
    printf("Resultado Atributo 2: %s\n", vencedorB == 1 ? nomePais1 : vencedorB == 2 ? nomePais2 : "Empate");

    float soma1 = valor1A + valor1B;
    float soma2 = valor2A + valor2B;

    printf("\nSoma dos dois atributos:\n");
    printf("%s: %.2f\n", nomePais1, soma1);
    printf("%s: %.2f\n", nomePais2, soma2);
    printf("Resultado Final: ");
    printf("%s\n", (soma1 > soma2) ? nomePais1 : (soma2 > soma1) ? nomePais2 : "Empate!");
    
    return 0;
}
