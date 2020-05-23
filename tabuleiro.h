#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Bibliotecas para impressão dos caracteres especiais
#include <locale.h>
#include <wchar.h>

#include "grafo.h"
#include "fila.h"

typedef struct tabuleiro Tabuleiro;

void auxMarcacao(Tabuleiro **t, Grafo **g, int posFantasma);
void Marcacao(Grafo **g, Tabuleiro **t);
void CriarTabuleiro(int ladoTab, Tabuleiro **t, Grafo **g);
void DeletarTabuleiro(Tabuleiro **t);
void printLinhas (Tabuleiro *t);
void printTabu(Tabuleiro *t, int anima);
void pacMove(Tabuleiro **t, Grafo **g);
int getPacPos(Tabuleiro *t, Grafo *g);
void fantMove(Tabuleiro **t, Grafo **g);
int getFantPos(Tabuleiro *t, Grafo *g);