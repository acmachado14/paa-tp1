#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ANALISE 1

typedef struct Cel* proximaCelula;
typedef struct Cel{
    int linha;
    int coluna;
    proximaCelula proxima;
}Celula;

typedef struct{
    proximaCelula primeira;
}ListaEncadeada;


typedef struct{
    int **campo;
    int *rota;
    int N;
    int M;
}Fazenda;

bool leituraDados(Fazenda *fazenda);

void inicializaMatriz(Fazenda *fazenda, int N, int M);

void inserirNumeroCampo(Fazenda *fazenda, int  numeroCampo,int i, int j);

void rotaOtima(Fazenda *fazenda);

void movimentar(Fazenda *fazenda);

void movimentarAuxiliar(Fazenda *fazenda, ListaEncadeada *listaEncadeada, int posicaoNaRota, bool *caminhoOtimo, int ***caminho, int l, int c);

int* fibonacci(int n);

int* gerarSequencia(int n);

void inicializaListaEncadeada(ListaEncadeada *listaEncadeada);

void inserirListaEncadeada(ListaEncadeada *listaEncadeada, int linha, int coluna);

void imprimirListaEncadeada(ListaEncadeada *listaEncadeada);