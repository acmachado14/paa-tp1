#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ANALISE 1

typedef struct{
    int **campo;
    int N;
    int M;
}Fazenda;

bool leituraDados(Fazenda *fazenda);
void inicializaMatriz(Fazenda *fazenda, int N, int M);
void inserirNumeroCampo(Fazenda *fazenda, int  numeroCampo,int i, int j);
