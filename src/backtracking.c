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

int* fibonacci(int n){
    if(n == 0){
        int* vetor = (int*) malloc(sizeof(int));
        vetor[0] = 1;
        return vetor;
    }
    if(n == 1){
        int* vetor = (int*) malloc(sizeof(int)*2);
        vetor[0] = 1;
        vetor[1] = 1;
        return vetor;
    }

    int *vetor = (int*)malloc(n * sizeof(int));
    vetor[0] = 1;
    vetor[1] = 1;
    for(int i = 2; i < n; i++){
        vetor[i] = vetor[i - 1] + vetor[i - 2];
    }
    return vetor;
}

int* gerarSequencia(int n){
    int *fibo = (int*)malloc(n * sizeof(int));
    int i = 0;
    int fiboCont = 1;
    while(i < n){
        int *vetor = fibonacci(fiboCont);

        for(int j = 0; j < fiboCont; j++){
            fibo[i] = vetor[j];
            i++;
        }
        fiboCont++;
    }
    return fibo;
}

//Nao funcional, precisa de ajustes
void movimentar(Fazenda *fazenda, int i, int j, int *sequencia, int tamanhoSequencia, int *sequenciaAtual, int tamanhoSequenciaAtual, int *melhorSequencia, int *tamanhoMelhorSequencia){
    if(i < 0 || i >= fazenda->N || j < 0 || j >= fazenda->M){
        return;
    }
    if(fazenda->campo[i][j] == 0){
        return;
    }
    if(tamanhoSequenciaAtual > *tamanhoMelhorSequencia){
        *tamanhoMelhorSequencia = tamanhoSequenciaAtual;
        for(int k = 0; k < tamanhoSequenciaAtual; k++){
            melhorSequencia[k] = sequenciaAtual[k];
        }
    }
    int numeroCampo = fazenda->campo[i][j];
    if(numeroCampo == sequencia[tamanhoSequenciaAtual]){
        sequenciaAtual[tamanhoSequenciaAtual] = numeroCampo;
        fazenda->campo[i][j] = 0;
        movimentar(fazenda, i + 1, j, sequencia, tamanhoSequencia, sequenciaAtual, tamanhoSequenciaAtual + 1, melhorSequencia, tamanhoMelhorSequencia);
        movimentar(fazenda, i - 1, j, sequencia, tamanhoSequencia, sequenciaAtual, tamanhoSequenciaAtual + 1, melhorSequencia, tamanhoMelhorSequencia);
        movimentar(fazenda, i, j + 1, sequencia, tamanhoSequencia, sequenciaAtual, tamanhoSequenciaAtual + 1, melhorSequencia, tamanhoMelhorSequencia);
        movimentar(fazenda, i, j - 1, sequencia, tamanhoSequencia, sequenciaAtual, tamanhoSequenciaAtual + 1, melhorSequencia, tamanhoMelhorSequencia);
        fazenda->campo[i][j] = numeroCampo;
    }
}