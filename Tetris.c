#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10   // tamanho máximo da fila

typedef struct {
    int id;
    char tipo[10];   // Ex.: "I", "O", "T", "L", "J", "S", "Z"
} Peca;

typedef struct {
    Peca fila[MAX];
    int inicio;
    int fim;
    int qtd;
} Fila;

// --------- Funções da fila ----------

void inicializar(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
}

int filaVazia(Fila *f) {
    return f->qtd == 0;
}

int filaCheia(Fila *f) {
    return f->qtd == MAX;
}

void inserir(Fila *f, int id, const char *tipo) {
    if (filaCheia(f)) {
        printf("Fila cheia! Nao foi possivel inserir a peca %d.\n", id);
        return;
    }

    f->fila[f->fim].id = id;
    strcpy(f->fila[f->fim].tipo, tipo);

    f->fim = (f->fim + 1) % MAX;
    f->qtd++;

    printf("Inserida peca ID %d, tipo %s.\n", id, tipo);
}

void remover(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia! Nenhuma peca para remover.\n");
        return;
    }

    Peca removida = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->qtd--;

    printf("Removida peca ID %d, tipo %s.\n", removida.id, removida.tipo);
}

void mostrarFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }

    printf("\n--- Fila de Pecas Tetris ---\n");

    int i = f->inicio;
    for (int count = 0; count < f->qtd; count++) {
        printf("ID: %d | Tipo: %s\n", f->fila[i].id, f->fila[i].tipo);
        i = (i + 1) % MAX;
    }
    printf("-----------------------------\n\n");
}

// --------- Programa principal ----------

int main() {
    Fila tetris;
    inicializar(&tetris);

    int opcao, id;
    char tipo[10];

    do {
        printf("1 - Inserir peca\n");
        printf("2 - Remover peca\n");
        printf("3 - Mostrar fila\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("ID da peca: ");
                scanf("%d", &id);
                printf("Tipo (I,O,T,L,J,S,Z): ");
                scanf("%s", tipo);
                inserir(&tetris, id, tipo);
                break;

            case 2:
                remover(&tetris);
                break;

            case 3:
                mostrarFila(&tetris);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
