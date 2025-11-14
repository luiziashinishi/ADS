#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Definição da estrutura do componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Constante para o número máximo de componentes
#define MAX_COMPONENTES 20
// Nome do componente-chave para a busca binária
#define CHAVE_BUSCA "chip central"

/**
 * @brief Exibe o vetor de componentes na tela.
 * @param componentes O array de structs Componente.
 * @param tamanho O número de componentes no array.
 */
void mostrarComponentes(Componente componentes[], int tamanho) {
    printf("\n### Lista de Componentes da Torre ###\n");
    printf("| %-25s | %-15s | %-10s |\n", "Nome", "Tipo", "Prioridade");
    printf("|---------------------------|-----------------|------------|\n");
    for (int i = 0; i < tamanho; i++) {
        printf("| %-25s | %-15s | %-10d |\n",
               componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
    printf("----------------------------------------------------------\n");
}

/**
 * @brief Realiza a ordenação Bubble Sort por nome (string) e conta as comparações.
 * @param componentes O array de structs Componente.
 * @param tamanho O número de componentes no array.
 * @param num_comparacoes Ponteiro para armazenar o número total de comparações.
 */
void bubbleSortNome(Componente componentes[], int tamanho, long long *num_comparacoes) {
    *num_comparacoes = 0;
    Componente temp;
    int trocado;
    for (int i = 0; i < tamanho - 1; i++) {
        trocado = 0;
        for (int j = 0; j < tamanho - 1 - i; j++) {
            (*num_comparacoes)++; // Contagem da comparação de strings
            // Compara os nomes ignorando maiúsculas/minúsculas para uma ordenação mais robusta
            if (strcasecmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca
                temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
                trocado = 1;
            }
        }
        if (trocado == 0) break; // O array já está ordenado
    }
}

/**
 * @brief Realiza a ordenação Insertion Sort por tipo (string) e conta as comparações.
 * @param componentes O array de structs Componente.
 * @param tamanho O número de componentes no array.
 * @param num_comparacoes Ponteiro para armazenar o número total de comparações.
 */
void insertionSortTipo(Componente componentes[], int tamanho, long long *num_comparacoes) {
    *num_comparacoes = 0;
    int i, j;
    Componente chave;
    for (i = 1; i < tamanho; i++) {
        chave = componentes[i];
        j = i - 1;

        // Compara o tipo da chave com os elementos anteriores
        while (j >= 0) {
            (*num_comparacoes)++;
            if (strcasecmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j = j - 1;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
}

/**
 * @brief Realiza a ordenação Selection Sort por prioridade (int) e conta as comparações.
 * @param componentes O array de structs Componente.
 * @param tamanho O número de componentes no array.
 * @param num_comparacoes Ponteiro para armazenar o número total de comparações.
 */
void selectionSortPrioridade(Componente componentes[], int tamanho, long long *num_comparacoes) {
    *num_comparacoes = 0;
    int i, j, indice_minimo;
    Componente temp;

    for (i = 0; i < tamanho - 1; i++) {
        indice_minimo = i;
        for (j = i + 1; j < tamanho; j++) {
            (*num_comparacoes)++; // Contagem da comparação de inteiros
            if (componentes[j].prioridade < componentes[indice_minimo].prioridade) {
                indice_minimo = j;
            }
        }
        // Troca o elemento encontrado pelo elemento atual
        if (indice_minimo != i) {
            temp = componentes[i];
            componentes[i] = componentes[indice_minimo];
            componentes[indice_minimo] = temp;
        }
    }
}

/**
 * @brief Realiza a Busca Binária por nome (string) em um array já ordenado.
 * @param componentes O array de structs Componente (deve estar ordenado por nome).
 * @param tamanho O número de componentes no array.
 * @param nome_chave O nome do componente a ser buscado.
 * @param num_comparacoes Ponteiro para armazenar o número total de comparações.
 * @return O índice do componente encontrado ou -1 se não for encontrado.
 */
int buscaBinariaPorNome(Componente componentes[], int tamanho, const char nome_chave[], long long *num_comparacoes) {
    *num_comparacoes = 0;
    int inicio = 0;
    int fim = tamanho - 1;
    int meio;
    int resultado_cmp;

    while (inicio <= fim) {
        meio = inicio + (fim - inicio) / 2;
        (*num_comparacoes)++;
        resultado_cmp = strcasecmp(componentes[meio].nome, nome_chave);

        if (resultado_cmp == 0) {
            return meio; // Encontrado
        } else if (resultado_cmp < 0) {
            inicio = meio + 1; // Ignora a metade esquerda
        } else {
            fim = meio - 1; // Ignora a metade direita
        }
    }
    return -1; // Não encontrado
}

/**
 * @brief Limpa o buffer de entrada (após o uso de scanf ou para entradas de string).
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/**
 * @brief Remove a nova linha ('\n') de uma string lida com fgets, se presente.
 * @param string A string a ser tratada.
 */
void removerNovaLinha(char *string) {
    size_t len = strlen(string);
    if (len > 0 && string[len - 1] == '\n') {
        string[len - 1] = '\0';
    }
}

/**
 * @brief Função para cadastrar os componentes.
 * @param componentes O array para armazenar os componentes.
 * @return O número de componentes cadastrados.
 */
int cadastrarComponentes(Componente componentes[]) {
    int n = 0;
    char resposta[5];

    printf("\n### Cadastro de Componentes da Torre de Resgate ###\n");
    printf("Você pode cadastrar até %d componentes.\n", MAX_COMPONENTES);

    while (n < MAX_COMPONENTES) {
        printf("\n--- Componente %d ---\n", n + 1);

        // Nome do componente
        printf("Nome do Componente (max 29 caracteres): ");
        if (fgets(componentes[n].nome, sizeof(componentes[n].nome), stdin) == NULL) break;
        removerNovaLinha(componentes[n].nome);
        if (strlen(componentes[n].nome) == 0) strcpy(componentes[n].nome, "Componente Generico");

        // Tipo do componente
        printf("Tipo (ex: controle, suporte, propulsao) (max 19 caracteres): ");
        if (fgets(componentes[n].tipo, sizeof(componentes[n].tipo), stdin) == NULL) break;
        removerNovaLinha(componentes[n].tipo);
        if (strlen(componentes[n].tipo) == 0) strcpy(componentes[n].tipo, "Diversos");

        // Prioridade
        printf("Prioridade (1 a 10): ");
        if (scanf("%d", &componentes[n].prioridade) != 1) {
            printf("Prioridade inválida. Usando 5.\n");
            componentes[n].prioridade = 5;
            limparBuffer();
        } else {
            limparBuffer(); // Limpa o buffer após scanf
        }
        if (componentes[n].prioridade < 1 || componentes[n].prioridade > 10) {
            printf("Prioridade fora do intervalo (1-10). Ajustando para 5.\n");
            componentes[n].prioridade = 5;
        }

        n++;

        if (n < MAX_COMPONENTES) {
            printf("\nDeseja cadastrar mais um componente? (s/n): ");
            if (fgets(resposta, sizeof(resposta), stdin) == NULL) break;
            removerNovaLinha(resposta);
            if (tolower(resposta[0]) == 'n') break;
        }
    }

    printf("\nTotal de %d componentes cadastrados.\n", n);
    return n;
}

/**
 * @brief Implementa o menu interativo principal.
 * @param componentes O array de structs Componente.
 * @param tamanho O número de componentes no array.
 */
void menuPrincipal(Componente componentes[], int tamanho) {
    if (tamanho == 0) {
        printf("Nenhum componente cadastrado. Retornando ao menu principal.\n");
        return;
    }

    int opcao;
    Componente copia_componentes[MAX_COMPONENTES];
    long long comparacoes = 0;
    clock_t inicio, fim;
    double tempo_execucao;
    int indice_chave = -1;

    do {
        printf("\n\n### Menu de Estratégia de Montagem ###\n");
        printf("1. Ordenar por Nome (Bubble Sort) - Habilita Busca\n");
        printf("2. Ordenar por Tipo (Insertion Sort)\n");
        printf("3. Ordenar por Prioridade (Selection Sort)\n");
        printf("4. Buscar Componente-Chave (Apenas após a Ordenação por Nome)\n");
        printf("5. Visualizar Componentes Atuais\n");
        printf("0. Sair\n");
        printf("Escolha sua opção: ");

        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = -1; // Opção inválida
        } else {
            limparBuffer();
        }

        // Cria uma cópia do array para garantir que a ordenação original seja preservada
        // ou para permitir que o usuário ordene novamente
        memcpy(copia_componentes, componentes, tamanho * sizeof(Componente));

        switch (opcao) {
            case 1:
                // Ordenação por Nome (Bubble Sort)
                inicio = clock();
                bubbleSortNome(copia_componentes, tamanho, &comparacoes);
                fim = clock();
                tempo_execucao = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
                
                // Atualiza o array principal para manter o estado ordenado para a busca
                memcpy(componentes, copia_componentes, tamanho * sizeof(Componente));
                
                printf("\n✅ Ordenação por Nome (Bubble Sort) Concluída.\n");
                printf("📊 Comparações: %lld\n", comparacoes);
                printf("⏱️ Tempo de Execução: %f segundos\n", tempo_execucao);
                mostrarComponentes(componentes, tamanho);
                indice_chave = -1; // Reset da busca
                break;

            case 2:
                // Ordenação por Tipo (Insertion Sort)
                inicio = clock();
                insertionSortTipo(copia_componentes, tamanho, &comparacoes);
                fim = clock();
                tempo_execucao = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
                
                printf("\n✅ Ordenação por Tipo (Insertion Sort) Concluída.\n");
                printf("📊 Comparações: %lld\n", comparacoes);
                printf("⏱️ Tempo de Execução: %f segundos\n", tempo_execucao);
                mostrarComponentes(copia_componentes, tamanho);
                indice_chave = -1; // Reset da busca
                break;

            case 3:
                // Ordenação por Prioridade (Selection Sort)
                inicio = clock();
                selectionSortPrioridade(copia_componentes, tamanho, &comparacoes);
                fim = clock();
                tempo_execucao = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
                
                printf("\n✅ Ordenação por Prioridade (Selection Sort) Concluída.\n");
                printf("📊 Comparações: %lld\n", comparacoes);
                printf("⏱️ Tempo de Execução: %f segundos\n", tempo_execucao);
                mostrarComponentes(copia_componentes, tamanho);
                indice_chave = -1; // Reset da busca
                break;

            case 4:
                // Busca Binária
                // Verifica se a última ordenação foi por nome, necessária para a Busca Binária
                // A verificação é implícita, pois a busca usa o array 'componentes',
                // que é atualizado apenas pela opção 1.
                
                printf("\n🔍 Buscando Componente-Chave: **%s**\n", CHAVE_BUSCA);
                inicio = clock();
                indice_chave = buscaBinariaPorNome(componentes, tamanho, CHAVE_BUSCA, &comparacoes);
                fim = clock();
                tempo_execucao = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
                
                if (indice_chave != -1) {
                    printf("🎉 Componente-Chave **ENCONTRADO** na posição %d.\n", indice_chave + 1);
                    printf("Montagem Final pode ser Iniciada!\n");
                } else {
                    printf("❌ Componente-Chave **NÃO ENCONTRADO**. A torre não pode ser ativada.\n");
                }
                printf("📊 Comparações na Busca: %lld\n", comparacoes);
                printf("⏱️ Tempo de Execução da Busca: %f segundos\n", tempo_execucao);
                
                // Montagem Final: Visualização e Confirmação
                if (indice_chave != -1) {
                    printf("\n--- Confirmação Visual da Montagem ---\n");
                    mostrarComponentes(componentes, tamanho);
                    printf("--> Componente Chave: **%s** | Tipo: %s | Prioridade: %d\n",
                           componentes[indice_chave].nome, componentes[indice_chave].tipo, componentes[indice_chave].prioridade);
                }
                
                break;
                
            case 5:
                 mostrarComponentes(componentes, tamanho);
                 break;

            case 0:
                printf("\nSaindo do sistema de organização. Boa Fuga!\n");
                break;

            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);
}

/**
 * @brief Função principal do programa.
 */
int main() {
    // Array de structs para armazenar os componentes
    Componente componentes[MAX_COMPONENTES];
    int n_componentes = 0; // Número real de componentes cadastrados

    printf("====================================================\n");
    printf("     🚀 Módulo de Organização de Componentes 🚀\n");
    printf("====================================================\n");

    // 1. Cadastro dos dados
    n_componentes = cadastrarComponentes(componentes);
    
    // 2. Inicia o Menu Principal
    if (n_componentes > 0) {
        menuPrincipal(componentes, n_componentes);
    } else {
        printf("\nNenhum componente foi cadastrado. O programa será encerrado.\n");
    }

    return 0;
}
