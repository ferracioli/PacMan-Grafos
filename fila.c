#include "fila.h"

struct no
{
    struct no *prox;
    int info;
};

struct fila
{
    No *ini;
    No *fim;
};

void criarFila(Fila **fila)
{
    *fila = malloc(sizeof(Fila));
    (*fila)->ini = NULL;
    (*fila)->fim = NULL;
}

void excluiFila(Fila **fila)
{
    No *aux;
    while ((*fila)->ini != NULL)
    {
        aux = (*fila)->ini;
        (*fila)->ini = (*fila)->ini->prox;
        free(aux);
    }
    free(*fila);
    *fila = NULL;
    aux = NULL;
}

int checaFilaVazia(Fila *fila)
{
    return (fila->ini == NULL) ? 1 : 0;
}

void pushFila(Fila *fila, int x)
{
    No *aux = malloc(sizeof(No));

    aux->info = x;
    aux->prox = NULL;

    if (checaFilaVazia(fila))
        fila->ini = aux;
    else
        fila->fim->prox = aux;
    fila->fim = aux;
}

int popFila(Fila *fila)
{
    No *aux;
    int x;

    if (checaFilaVazia(fila))
        return -1; /* sem elemento */

    x = fila->ini->info;
    aux = fila->ini;
    fila->ini = fila->ini->prox;
    free(aux);

    return x;
}