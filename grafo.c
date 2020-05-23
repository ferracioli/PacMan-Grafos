#include "grafo.h"

void CriarGrafo(int lado, Grafo **g)
{
    int totalCasas = lado * lado;
    int i, j;

    /* Inicializacoes e alocamentos*/
    *g = malloc(sizeof(Grafo));
    (*g)->vertices = malloc(totalCasas * sizeof(int *));
    (*g)->nVertices = totalCasas;
    (*g)->vetVisitado = malloc(totalCasas * sizeof(int));
    for (i = 0; i < totalCasas; i++)
    {
        (*g)->vertices[i] = malloc(totalCasas * sizeof(int));
    }
    for (i = 0; i < totalCasas; i++)
    {
        (*g)->vetVisitado[i] = 0; // vetVisitado tem que ser todo 0
    }

    /* Percorrendo a matriz toda */
    /* 1 para posicao conectada, 0 para posicao nao conectada */
    for (i = 0; i < totalCasas; i++)
    {
        for (j = 0; j < totalCasas; j++)
        {
            if ((((i + 1) / lado) == (i / lado)) && j == (i + 1)) // vizinho a direita?
            {
                (*g)->vertices[i][j] = 1;
            }
            else if (j == (i + lado)) // vizinho embaixo?
            {
                (*g)->vertices[i][j] = 1;
            }
            else if ((((i - 1) / lado) == (i / lado)) && j == (i - 1)) // vizinho a esquerda?
            {
                (*g)->vertices[i][j] = 1;
            }
            else if (j == (i - lado)) // vizinho em cima?
            {
                (*g)->vertices[i][j] = 1;
            }
            else // sem vizinho
            {
                (*g)->vertices[i][j] = 0;
            }
        }
    }
}

void DeletarGrafo(Grafo **g)
{
    for (int i = 0; i < (*g)->nVertices; i++)
    {
        free((*g)->vertices[i]); // libera linha a linha
    }

    free((*g)->vertices); // libera o grafo
    (*g) = NULL;
}

int VerificaAresta(Grafo *g, int x, int y)
{
    if (x < g->nVertices && x >= 0 && y < g->nVertices && y >= 0) // X e Y estao dentro do intervalo valido da matriz?
    {
        return (g->vertices[x][y] == 1) ? 1 : 0; // Sao vizinhos? 1 = sim ; 0 = nao
    }
}

void SetVizVisitado(Grafo *g, int index, int valor)
{
    g->vetVisitado[index] = valor;
}