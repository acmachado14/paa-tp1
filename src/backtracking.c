#include "backtracking.h"

bool leituraDados(Fazenda *fazenda){
    int N, M, numeroCampo, i, j;
    char nomeArquivo[50] = "testes/teste1.txt";
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
    fazenda->campo = (int*)malloc((N * M) * sizeof(int));
    fazenda->campo = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < M; i++){
        fazenda->campo[i] = (int*)malloc(N * sizeof(int));
    }
}

int getN(Fazenda *fazenda){
    return fazenda->N;
}
int getM(Fazenda *fazenda){
    return fazenda->M;
}

void inserirNumeroCampo(Fazenda *fazenda, int  numeroCampo,int i, int j){
    fazenda->campo[i][j] = numeroCampo;
}

void rotaOtima(Fazenda *fazenda){
    int N = getN(fazenda);
    int M = getM(fazenda);
    int maximoTermos = N * M;
    int termoAtual, qtdSequenciaFibonacci, i, pegaValorNaPosicao;
    fazenda->rota[0] = 1;
    fazenda->rota[1] = 1;
    fazenda->rota[2] = 1;
    termoAtual = 3;
    qtdSequenciaFibonacci = 2;

    while (termoAtual < maximoTermos){
        qtdSequenciaFibonacci += 1;
        for(i = 0; i < qtdSequenciaFibonacci; i++){
            termoAtual++;
            pegaValorNaPosicao = termoAtual - qtdSequenciaFibonacci;
            if(termoAtual > maximoTermos){
                break;
            }
            else if(i == qtdSequenciaFibonacci -1){
                fazenda->rota[termoAtual - 1] = (fazenda->rota[termoAtual - 2] + fazenda->rota[termoAtual - 3]);
            }
            else{
                fazenda->rota[termoAtual - 1] = fazenda->rota[pegaValorNaPosicao];
            }
        }

    }
    
}