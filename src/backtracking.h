#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define ANALISE 1

typedef struct Cel* proximaCelula;
typedef struct Cel{
    int linha;
    int coluna;
    int numeroRota;
    proximaCelula proxima;
}Celula;

typedef struct{
    proximaCelula primeira;
}ListaEncadeada;

typedef struct{
    int **campo;
    int N;
    int M;
}Fazenda;

typedef struct{
    int *rota;
}RotaOtima;

bool leituraDados(Fazenda *fazenda, RotaOtima *rotaOtima, char nomeArquivo[]);

void inicializaMatriz(Fazenda *fazenda, int N, int M);

void inserirNumeroCampo(Fazenda *fazenda, int  numeroCampo,int i, int j);

void criaRotaOtima(RotaOtima *rotaOtima, int N, int M);

void movimentar(Fazenda *fazenda, RotaOtima *rotaOtima, clock_t tempoIncial);

void movimentarAuxiliar(Fazenda *fazenda, RotaOtima *rotaOtima, ListaEncadeada *listaEncadeada, int posicaoNaRota, bool *caminhoOtimo, int ***caminho, int l, int c, int *contRecursoes, int *maxRecursoes, int *maxAuxiliar);

void inicializaListaEncadeada(ListaEncadeada *listaEncadeada);

void inserirListaEncadeada(ListaEncadeada *listaEncadeada, int linha, int coluna, int numeroRota);

void imprimirListaEncadeada(ListaEncadeada *listaEncadeada);

bool criaCassoTeste(char nomeArquivo[], int N, int M);

void inicializaRotaOtima(RotaOtima *rotaOtima, int N, int M);
