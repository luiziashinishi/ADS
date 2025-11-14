#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- Constantes e Estruturas ---

// Constantes para Hash
#define TAMANHO_HASH 7 // Tamanho primo para a tabela hash
#define MAX_PISTAS 10  // Número máximo de pistas que a BST pode armazenar
#define MAX_NOME 50

// 1. Estrutura para os Cômodos (Nó da Árvore Binária da Mansão)
typedef struct Comodo {
    char nome[MAX_NOME];
    struct Comodo *esquerda;
    struct Comodo *direita;
} Comodo;

// 2. Estrutura para as Pistas Coletadas (Nó da Árvore BST)
typedef struct PistaNode {
    char nome_pista[MAX_NOME];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// 3. Estrutura para a Tabela Hash (Associação Pista -> Suspeito)
typedef struct HashNode {
    char pista[MAX_NOME];
    char suspeito[MAX_NOME];
    struct HashNode *proximo; // Tratamento de colisão por encadeamento
} HashNode;

// --- Estruturas Globais ---
PistaNode *raizPistas = NULL; // Raiz da BST de pistas
HashNode *tabelaHash[TAMANHO_HASH]; // Tabela Hash

// --- Funções de Cômodos (Árvore Binária) ---

/**
 * @brief Cria dinamicamente um novo cômodo (nó da árvore binária da mansão).
 * @param nome O nome do cômodo.
 * @return Ponteiro para o novo cômodo alocado.
 */
Comodo *criarSala(const char *nome) {
    Comodo *novoComodo = (Comodo *)malloc(sizeof(Comodo));
    if (novoComodo == NULL) {
        perror("Erro de alocação de memória para Comodo");
        exit(EXIT_FAILURE);
    }
    strncpy(novoComodo->nome, nome, MAX_NOME - 1);
    novoComodo->nome[MAX_NOME - 1] = '\0';
    novoComodo->esquerda = NULL;
    novoComodo->direita = NULL;
    return novoComodo;
}

/**
 * @brief Associa uma pista a um cômodo com base no nome do cômodo.
 * As pistas são estáticas, conforme requisito.
 * @param nomeComodo Nome do cômodo atual.
 * @param pista_out Buffer de saída para a string da pista.
 */
void obterPistaDoComodo(const char *nomeComodo, char *pista_out) {
    // Regras codificadas para as pistas
    if (strcmp(nomeComodo, "Sala Principal") == 0) {
        strcpy(pista_out, "Relogio quebrado");
    } else if (strcmp(nomeComodo, "Escritorio") == 0) {
        strcpy(pista_out, "Recibo de viagem");
    } else if (strcmp(nomeComodo, "Cozinha") == 0) {
        strcpy(pista_out, "Faca de prata");
    } else if (strcmp(nomeComodo, "Quarto Mestre") == 0) {
        strcpy(pista_out, "Carta de amor");
    } else if (strcmp(nomeComodo, "Jardim de Inverno") == 0) {
        strcpy(pista_out, "Pegadas na lama");
    } else if (strcmp(nomeComodo, "Biblioteca") == 0) {
        strcpy(pista_out, "Livro sobre venenos");
    } else {
        strcpy(pista_out, "Nenhuma pista encontrada");
    }
}

// --- Funções da BST de Pistas ---

/**
 * @brief Insere uma nova pista na Árvore Binária de Busca (BST).
 * @param raiz A raiz atual da subárvore.
 * @param nomePista O nome da pista a ser inserida.
 * @return A nova raiz da subárvore após a inserção.
 */
PistaNode *inserirPista(PistaNode *raiz, const char *nomePista) {
    if (raiz == NULL) {
        // Cria um novo nó
        PistaNode *novo = (PistaNode *)malloc(sizeof(PistaNode));
        if (novo == NULL) {
            perror("Erro de alocação de memória para PistaNode");
            return NULL;
        }
        strncpy(novo->nome_pista, nomePista, MAX_NOME - 1);
        novo->nome_pista[MAX_NOME - 1] = '\0';
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    int comparacao = strcmp(nomePista, raiz->nome_pista);

    if (comparacao < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, nomePista);
    } else if (comparacao > 0) {
        raiz->direita = inserirPista(raiz->direita, nomePista);
    }
    // Se comparacao == 0, a pista já existe, não faz nada.

    return raiz;
}

/**
 * @brief Percorre a BST em ordem (In-Order) para listar as pistas coletadas.
 * @param raiz A raiz da BST de pistas.
 */
void listarPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        listarPistas(raiz->esquerda);
        printf("- %s\n", raiz->nome_pista);
        listarPistas(raiz->direita);
    }
}

// --- Funções da Tabela Hash ---

/**
 * @brief Função de hashing simples (soma de valores ASCII)
 * @param chave A string (nome da pista) para calcular o hash.
 * @return O índice da tabela hash.
 */
int funcaoHash(const char *chave) {
    unsigned long hash = 0;
    int c;
    while ((c = *chave++)) {
        hash = hash + c;
    }
    return hash % TAMANHO_HASH;
}

/**
 * @brief Insere a associação pista/suspeito na tabela hash.
 * Se a pista já existir, o suspeito é atualizado.
 * @param pista O nome da pista (chave).
 * @param suspeito O nome do suspeito (valor).
 */
void inserirNaHash(const char *pista, const char *suspeito) {
    int indice = funcaoHash(pista);
    HashNode *novoNode;
    HashNode *atual = tabelaHash[indice];

    // Verifica se a chave (pista) já existe
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            // Pista já existe, apenas atualiza o suspeito (Embora não deva acontecer neste projeto)
            strncpy(atual->suspeito, suspeito, MAX_NOME - 1);
            atual->suspeito[MAX_NOME - 1] = '\0';
            return;
        }
        atual = atual->proximo;
    }

    // Cria e insere um novo nó no início da lista encadeada (colisão)
    novoNode = (HashNode *)malloc(sizeof(HashNode));
    if (novoNode == NULL) {
        perror("Erro de alocação de memória para HashNode");
        return;
    }
    strncpy(novoNode->pista, pista, MAX_NOME - 1);
    novoNode->pista[MAX_NOME - 1] = '\0';
    strncpy(novoNode->suspeito, suspeito, MAX_NOME - 1);
    novoNode->suspeito[MAX_NOME - 1] = '\0';

    novoNode->proximo = tabelaHash[indice];
    tabelaHash[indice] = novoNode;
}

/**
 * @brief Consulta o suspeito associado a uma pista na tabela hash.
 * @param pista O nome da pista a ser consultada.
 * @param suspeito_out Buffer de saída para o nome do suspeito.
 * @return 1 se encontrado, 0 caso contrário.
 */
int encontrarSuspeito(const char *pista, char *suspeito_out) {
    int indice = funcaoHash(pista);
    HashNode *atual = tabelaHash[indice];

    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            strncpy(suspeito_out, atual->suspeito, MAX_NOME - 1);
            suspeito_out[MAX_NOME - 1] = '\0';
            return 1;
        }
        atual = atual->proximo;
    }
    return 0; // Não encontrado
}

// --- Lógica de Jogo e Exploração ---

/**
 * @brief Implementa a lógica de exploração de cômodos, coleta de pistas e armazenamento.
 * @param atual O cômodo atual na mansão (nó da árvore binária).
 */
void explorarSalas(Comodo *atual) {
    char acao[10];
    char pista_str[MAX_NOME];

    while (atual != NULL) {
        printf("\nVocê está em: 📍 **%s**\n", atual->nome);

        // 1. Identificar e exibir a pista
        obterPistaDoComodo(atual->nome, pista_str);
        if (strcmp(pista_str, "Nenhuma pista encontrada") != 0) {
            printf("🔍 Pista encontrada! -> **%s**\n", pista_str);

            // 2. Armazenar a pista na BST (se ainda não coletada)
            PistaNode *anterior = raizPistas;
            raizPistas = inserirPista(raizPistas, pista_str);
            if (anterior != raizPistas || (anterior == raizPistas && strcmp(pista_str, "Nenhuma pista encontrada") != 0)) {
                 printf("💾 Pista adicionada ao seu Caderno de Evidências.\n");
            }
        } else {
            printf("Nada de relevante por aqui.\n");
        }
        
        // 3. Interação do jogador
        printf("\nAções disponíveis: [e] Esquerda, [d] Direita, [s] Sair\n");
        printf("Escolha o próximo caminho: ");
        if (scanf("%9s", acao) != 1) {
            // Limpa o buffer em caso de erro na entrada
            while(getchar() != '\n');
            continue; 
        }

        // Converte para minúsculas
        char escolha = tolower(acao[0]);
        while(getchar() != '\n'); // Limpa o buffer

        if (escolha == 's') {
            printf("🚪 Você decide que é hora de confrontar o culpado. Fim da exploração.\n");
            return;
        } else if (escolha == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("❌ Não há cômodo à esquerda. Fique atento!\n");
            }
        } else if (escolha == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("❌ Não há cômodo à direita. Fique atento!\n");
            }
        } else {
            printf("Comando inválido. Tente novamente.\n");
        }
    }
}

/**
 * @brief Conta recursivamente quantas pistas na BST apontam para o suspeito final.
 * @param raiz A raiz da BST de pistas coletadas.
 * @param suspeitoAcusado O nome do suspeito.
 * @param contador Ponteiro para o contador de pistas (usado para o retorno).
 */
void contarPistasPorSuspeito(PistaNode *raiz, const char *suspeitoAcusado, int *contador) {
    if (raiz == NULL) return;

    // Recursão In-Order
    contarPistasPorSuspeito(raiz->esquerda, suspeitoAcusado, contador);

    char suspeito_encontrado[MAX_NOME];
    // Consulta a Hash
    if (encontrarSuspeito(raiz->nome_pista, suspeito_encontrado)) {
        if (strcmp(suspeito_encontrado, suspeitoAcusado) == 0) {
            (*contador)++;
            printf("  ✔️ Pista '%s' aponta para %s.\n", raiz->nome_pista, suspeitoAcusado);
        }
    }

    contarPistasPorSuspeito(raiz->direita, suspeitoAcusado, contador);
}


/**
 * @brief Conduz à fase de julgamento final: acusa, verifica e exibe o desfecho.
 * @param suspeitos Array de nomes de suspeitos válidos.
 * @param numSuspeitos O tamanho do array de suspeitos.
 */
void verificarSuspeitoFinal(const char **suspeitos, int numSuspeitos) {
    char acusacao[MAX_NOME];
    int pistas_suficientes = 0;
    int pistas_coletadas = 0;

    printf("\n\n======================================================\n");
    printf("         ⚖️  FASE DE JULGAMENTO FINAL ⚖️\n");
    printf("======================================================\n");

    // 1. Listar pistas coletadas
    printf("\nSeu Caderno de Evidências (Pistas Coletadas - BST Ordenada):\n");
    listarPistas(raizPistas);
    printf("\nSuspeitos Válidos:\n");
    for (int i = 0; i < numSuspeitos; i++) {
        printf("- %s\n", suspeitos[i]);
    }
    printf("------------------------------------------------------\n");

    // 2. Solicitar acusação
    printf("Quem você acusa como culpado? (Digite o nome): ");
    if (fgets(acusacao, MAX_NOME, stdin) == NULL) return;
    
    // Remover nova linha
    size_t len = strlen(acusacao);
    if (len > 0 && acusacao[len - 1] == '\n') {
        acusacao[len - 1] = '\0';
    }

    printf("\n🚨 Você acusa: **%s**!\n", acusacao);

    // 3. Verificar o suporte das pistas (usando a BST e a Hash)
    printf("Iniciando a verificação das evidências:\n");
    contarPistasPorSuspeito(raizPistas, acusacao, &pistas_coletadas);

    // 4. Exibir o desfecho
    printf("\nResultado da Análise:\n");
    printf("Total de Pistas Coletadas que Apontam para %s: **%d**\n", acusacao, pistas_coletadas);

    if (pistas_coletadas >= 2) {
        printf("\n🎉 SUCESSO! Você tem **%d** pistas. A acusação é forte e sustentada!\n", pistas_coletadas);
    } else {
        printf("\n❌ FRACASSO. Você tem apenas **%d** pistas. A evidência é fraca e o caso foi arquivado.\n", pistas_coletadas);
    }
    printf("======================================================\n");
}

// --- Funções de Limpeza de Memória ---

void liberarComodos(Comodo *raiz) {
    if (raiz != NULL) {
        liberarComodos(raiz->esquerda);
        liberarComodos(raiz->direita);
        free(raiz);
    }
}

void liberarPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

void liberarHash() {
    HashNode *atual, *temp;
    for (int i = 0; i < TAMANHO_HASH; i++) {
        atual = tabelaHash[i];
        while (atual != NULL) {
            temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        tabelaHash[i] = NULL;
    }
}

// --- Função Principal ---

int main() {
    // Definindo suspeitos e suas pistas (de forma codificada)
    const char *SUSPEITOS[] = {"Mordomo", "Jardineiro", "Dona da Casa", "Professor"};
    int numSuspeitos = sizeof(SUSPEITOS) / sizeof(SUSPEITOS[0]);

    // Inicialização da Tabela Hash com as associações Pista -> Suspeito
    inserirNaHash("Relogio quebrado", "Mordomo");
    inserirNaHash("Recibo de viagem", "Dona da Casa");
    inserirNaHash("Faca de prata", "Jardineiro");
    inserirNaHash("Carta de amor", "Professor");
    inserirNaHash("Pegadas na lama", "Jardineiro");
    inserirNaHash("Livro sobre venenos", "Dona da Casa");
    // Adicionar mais associações, se necessário
    inserirNaHash("Vidro estilhaçado", "Professor");
    inserirNaHash("Chave mestra", "Mordomo");


    // 1. Montagem do Mapa da Mansão (Árvore Binária Fixa)
    Comodo *mansao = criarSala("Sala Principal");
    mansao->esquerda = criarSala("Escritorio");
    mansao->direita = criarSala("Cozinha");
    mansao->esquerda->esquerda = criarSala("Quarto Mestre");
    mansao->esquerda->direita = criarSala("Jardim de Inverno");
    mansao->direita->esquerda = criarSala("Biblioteca");
    mansao->direita->direita = criarSala("Saida dos Fundos");
    
    // --- Lógica de Jogo ---

    printf("==================================================\n");
    printf("   🕵️  Detective Quest - Sistema de Evidências\n");
    printf("==================================================\n");
    
    // Limpar buffer antes de iniciar a exploração
    while(getchar() != '\n' && getchar() != EOF);

    // 2. Iniciar a Exploração Interativa
    explorarSalas(mansao);

    // 3. Julgamento Final
    verificarSuspeitoFinal(SUSPEITOS, numSuspeitos);

    // 4. Limpeza de Memória
    liberarComodos(mansao);
    liberarPistas(raizPistas);
    liberarHash();

    return 0;
}
