#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


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