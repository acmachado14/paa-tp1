#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ANALISE 1

typedef struct{
    int **campo;
    int *rota;
    int N;
    int M;
}Fazenda;

bool leituraDados(Fazenda *fazenda);

void inicializaMatriz(Fazenda *fazenda, int N, int M);

int getN(Fazenda *fazenda);

int getM(Fazenda *fazenda);

void inserirNumeroCampo(Fazenda *fazenda, int  numeroCampo,int i, int j);

void rotaOtima(Fazenda *fazenda);

void movimentar(Fazenda *fazenda);

void movimentarAuxiliar(Fazenda *fazenda, int posicaoNaRota, bool *caminhoOtimo, int ***caminho, int N, int M, int l, int c, int deOndeVeio);

int* fibonacci(int n);

int* gerarSequencia(int n);
