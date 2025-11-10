#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da constante para o número de territórios e missões
#define NUM_TERRITORIOS 5
#define MAX_MISSOES 5
#define TAM_MISSAO 100 // Tamanho máximo para a string da missão

/**
 * @brief Estrutura que representa um Território.
 */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---

// Funções de Inicialização e Jogo
void inicializarMapa(Territorio** mapa);
void atribuirMissao(char** missaoDestino, const char* missoes[], int totalMissoes);
void exibirMapa(const Territorio* mapa, int tamanho);
void exibirMissao(const char* missao); // Passagem por valor (cópia do ponteiro)
void simularTurno(Territorio* mapa, int tamanho);
int atacar(Territorio* atacante, Territorio* defensor);
int verificarMissao(const char* missao, const Territorio* mapa, int tamanho); // Passagem por referência
void liberarMemoria(Territorio* mapa, char* missaoJogador);

// -----------------------------------------------------------------------------

/**
 * @brief Função principal do jogo.
 * * Gerencia o ciclo de vida do jogo: inicialização, turno, verificação e limpeza.
 */
int main() {
    // Inicialização do gerador de números aleatórios
    srand(time(NULL));

    // Vetor de strings contendo as missões estratégicas pré-definidas
    const char* missoes[MAX_MISSOES] = {
        "Conquistar o Territorio B e o Territorio D.",
        "Eliminar todas as tropas da cor Azul.",
        "Conquistar 3 territorios consecutivos.",
        "Acumular 15 ou mais tropas em um unico territorio.",
        "Conquistar 4 territorios com 1 ou mais tropas em cada."
    };

    // --- Alocação Dinâmica ---
    
    // Alocação dinâmica para o vetor de territórios (o 'mapa')
    Territorio* mapa = NULL;
    inicializarMapa(&mapa);

    // Alocação dinâmica para armazenar a missão do Jogador 1 (usando ponteiros)
    char* missaoJogador1 = (char*)malloc(TAM_MISSAO * sizeof(char));
    if (missaoJogador1 == NULL) {
        printf("Erro ao alocar memoria para a missao.\n");
        return 1;
    }

    printf("⚔️ **WAR ESTRUTURADO - INÍCIO DO JOGO** ⚔️\n");
    
    // --- Atribuição e Exibição da Missão ---

    // Atribuição da missão (passando o endereço da variável missaoJogador1)
    atribuirMissao(&missaoJogador1, missoes, MAX_MISSOES);
    
    // Exibição da missão (passagem por valor, copiando o valor do ponteiro)
    exibirMissao(missaoJogador1);
    
    printf("\n--- ESTADO INICIAL DO MAPA ---\n");
    exibirMapa(mapa, NUM_TERRITORIOS);

    // --- Simulação do Jogo ---
    
    int vencedor = 0; // Flag para indicar se a missão foi cumprida
    
    // Simulação de 3 turnos de jogo
    for (int turno = 1; turno <= 3; turno++) {
        printf("\n===========================================\n");
        printf("              TURNO %d\n", turno);
        printf("===========================================\n");

        simularTurno(mapa, NUM_TERRITORIOS);

        // Verificação silenciosa da missão (Passagem por referência implícita: mapa)
        vencedor = verificarMissao(missaoJogador1, mapa, NUM_TERRITORIOS);

        if (vencedor) {
            printf("\n🎉🎉🎉 MISSAO CUMPRIDA! O JOGADOR VENCEU! 🎉🎉🎉\n");
            break;
        } else {
            printf("Missao ainda nao cumprida. O jogo continua.\n");
            printf("\n--- MAPA ATUALIZADO ---\n");
            exibirMapa(mapa, NUM_TERRITORIOS);
        }
    }

    // --- Liberação da Memória ---
    liberarMemoria(mapa, missaoJogador1);
    
    printf("\nFim de jogo. Memoria liberada com sucesso.\n");
    
    return 0;
}

// -----------------------------------------------------------------------------
// --- Implementação das Funções Modulares ---
// -----------------------------------------------------------------------------

/**
 * @brief Inicializa o vetor de territórios com dados iniciais.
 * * Usa calloc para alocar e zerar a memória.
 * * @param mapa Ponteiro para o ponteiro do mapa (passagem por referência para alocação).
 */
void inicializarMapa(Territorio** mapa) {
    // Aloca memória para o vetor de 5 territórios e inicializa com zeros
    *mapa = (Territorio*)calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (*mapa == NULL) {
        printf("Erro ao alocar memoria para o mapa.\n");
        exit(1);
    }
    
    // Inicialização dos dados dos territórios (simulação de um estado inicial)
    // Territórios 0, 2, 4 são do "Vermelho"
    strcpy((*mapa)[0].nome, "Territorio A"); strcpy((*mapa)[0].cor, "Vermelho"); (*mapa)[0].tropas = 3;
    strcpy((*mapa)[1].nome, "Territorio B"); strcpy((*mapa)[1].cor, "Azul");     (*mapa)[1].tropas = 2;
    strcpy((*mapa)[2].nome, "Territorio C"); strcpy((*mapa)[2].cor, "Vermelho"); (*mapa)[2].tropas = 5;
    strcpy((*mapa)[3].nome, "Territorio D"); strcpy((*mapa)[3].cor, "Verde");    (*mapa)[3].tropas = 4;
    strcpy((*mapa)[4].nome, "Territorio E"); strcpy((*mapa)[4].cor, "Vermelho"); (*mapa)[4].tropas = 1;

    printf("Mapa inicializado com %d territorios.\n", NUM_TERRITORIOS);
}

/**
 * @brief Sorteia e atribui uma missão para o jogador.
 * * Utiliza rand() para o sorteio e strcpy para a cópia segura.
 * * @param missaoDestino O endereço do ponteiro da missão do jogador (passagem por referência).
 * * @param missoes O vetor de strings contendo as missões disponíveis.
 * * @param totalMissoes O número total de missões no vetor.
 */
void atribuirMissao(char** missaoDestino, const char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    
    // Copia a missão sorteada para a string alocada dinamicamente
    // Garantia de que não haverá overflow na cópia
    strncpy(*missaoDestino, missoes[indiceSorteado], TAM_MISSAO - 1);
    (*missaoDestino)[TAM_MISSAO - 1] = '\0'; // Garantir terminação
}

/**
 * @brief Exibe a missão atual do jogador.
 * * A missão é passada por valor (cópia do ponteiro char*).
 * * @param missao A string da missão a ser exibida.
 */
void exibirMissao(const char* missao) {
    printf("\n📜 **SUA MISSAO ESTRATÉGICA**:\n");
    printf("> %s\n", missao);
}

/**
 * @brief Exibe o estado atual de todos os territórios no mapa.
 * * @param mapa O vetor de structs Territorio.
 * * @param tamanho O número de territórios.
 */
void exibirMapa(const Territorio* mapa, int tamanho) {
    printf("---------------------------------------------------\n");
    printf("| %-15s | %-8s | %-6s |\n", "NOME", "COR", "TROPAS");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < tamanho; i++) {
        printf("| %-15s | %-8s | %6d |\n", 
               mapa[i].nome, 
               mapa[i].cor, 
               mapa[i].tropas);
    }
    printf("---------------------------------------------------\n");
}

/**
 * @brief Simula um único ataque entre dois territórios pré-definidos para demonstração.
 * * @param atacante Ponteiro para o território atacante.
 * * @param defensor Ponteiro para o território defensor.
 * * @return 1 se a cor do atacante mudou, 0 caso contrário.
 */
int atacar(Territorio* atacante, Territorio* defensor) {
    // Validação: Só pode atacar se as cores forem diferentes
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Ataque cancelado: O Territorio %s ja pertence a cor %s.\n", defensor->nome, atacante->cor);
        return 0;
    }

    // Simulação da rolagem de dados (valores entre 1 e 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("\n--> ATAQUE: %s (%d tropas) vs %s (%d tropas) <--\n", 
           atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
    printf("    Dados: Atacante (%d) | Defensor (%d)\n", dadoAtacante, dadoDefensor);

    int corMudou = 0;

    if (dadoAtacante > dadoDefensor) {
        printf("    Vitoria! %s conquistou o territorio %s.\n", atacante->nome, defensor->nome);
        
        // Transferência de cor e tropas
        int tropasTransferidas = defensor->tropas / 2;
        
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = tropasTransferidas;
        
        atacante->tropas += (defensor->tropas - tropasTransferidas); // Ajuste do atacante (as outras tropas do defensor são eliminadas)
        
        corMudou = 1;
    } else {
        printf("    Defesa bem-sucedida! %s manteve o territorio.\n", defensor->nome);
        
        // Atacante perde uma tropa
        if (atacante->tropas > 1) {
            atacante->tropas--;
            printf("    %s perdeu 1 tropa (Tropas restantes: %d).\n", atacante->nome, atacante->tropas);
        }
    }
    return corMudou;
}

/**
 * @brief Simula um turno de ataque para fins de demonstração.
 * * @param mapa O vetor de structs Territorio.
 * * @param tamanho O número de territórios.
 */
void simularTurno(Territorio* mapa, int tamanho) {
    // Ataque 1: Territorio C (Vermelho) ataca Territorio D (Verde)
    // Índice 2 ataca Índice 3
    printf("\n--- Tentativa de Ataque 1 ---\n");
    atacar(&mapa[2], &mapa[3]);

    // Ataque 2: Territorio B (Azul) ataca Territorio E (Vermelho)
    // Índice 1 ataca Índice 4
    printf("\n--- Tentativa de Ataque 2 ---\n");
    atacar(&mapa[1], &mapa[4]);
}

/**
 * @brief Verifica se a missão do jogador foi cumprida.
 * * Implementa uma lógica simples baseada nas missões pré-definidas.
 * * @param missao A string da missão do jogador (Passagem por referência implícita via mapa).
 * * @param mapa O vetor de structs Territorio.
 * * @param tamanho O número de territórios.
 * * @return 1 se a missão foi cumprida, 0 caso contrário.
 */
int verificarMissao(const char* missao, const Territorio* mapa, int tamanho) {
    // A cor do jogador 1 é considerada "Vermelho" para esta verificação simples
    const char* corJogador = "Vermelho"; 
    int territoriosJogador = 0;
    
    // --- Lógica simples de verificação ---
    
    // Missão 1: "Conquistar o Territorio B e o Territorio D."
    if (strstr(missao, "Territorio B") != NULL && strstr(missao, "Territorio D") != NULL) {
        int bConquistado = (strcmp(mapa[1].cor, corJogador) == 0); // Territorio B é índice 1
        int dConquistado = (strcmp(mapa[3].cor, corJogador) == 0); // Territorio D é índice 3
        return (bConquistado && dConquistado) ? 1 : 0;
    }

    // Missão 2: "Eliminar todas as tropas da cor Azul."
    if (strstr(missao, "cor Azul") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0) {
                return 0; // Encontrou um território Azul, missão não cumprida
            }
        }
        return 1; // Nenhuma cor Azul restante
    }
    
    // Missão 3: "Conquistar 3 territorios consecutivos." (Lógica Simplificada)
    if (strstr(missao, "3 territorios consecutivos") != NULL) {
        for (int i = 0; i < tamanho - 2; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 &&
                strcmp(mapa[i+1].cor, corJogador) == 0 &&
                strcmp(mapa[i+2].cor, corJogador) == 0) {
                return 1;
            }
        }
        return 0;
    }
    
    // Missão 4: "Acumular 15 ou mais tropas em um unico territorio."
    if (strstr(missao, "15 ou mais tropas") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas >= 15 && strcmp(mapa[i].cor, corJogador) == 0) {
                return 1;
            }
        }
        return 0;
    }

    // Missão 5: "Conquistar 4 territorios com 1 ou mais tropas em cada."
    if (strstr(missao, "4 territorios") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 1) {
                territoriosJogador++;
            }
        }
        return (territoriosJogador >= 4) ? 1 : 0;
    }

    return 0; // Missão desconhecida ou não cumprida
}

/**
 * @brief Libera a memória alocada dinamicamente.
 * * Garante que não haja vazamentos de memória (memory leaks).
 * * @param mapa O ponteiro para o vetor de territórios.
 * * @param missaoJogador O ponteiro para a string da missão.
 */
void liberarMemoria(Territorio* mapa, char* missaoJogador) {
    if (mapa != NULL) {
        free(mapa);
        mapa = NULL;
    }
    if (missaoJogador != NULL) {
        free(missaoJogador);
        missaoJogador = NULL;
    }
}
