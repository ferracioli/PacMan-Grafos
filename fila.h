#include <stdio.h>
#include <stdlib.h>

/** 
 * Tudo na parte de fila esta definido como padrao de uma fila.
 * Nao ha nada de especial para comentar durante o desenvolvimento.
 **/

typedef struct no No;

typedef struct fila Fila;

void criarFila(Fila **fila);
void excluiFila(Fila **fila);
int checaFilaVazia(Fila *fila);
void pushFila(Fila *fila, int x);
int popFila(Fila *fila);