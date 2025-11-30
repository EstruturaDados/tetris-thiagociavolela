/*
    ============================================================================
                        DESAFIO TETRIS STACK – NÍVEL AVENTUREIRO
                        Fila Circular + Pilha de Reserva (3 posições)
    ============================================================================
    
    Objetivo:
    - Manter a fila circular com 5 peças (como no nível Novato)
    - Adicionar uma pilha linear de capacidade 3 para reserva de peças

    Funcionalidades:
    ✔ Jogar peça (dequeue)
    ✔ Gerar nova peça (enqueue automático)
    ✔ Reservar peça da frente da fila (push)
    ✔ Usar peça reservada (pop)
    ✔ Exibir fila e pilha após cada ação

    Conceitos utilizados:
    - Fila circular
    - Pilha linear (stack)
    - struct
    - modularização
    - limites de capacidade
    ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// ============================================================================
// STRUCT DA PEÇA
// ============================================================================
typedef struct {
    int id;
    char nome[3];
} Peca;

// ============================================================================
// PROTÓTIPOS
// ============================================================================
// Fila
void inicializarFila(Peca fila[], int* frente, int* tras);
Peca gerarPeca();
void enqueue(Peca fila[], int* tras, int* frente, Peca nova);
Peca dequeue(Peca fila[], int* frente, int* tras);
void exibirFila(Peca fila[], int frente, int tras);

// Pilha
void inicializarPilha(Peca pilha[], int* topo);
void push(Peca pilha[], int* topo, Peca elemento);
Peca pop(Peca pilha[], int* topo);
void exibirPilha(Peca pilha[], int topo);

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================
int main() {
    srand(time(NULL));

    // -------- FILA --------
    Peca fila[TAM_FILA];
    int frente = 0, tras = 0;
    inicializarFila(fila, &frente, &tras);

    // -------- PILHA --------
    Peca pilha[TAM_PILHA];
    int topo = -1;
    inicializarPilha(pilha, &topo);

    int opcao;

    do {
        printf("\n============== TETRIS STACK – NÍVEL AVENTUREIRO ==============\n");
        printf("1 - Jogar peça (fila)\n");
        printf("2 - Reservar peça (push na pilha)\n");
        printf("3 - Usar peça reservada (pop da pilha)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = dequeue(fila, &frente, &tras);
                printf("\nVocê jogou a peça da fila: ID %d | Tipo: %s\n",
                       jogada.id, jogada.nome);
                break;
            }

            case 2: {
                if (topo == TAM_PILHA - 1) {
                    printf("\n❌ Pilha cheia! Não é possível reservar mais peças.\n");
                } else {
                    Peca reservada = dequeue(fila, &frente, &tras);
                    push(pilha, &topo, reservada);
                    printf("\nPeça reservada: ID %d | Tipo: %s\n",
                           reservada.id, reservada.nome);
                }
                break;
            }

            case 3: {
                if (topo == -1) {
                    printf("\n❌ A pilha está vazia! Não há peças reservadas.\n");
                } else {
                    Peca usada = pop(pilha, &topo);
                    printf("\nPeça usada da reserva: ID %d | Tipo: %s\n",
                           usada.id, usada.nome);
                }
                break;
            }

            case 0:
                printf("\nEncerrando o jogo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

        // Sempre mostrar o estado atualizado
        exibirFila(fila, frente, tras);
        exibirPilha(pilha, topo);

    } while (opcao != 0);

    return 0;
}

// ============================================================================
// FUNÇÕES DA FILA CIRCULAR
// ============================================================================
void inicializarFila(Peca fila[], int* frente, int* tras) {
    *frente = 0;
    *tras = 0;
    for (int i = 0; i < TAM_FILA; i++) {
        fila[i] = gerarPeca();
        *tras = (*tras + 1) % TAM_FILA;
    }
}

Peca gerarPeca() {
    Peca p;
    p.id = rand() % 1000;

    const char* formas[] = {"I", "O", "T", "L", "J", "S", "Z"};
    strcpy(p.nome, formas[rand() % 7]);

    return p;
}

void enqueue(Peca fila[], int* tras, int* frente, Peca nova) {
    int proximaPos = (*tras + 1) % TAM_FILA;

    if (proximaPos == *frente) {
        *frente = (*frente + 1) % TAM_FILA; // sobrescrever item antigo
    }

    fila[*tras] = nova;
    *tras = proximaPos;
}

Peca dequeue(Peca fila[], int* frente, int* tras) {
    if (*frente == *tras) {
        printf("\n⚠️  Fila vazia! Gerando nova peça...\n");
        return gerarPeca();
    }

    Peca removida = fila[*frente];
    *frente = (*frente + 1) % TAM_FILA;

    // Garantir que a fila tenha sempre 5 peças
    enqueue(fila, tras, frente, gerarPeca());

    return removida;
}

void exibirFila(Peca fila[], int frente, int tras) {
    printf("\n===== FILA DE PEÇAS FUTURAS =====\n");

    int i = frente;
    while (i != tras) {
        printf("Pos %d | ID: %d | Tipo: %s\n",
               i, fila[i].id, fila[i].nome);
        i = (i + 1) % TAM_FILA;
    }

    printf("=================================\n");
}

// ============================================================================
// FUNÇÕES DA PILHA
// ============================================================================
void inicializarPilha(Peca pilha[], int* topo) {
    *topo = -1;
}

void push(Peca pilha[], int* topo, Peca elemento) {
    (*topo)++;
    pilha[*topo] = elemento;
}

Peca pop(Peca pilha[], int* topo) {
    Peca removida = pilha[*topo];
    (*topo)--;
    return removida;
}

void exibirPilha(Peca pilha[], int topo) {
    printf("\n===== PILHA DE RESERVA =====\n");

    if (topo == -1) {
        printf("Pilha vazia.\n");
    } else {
        for (int i = topo; i >= 0; i--) {
            printf("Topo %d | ID: %d | Tipo: %s\n",
                   i, pilha[i].id, pilha[i].nome);
        }
    }

    printf("================================\n");
}
