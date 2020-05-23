#include <stdio.h>
#include <stdlib.h>

typedef struct grafo
{
    /**
     * Numero de vertices do grafo
     * Tambem representa o numero de casas do tabuleiro
    */
    int nVertices;

    /* Representacao do grafo por matriz de adjacencia */
    int **vertices;

    /**
     * Vetor que indica a situacao do vertice de indice i em relacao ao seus vizinhos
     * 
     * -1   :  Processado
     * 0    :  Nao visitado
     * 1    :  Descoberto
    */
    int *vetVisitado;
} Grafo;

void CriarGrafo(int lado, Grafo **g);
void DeletarGrafo(Grafo **g);
int VerificaAresta(Grafo *g, int x, int y);
void SetVizVisitado(Grafo *g, int index, int valor);