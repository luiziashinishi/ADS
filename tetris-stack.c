#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Definições de Estruturas e Constantes ---

// Atributos de cada peça
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;   // Ordem de criação
} Peca;

// Estrutura para a Fila Circular
#define MAX_FILA 5
typedef struct {
    Peca pecas[MAX_FILA];
    int frente;
    int tras;
    int contador; // Número atual de peças na fila
} FilaCircular;

// Estrutura para a Pilha
#define MAX_PILHA 3
typedef struct {
    Peca pecas[MAX_PILHA];
    int topo; // Índice do topo da pilha (-1 se vazia)
} Pilha;

// Variável global para gerar IDs únicos das peças
static int ID_GERAL = 0;

// --- Funções de Inicialização e Geração ---

/**
 * @brief Inicializa a estrutura da Fila Circular.
 * @param f Ponteiro para a FilaCircular a ser inicializada.
 */
void inicializarFila(FilaCircular *f) {
    f->frente = 0;
    f->tras = -1;
    f->contador = 0;
}

/**
 * @brief Inicializa a estrutura da Pilha.
 * @param p Ponteiro para a Pilha a ser inicializada.
 */
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

/**
 * @brief Gera uma nova peça com nome aleatório e ID único.
 * @return A nova peça gerada.
 */
Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % (sizeof(tipos) / sizeof(tipos[0]));

    nova.nome = tipos[indice];
    nova.id = ID_GERAL++; // Atribui e incrementa o ID global
    return nova;
}

// --- Funções da Fila Circular ---

/**
 * @brief Verifica se a fila está cheia.
 * @param f Ponteiro para a FilaCircular.
 * @return 1 se cheia, 0 caso contrário.
 */
int filaCheia(FilaCircular *f) {
    return f->contador == MAX_FILA;
}

/**
 * @brief Verifica se a fila está vazia.
 * @param f Ponteiro para a FilaCircular.
 * @return 1 se vazia, 0 caso contrário.
 */
int filaVazia(FilaCircular *f) {
    return f->contador == 0;
}

/**
 * @brief Insere uma peça no final da fila (enqueue).
 * @param f Ponteiro para a FilaCircular.
 * @param peca A peça a ser inserida.
 * @return 1 se sucesso, 0 se a fila está cheia.
 */
int enfileirar(FilaCircular *f, Peca peca) {
    if (filaCheia(f)) {
        return 0; // Fila cheia
    }
    f->tras = (f->tras + 1) % MAX_FILA;
    f->pecas[f->tras] = peca;
    f->contador++;
    return 1;
}

/**
 * @brief Remove a peça da frente da fila (dequeue).
 * @param f Ponteiro para a FilaCircular.
 * @param peca Ponteiro onde a peça removida será armazenada.
 * @return 1 se sucesso, 0 se a fila está vazia.
 */
int desenfileirar(FilaCircular *f, Peca *peca) {
    if (filaVazia(f)) {
        return 0; // Fila vazia
    }
    *peca = f->pecas[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->contador--;
    return 1;
}

/**
 * @brief Pega a peça da frente da fila sem removê-la (peek).
 * @param f Ponteiro para a FilaCircular.
 * @param peca Ponteiro onde a peça da frente será armazenada.
 * @return 1 se sucesso, 0 se a fila está vazia.
 */
int pecaDaFrente(FilaCircular *f, Peca *peca) {
    if (filaVazia(f)) {
        return 0;
    }
    *peca = f->pecas[f->frente];
    return 1;
}

// --- Funções da Pilha ---

/**
 * @brief Verifica se a pilha está cheia.
 * @param p Ponteiro para a Pilha.
 * @return 1 se cheia, 0 caso contrário.
 */
int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

/**
 * @brief Verifica se a pilha está vazia.
 * @param p Ponteiro para a Pilha.
 * @return 1 se vazia, 0 caso contrário.
 */
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

/**
 * @brief Insere uma peça no topo da pilha (push).
 * @param p Ponteiro para a Pilha.
 * @param peca A peça a ser inserida.
 * @return 1 se sucesso, 0 se a pilha está cheia.
 */
int empilhar(Pilha *p, Peca peca) {
    if (pilhaCheia(p)) {
        return 0; // Pilha cheia
    }
    p->topo++;
    p->pecas[p->topo] = peca;
    return 1;
}

/**
 * @brief Remove a peça do topo da pilha (pop).
 * @param p Ponteiro para a Pilha.
 * @param peca Ponteiro onde a peça removida será armazenada.
 * @return 1 se sucesso, 0 se a pilha está vazia.
 */
int desempilhar(Pilha *p, Peca *peca) {
    if (pilhaVazia(p)) {
        return 0; // Pilha vazia
    }
    *peca = p->pecas[p->topo];
    p->topo--;
    return 1;
}

/**
 * @brief Pega a peça do topo da pilha sem removê-la (peek).
 * @param p Ponteiro para a Pilha.
 * @param peca Ponteiro onde a peça do topo será armazenada.
 * @return 1 se sucesso, 0 se a pilha está vazia.
 */
int pecaDoTopo(Pilha *p, Peca *peca) {
    if (pilhaVazia(p)) {
        return 0;
    }
    *peca = p->pecas[p->topo];
    return 1;
}

// --- Funções de Exibição e Coreografia ---

/**
 * @brief Exibe o estado atual da Fila e da Pilha.
 * @param f Ponteiro para a FilaCircular.
 * @param p Ponteiro para a Pilha.
 */
void exibirEstado(FilaCircular *f, Pilha *p) {
    printf("\n======================================================\n");
    printf("                  ESTADO ATUAL\n");
    printf("======================================================\n");

    // Exibir Fila
    printf("👉 Fila de Peças (Cap: %d | Cont: %d): ", MAX_FILA, f->contador);
    if (filaVazia(f)) {
        printf("Vazia\n");
    } else {
        printf("[");
        for (int i = 0; i < f->contador; i++) {
            int indice_atual = (f->frente + i) % MAX_FILA;
            printf(" %c %d ", f->pecas[indice_atual].nome, f->pecas[indice_atual].id);
            if (i < f->contador - 1) {
                printf("] [");
            }
        }
        printf("]\n");
    }

    // Exibir Pilha
    printf("📦 Pilha de Reserva (Cap: %d | Cont: %d | Topo -> Base): ", MAX_PILHA, p->topo + 1);
    if (pilhaVazia(p)) {
        printf("Vazia\n");
    } else {
        printf("[");
        for (int i = p->topo; i >= 0; i--) {
            printf(" %c %d ", p->pecas[i].nome, p->pecas[i].id);
            if (i > 0) {
                printf("] [");
            }
        }
        printf("]\n");
    }
    printf("======================================================\n");
}

/**
 * @brief Mostra o menu de opções.
 */
void exibirMenu() {
    printf("\n### Ações Estratégicas ###\n");
    printf("1. 🕹️ **Jogar Peça** (Remove da frente da Fila)\n");
    printf("2. 💾 **Reservar Peça** (Fila -> Pilha, gera nova peça na Fila)\n");
    printf("3. ♻️ **Usar Peça Reservada** (Remove do topo da Pilha)\n");
    printf("4. 🔄 **Trocar Peça Atual** (Frente da Fila <-> Topo da Pilha)\n");
    printf("5. 🔀 **Troca Múltipla** (3 primeiras Fila <-> 3 Pilha)\n");
    printf("0. 🚪 **Sair**\n");
    printf("Escolha uma opção: ");
}

/**
 * @brief Tenta enfileirar uma nova peça se a fila não estiver cheia.
 * @param f Ponteiro para a FilaCircular.
 * @param motivo String descrevendo a ação que disparou a geração.
 */
void tentarGerarNovaPeca(FilaCircular *f, const char *motivo) {
    if (!filaCheia(f)) {
        Peca nova = gerarPeca();
        enfileirar(f, nova);
        printf("... Peça [%c %d] gerada automaticamente e adicionada ao final da Fila (%s).\n", nova.nome, nova.id, motivo);
    }
}

// --- Funções de Ação (Requisitos Funcionais) ---

/**
 * @brief Implementa a ação de jogar uma peça (dequeue + tentarGerarNovaPeca).
 * @param f Ponteiro para a FilaCircular.
 */
void jogarPeca(FilaCircular *f) {
    Peca peca_jogada;
    if (desenfileirar(f, &peca_jogada)) {
        printf("Ação: Peça jogada da Fila: [%c %d].\n", peca_jogada.nome, peca_jogada.id);
        tentarGerarNovaPeca(f, "Jogada"); // Gera nova peça na vaga aberta
    } else {
        printf("Ação: ❌ Fila de peças está vazia. Nenhuma peça para jogar.\n");
    }
}

/**
 * @brief Implementa a ação de reservar uma peça (Fila -> Pilha + tentarGerarNovaPeca).
 * @param f Ponteiro para a FilaCircular.
 * @param p Ponteiro para a Pilha.
 */
void reservarPeca(FilaCircular *f, Pilha *p) {
    Peca peca_reservar;
    if (pilhaCheia(p)) {
        printf("Ação: ❌ Pilha de reserva está cheia (máx %d). Não é possível reservar mais peças.\n", MAX_PILHA);
        return;
    }
    if (desenfileirar(f, &peca_reservar)) {
        empilhar(p, peca_reservar);
        printf("Ação: Peça [%c %d] reservada (Fila -> Pilha).\n", peca_reservar.nome, peca_reservar.id);
        tentarGerarNovaPeca(f, "Reserva"); // Gera nova peça na vaga aberta
    } else {
        printf("Ação: ❌ Fila de peças está vazia. Nenhuma peça para reservar.\n");
    }
}

/**
 * @brief Implementa a ação de usar uma peça reservada (pop).
 * @param p Ponteiro para a Pilha.
 */
void usarPecaReservada(Pilha *p) {
    Peca peca_usada;
    if (desempilhar(p, &peca_usada)) {
        printf("Ação: Peça reservada [%c %d] usada (Removida da Pilha).\n", peca_usada.nome, peca_usada.id);
    } else {
        printf("Ação: ❌ Pilha de reserva está vazia. Nenhuma peça para usar.\n");
    }
}

/**
 * @brief Implementa a troca da peça da frente da Fila com a peça do Topo da Pilha.
 * @param f Ponteiro para a FilaCircular.
 * @param p Ponteiro para a Pilha.
 */
void trocarPecaAtual(FilaCircular *f, Pilha *p) {
    Peca peca_frente, peca_topo;

    if (filaVazia(f) || pilhaVazia(p)) {
        printf("Ação: ❌ Não foi possível realizar a troca. A Fila ou a Pilha está vazia.\n");
        return;
    }

    // 1. Obter as peças (sem remover)
    pecaDaFrente(f, &peca_frente);
    pecaDoTopo(p, &peca_topo);

    // 2. Realizar a troca nos respectivos locais
    // Fila: sobrescreve a peca da frente
    f->pecas[f->frente] = peca_topo;

    // Pilha: sobrescreve a peca do topo
    p->pecas[p->topo] = peca_frente;

    printf("Ação: Troca de peças realizada.\n");
    printf("... Fila recebeu: [%c %d] | Pilha recebeu: [%c %d].\n", peca_topo.nome, peca_topo.id, peca_frente.nome, peca_frente.id);
}

/**
 * @brief Implementa a troca em bloco das 3 primeiras peças da Fila com as 3 peças da Pilha.
 * @param f Ponteiro para a FilaCircular.
 * @param p Ponteiro para a Pilha.
 */
void trocaMultipla(FilaCircular *f, Pilha *p) {
    if (f->contador < 3 || p->topo + 1 < 3) {
        printf("Ação: ❌ Troca múltipla não pode ser realizada. Fila precisa de no mínimo 3 (%d), Pilha precisa de no mínimo 3 (%d).\n",
               f->contador, p->topo + 1);
        return;
    }

    Peca temp_peca;
    int indice_fila, indice_pilha;

    printf("Ação: Troca em bloco das 3 primeiras peças da Fila com as 3 da Pilha.\n");

    // A Pilha tem tamanho MAX_PILHA=3, logo seus índices são 0, 1, 2.
    // O topo é p->topo = 2.

    for (int i = 0; i < 3; i++) {
        // Fila: A primeira peça da fila é sempre f->frente.
        // As 3 primeiras peças são f->frente, (f->frente + 1) % MAX_FILA, (f->frente + 2) % MAX_FILA.
        indice_fila = (f->frente + i) % MAX_FILA;

        // Pilha: O elemento "i" da base (0) para o topo (2) é no índice "i".
        // Para que o topo da pilha (p->pecas[p->topo]) vá para a frente da fila (f->pecas[f->frente]),
        // a iteração deve ser cuidadosa.
        // Vamos usar o índice p->topo - i.
        indice_pilha = p->topo - i;

        // Troca de valores: (Fila[i] <-> Pilha[i])
        temp_peca = f->pecas[indice_fila];
        f->pecas[indice_fila] = p->pecas[indice_pilha];
        p->pecas[indice_pilha] = temp_peca;
    }

    printf("... Troca concluída. As 3 peças foram alternadas.\n");
}

// --- Função Principal (Main) ---

int main() {
    // Inicialização do gerador de números aleatórios para gerarPeca()
    srand(time(NULL));

    FilaCircular fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // 1. Inicializar a fila com 5 elementos
    printf("Iniciando o Gerenciador de Peças...\n");
    for (int i = 0; i < MAX_FILA; i++) {
        enfileirar(&fila, gerarPeca());
    }
    printf("Fila inicializada com %d peças. Pilha vazia.\n", MAX_FILA);

    int opcao;
    do {
        exibirEstado(&fila, &pilha);
        exibirMenu();

        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer em caso de entrada inválida
            while (getchar() != '\n');
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                reservarPeca(&fila, &pilha);
                break;
            case 3:
                usarPecaReservada(&pilha);
                break;
            case 4:
                trocarPecaAtual(&fila, &pilha);
                break;
            case 5:
                trocaMultipla(&fila, &pilha);
                break;
            case 0:
                printf("\nEncerrando o Gerenciador de Peças. Tchau!\n");
                break;
            default:
                printf("\n⚠️ Opção inválida. Digite um número de 0 a 5.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
