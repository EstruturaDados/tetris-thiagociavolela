/*
    ============================================================================
                        DESAFIO TETRIS STACK – NÍVEL NOVATO
                        Fila Circular de Peças Futuras (5 posições)
    ============================================================================

    Objetivo:
    - Implementar uma fila circular de 5 peças do Tetris.
    - Permitir visualizar, remover (jogar) e inserir automaticamente novas peças.

    Funcionalidades:
    ✔ Inicialização automática da fila
    ✔ Remover peça da frente (dequeue)
    ✔ Inserir nova peça no final (enqueue)
    ✔ Visualizar estado atual
    ✔ Fila circular reaproveitando espaço

    Conceitos utilizados:
    - Struct
    - Vetor como fila circular
    - Modularização (funções separadas)
    - Menu interativo
    - Aleatoriedade simples

    ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_FILA 5

// ============================================================================
// STRUCT DA PEÇA
// ============================================================================
typedef struct {
    int id;
    char nome[3];  // "I", "O", "T", "L", etc.
} Peca;

// ============================================================================
// PROTÓTIPOS
// ============================================================================
void inicializarFila(Peca fila[], int* frente, int* tras);
Peca gerarPeca();
void enqueue(Peca fila[], int* tras, int* frente, Peca novaPeca);
Peca dequeue(Peca fila[], int* frente, int* tras);
void exibirFila(Peca fila[], int frente, int tras);

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================
int main() {
    srand(time(NULL));

    Peca fila[TAM_FILA];
    int frente = 0;
    int tras = 0;

    inicializarFila(fila, &frente, &tras);

    int opcao;
    do {
        printf("\n=================== TETRIS STACK – NÍVEL NOVATO ===================\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Gerar nova peça (enqueue)\n");
        printf("3 - Visualizar fila\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = dequeue(fila, &frente, &tras);
                printf("\nPeça jogada: ID %d | Tipo %s\n", jogada.id, jogada.nome);
                break;
            }

            case 2: {
                Peca nova = gerarPeca();
                enqueue(fila, &tras, &frente, nova);
                printf("\nNova peça inserida: ID %d | Tipo %s\n", nova.id, nova.nome);
                break;
            }

            case 3:
                exibirFila(fila, frente, tras);
                break;

            case 0:
                printf("\nEncerrando o jogo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// ============================================================================
// INICIALIZA FILA COM 5 PEÇAS
// ============================================================================
void inicializarFila(Peca fila[], int* frente, int* tras) {
    *frente = 0;
    *tras = 0;

    for (int i = 0; i < TAM_FILA; i++) {
        fila[i] = gerarPeca();
        *tras = (*tras + 1) % TAM_FILA;
    }
}

// ============================================================================
// GERAR UMA PEÇA AUTOMÁTICA
// ============================================================================
Peca gerarPeca() {
    Peca p;
    p.id = rand() % 1000;  // ID aleatório

    const char* formas[] = {"I", "O", "T", "L", "J", "S", "Z"};
    strcpy(p.nome, formas[rand() % 7]);

    return p;
}

// ============================================================================
// ENQUEUE – INSERIR NO FINAL DA FILA
// ============================================================================
void enqueue(Peca fila[], int* tras, int* frente, Peca novaPeca) {
    int proximo = (*tras + 1) % TAM_FILA;

    if (proximo == *frente) {
        // Fila cheia — substituir o elemento mais antigo (sobrescrita circular)
        *frente = (*frente + 1) % TAM_FILA;
    }

    fila[*tras] = novaPeca;
    *tras = proximo;
}

// ============================================================================
// DEQUEUE – REMOVER A PEÇA DA FRENTE
// ============================================================================
Peca dequeue(Peca fila[], int* frente, int* tras) {
    if (*frente == *tras) {
        printf("\nFila vazia! Gerando peça automaticamente...\n");
        return gerarPeca();
    }

    Peca removida = fila[*frente];
    *frente = (*frente + 1) % TAM_FILA;

    return removida;
}

// ============================================================================
// EXIBIR A FILA
// ============================================================================
void exibirFila(Peca fila[], int frente, int tras) {
    printf("\n=================== FILA DE PEÇAS FUTURAS ===================\n");

    int i = frente;
    while (i != tras) {
        printf("Pos %d | ID: %d | Tipo: %s\n", i, fila[i].id, fila[i].nome);
        i = (i + 1) % TAM_FILA;
    }

    printf("=============================================================\n");
}
