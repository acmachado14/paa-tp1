#include "backtracking.h"

bool leituraDados(Fazenda *fazenda){
    int N, M, numeroCampo, i, j;
    char nomeArquivo[50] = "teste1.txt";
    FILE *file;
    file = fopen(nomeArquivo, "r");
    if(file == NULL){
        printf("\nErro na abertura do arquivo de entrada !!!!!!!!\n\n");
        return false;
    }
    int quantidadeDeVertices, verticeOrigem, verticeDestino;
    float pesoAresta;
    fscanf(file, "%d %d", &N, &M);
    printf("%d %d\n", N, M);
    inicializaMatriz(fazenda, N, M);
    for(i = 0; i < N; i++){
        for(j = 0; j < M; j++){
            fscanf(file, "%d ", &numeroCampo);
            inserirNumeroCampo(fazenda, numeroCampo, i, j);
        }
    }
    fclose(file);
    return true;
}

void inicializaMatriz(Fazenda *fazenda, int N, int M){
    fazenda->N = N;
    fazenda->M = M;
    fazenda->campo = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < M; i++){
        fazenda->campo[i] = (int*)malloc(N * sizeof(int));
    }
}

void inserirNumeroCampo(Fazenda *fazenda, int  numeroCampo,int i, int j){
    fazenda->campo[i][j] = numeroCampo;
}