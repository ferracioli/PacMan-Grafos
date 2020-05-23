#include "tabuleiro.h"

struct tabuleiro
{
    /* Tamanho do lado do tabuleiro */
    int ladoTab;

    /**
     * Posicao default: distancia de pacboy a fantasma
     * Posicao do pacman: -1
    */
    int **matTabuleiro;

    /* Posicoes dos personagens */
    int xPac, yPac;
    /* Posicoes dos personagens */
    int xFant, yFant;
};

void auxMarcacao(Tabuleiro **t, Grafo **g, int posFantasma)
{
    Fila *f;
    criarFila(&f);

    int currVertice;
    int tot = (*g)->nVertices;
    int n = (*t)->ladoTab;

    pushFila(f, posFantasma); // Push na posicao do fantasma logo no inicio da fila

    SetVizVisitado(*g, posFantasma, 1); // Seta o vertice que o fantasma esta como descoberto = 1

    while (!checaFilaVazia(f))
    {
        currVertice = popFila(f); // Inicia o processo com o vertice atual sendo o primeiro da fila

        SetVizVisitado(*g, currVertice, -1); // Setamos o estado dele como visitado = -1

        for (int i = 0; i < tot; i++) // Roda ate bater o total de vertices
        {
            if (VerificaAresta(*g, currVertice, i) == 1) // Existe aresta do atual para o vertice i?
            {
                if ((*g)->vetVisitado[i] == 0) // i esta marcado como nao visitado?
                {
                    SetVizVisitado(*g, i, 1); // Seta ele como descoberto = 1 entao

                    /* A posicao i do tabuleiro eh atribuida o (valor + 1) do vertice atual - WARNING: FIQUEI MEIO CONFUSO NESSE MAS DEU CERTO ENTAO OK */
                    (*t)->matTabuleiro[i / n][i % n] = (*t)->matTabuleiro[currVertice / n][currVertice % n] + 1;

                    pushFila(f, i); // Damos push no indice do vertice na fila
                }
            }
        }
    }
}

void Marcacao(Grafo **g, Tabuleiro **t)
{
    int posicaoFantasma;
    int lado = (*t)->ladoTab;

    posicaoFantasma = ((*t)->xFant * lado) + (*t)->yFant; // Acha a casa em que esta o fantasma

    auxMarcacao(t, g, posicaoFantasma); // Marca no tabuleiro
}

void CriarTabuleiro(int ladoTab, Tabuleiro **t, Grafo **g)
{
    int xAux, yAux;

    /* Alocacoes necessarias */
    *t = malloc(sizeof(Tabuleiro));
    (*t)->ladoTab = ladoTab;
    (*t)->matTabuleiro = malloc(ladoTab * sizeof(int *));
    for (int i = 0; i < ladoTab; i++)
    {
        (*t)->matTabuleiro[i] = malloc(ladoTab * sizeof(int));
    }

    for (int i = 0; i < ladoTab; i++)
    {
        for (int j = 0; j < ladoTab; j++)
        {
            (*t)->matTabuleiro[i][j] = 0; // Todas as casas da matriz recebem 0
        }
    }

    /* Posicao do pacboy gerada aleatoriamente */
    xAux = rand() % ladoTab;
    yAux = rand() % ladoTab;

    (*t)->xPac = xAux;
    (*t)->yPac = yAux;

    (*t)->matTabuleiro[xAux][yAux] = -1; // Atualiza o vetor do tabuleiro para conter o pacboy

    SetVizVisitado(*g, ((xAux * ladoTab) + yAux), -1); // Atualiza o vetor de visitados para lembrar do pacboy

    /* Gera a posicao do fantasma aleatoriamente */
    do
    {
        xAux = rand() % ladoTab;
        yAux = rand() % ladoTab;
    } while (xAux == (*t)->xPac && yAux == (*t)->yPac); // Enquanto a posicao do pacboy for igual do fantasma

    (*t)->xFant = xAux;
    (*t)->yFant = yAux;

    Marcacao(g, t); // Atualiza o tabuleiro
}

void DeletarTabuleiro(Tabuleiro **t)
{
    for (int i = 0; i < (*t)->ladoTab; i++)
    {
        free((*t)->matTabuleiro[i]);
    }
    free((*t)->matTabuleiro);
    (*t) = NULL;
}

// Imprime as linhas superior e inferior do tabuleiro
void printLinhas (Tabuleiro *t)
{
    printf("\033[0;36m%ls\033[0m", L"╬══");
    for (int i = 0; i < (t->ladoTab)-1; i++) {
        printf("\033[0;36m%ls\033[0m", L"═══");
    }
    printf("\033[0;36m%ls\033[0m\n", L"═╬");
}

void printTabu(Tabuleiro *t, int anima)
{

    // Permite a impressão dos caracteres especiais
    setlocale(LC_ALL, "");

    int i, j;
    int n = t->ladoTab;
    int aux;

    // Limite superior do tabuleiro :
    printLinhas(t);

    for (i = 0; i < n; i++)
    {

        // Imprime a barreira esquerda da linha i
        printf("\033[0;36m%ls\033[0m", L"║");

        for (j = 0; j < n; j++)
        {

            // Se o PacMan não encontrou o fantasma
            if(anima*anima == 1) 
            {

                // Imprime o PacMan com algum frame específico
                if (t->matTabuleiro[i][j] == -1)
                {
                    // PacMan com a boca aberta
                    if(anima == 1)
                        printf("\033[1;33m%ls\033[0m", L" ᗧ ");

                    // PacMan com a boca fechada
                    else 
                        printf("\033[1;33m%ls\033[0m", L"O  ");
                }
                else if (t->matTabuleiro[i][j] == 0)
                {
                    //Imprime o fantasma azul
                    printf("\033[1;36m%ls\033[0m", L" ᗣ ");
                }
                else
                {
                    // Espaço livre no tabuleiro
                    aux = t->matTabuleiro[i][j];
                    printf("   ");
                }
            }

            // Só imprimimos o PacMan e espaços em branco, pois o fantasma foi vencido
            else 
            {
                // Impressão do Pacman
                if (t->matTabuleiro[i][j] == -1)
                {

                    if(anima == 2)
                        printf("\033[1;33m%ls\033[0m", L" ᗧ ");
                    else 
                        printf("%ls", L"O  ");

                }
                else {
                    aux = t->matTabuleiro[i][j];
                    printf("   ");
                }
            }

        }

        // Lateral direita do tabuleiro
        printf("\033[0;36m%ls\033[0m\n", L"║");
    }

    // Lateral inferior do tabuleiro
    printLinhas(t);

    return;
}

void pacMove(Tabuleiro **t, Grafo **g)
{
    int x = (*t)->xPac, y = (*t)->yPac; // Os (x,y) originais
    int xAux = x, yAux = y;             // Os (x,y) auxiliares
    int lado = (*t)->ladoTab;           // Lado, para nao ter q invocar o t toda hora
    int min = 999999;                   // O minimo esta setado alto para nao bugar com um tabuleiro de 9x9
    int p = (x * lado) + y;             // Achando a posicao no tabuleiro (0,1,2,3,...,nVertices)

    /* A procura do caminho mais curto (NAO USAR ELSE, POIS PODE HAVER MAIS DE UM CAMINHO) */
    if (VerificaAresta(*g, p, p - lado) && x - 1 >= 0 && (*t)->matTabuleiro[x - 1][y] < min)
    {
        /* Todos os if seguem a mesma ideia, so muda a posicao usada */
        xAux = x - 1;
        yAux = y;

        min = (*t)->matTabuleiro[x - 1][y];
    }
    if (VerificaAresta(*g, p, p + 1) && y + 1 < lado && (*t)->matTabuleiro[x][y + 1] < min)
    {
        xAux = x;
        yAux = y + 1;

        min = (*t)->matTabuleiro[x][y + 1];
    }
    if (VerificaAresta(*g, p, p + lado) && x + 1 < lado && (*t)->matTabuleiro[x + 1][y] < min)
    {
        xAux = x + 1;
        yAux = y;

        min = (*t)->matTabuleiro[x + 1][y];
    }
    if (VerificaAresta(*g, p, p - 1) && y - 1 >= 0 && (*t)->matTabuleiro[x][y - 1] < min)
    {
        xAux = x;
        yAux = y - 1;

        min = (*t)->matTabuleiro[x][y - 1];
    }

    /* Atualizando o pacboy */
    (*t)->xPac = xAux;
    (*t)->yPac = yAux;

    (*t)->matTabuleiro[y][x] = 0; // Apesar de setar 0, ele sera arrumado depois
    (*t)->matTabuleiro[xAux][yAux] = -1;

    DeletarGrafo(g);
    CriarGrafo(lado, g); // Criamos novamente para termos as distancias atualizadas

    SetVizVisitado(*g, (x * lado) + y, 0);        // Setamos a posicao anterior como nao visitado
    SetVizVisitado(*g, (xAux * lado) + yAux, -1); // Setamos a posicao auxiliar como processado

    Marcacao(g, t); // Atualiza a marcacao do tabuleiro
}

int getPacPos(Tabuleiro *t, Grafo *g)
{
    int x = t->xPac, y = t->yPac;
    int lado = t->ladoTab;

    return (x * lado) + y;
}

void fantMove(Tabuleiro **t, Grafo **g)
{
    int x = (*t)->xFant, y = (*t)->yFant; // Os (x,y) originais
    int xAux = x, yAux = y;               // Os (x,y) auxiliares
    int lado = (*t)->ladoTab;             // Lado, para nao ter q invocar o t toda hora
    int p = (x * lado) + y;               // Achando a posicao no tabuleiro (0,1,2,3,...,nVertices)

    int r = rand() % 4; // O fantasma tem seu direcionamento aleatorizado

    // Direcionamento do fantasma :
    char op = 'm';
    while (op != 'w' && op != 'a' &&  op != 's' && op != 'd')
    {
        printf("\nQual movimento do seu fantasma (w = UP | d = RIGHT | s = DOWN | a = LEFT)? ");
        fflush(stdin);
        scanf(" %c", &op);
        printf("\nMovendo -> %c\n\n", r);
    }

    /* Faz os checks para ver se o fantasma pode andar em certa direcao (USAR ELSE POIS O RANDOM DETERMINOU PARA ONDE ELE VAI) */
    if (op == 'w' && VerificaAresta(*g, p, p - lado) && x - 1 >= 0 && (*t)->matTabuleiro[x - 1][y] != -1)
    {
        /* Todos os if seguem a mesma ideia, so muda a posicao usada */
        xAux = x - 1;
        yAux = y;
    }
    else if (op == 'd' && VerificaAresta(*g, p, p + 1) && y + 1 < lado && (*t)->matTabuleiro[x][y + 1] != -1)
    {
        xAux = x;
        yAux = y + 1;
    }
    else if (op == 's' && VerificaAresta(*g, p, p + lado) && x + 1 < lado && (*t)->matTabuleiro[x + 1][y] != -1)
    {
        xAux = x + 1;
        yAux = y;
    }
    else if (op == 'a' && VerificaAresta(*g, p, p - 1) && y - 1 >= 0 && (*t)->matTabuleiro[x][y - 1] != -1)
    {
        xAux = x;
        yAux = y - 1;
    }

    /* Atualizando o fantasma */
    (*t)->xFant = xAux;
    (*t)->yFant = yAux;

    (*t)->matTabuleiro[y][x] = 1;       // Esta agora a 1 distancia do fant
    (*t)->matTabuleiro[xAux][yAux] = 0; // Esta com o fant, entao a distancia eh zero

    DeletarGrafo(g);
    CriarGrafo(lado, g); // Criamos novamente para termos as distancias atualizadas

    SetVizVisitado(*g, getPacPos(*t, *g), -1); // Definimos a posicao do pacboy como processada

    Marcacao(g, t); // Atualiza a marcacao do tabuleiro
}

int getFantPos(Tabuleiro *t, Grafo *g)
{
    int x = t->xFant, y = t->yFant;
    int lado = t->ladoTab;

    return (x * lado) + y;
}