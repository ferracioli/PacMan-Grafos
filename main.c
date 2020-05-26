// Olavo Morais Borges Pereira  <>                          11297792
// Leonardo Antonetti da Motta  <l.a.motta@uspbr>           11275338
// Gabriel Monteiro Ferracioli  <ferracioligabriel@usp.br>  11219129
// Diogo Castanho Emídio        <diogo.ce@usp.br>           11297274

// O codigo foi separado por varios ////// para cada secao (Fila / Grafo / Tabuleiro / Main) respectivamente

// TADs
#include "tabuleiro.h"

int main()
{
    setlocale(LC_ALL, "");

    Grafo *g;
    Tabuleiro *t;
    int ladoTab = 0;

    srand(time(0));

    while (ladoTab > 11 || ladoTab < 2)
    {
        printf("Qual o tamanho do lado do tabuleiro (De 2 a 10)?\n");
        scanf("%d", &ladoTab);
    }

    CriarGrafo(ladoTab, &g);
    CriarTabuleiro(ladoTab, &t, &g);

    // anima indica o frame do PacMan que será mostrado (inicia com a boca aberta)
    int anima = 1;

    while (getPacPos(t, g) != getFantPos(t, g))
    {

        printTabu(t, anima);
        printf("\nMovimento do fantasma\n");
        fantMove(&t, &g);

        printTabu(t, anima);
        printf("\nMovimento do PacBoy\n\n");
        pacMove(&t, &g);

        // troca de frame
        anima*= -1;
    }

    // Multiplica por 2 para indicar que não queremos imprimir o fantasma
    printTabu(t, 2*anima);

    // Imprime os emojis de cereja
    printf("%ls", L"\n 🍒 ");
    printf(" PacBoy encontrou o fantasma!");
    printf("%ls", L" 🍒 \n");

    DeletarGrafo(&g);
    DeletarTabuleiro(&t);

    return 0;
}