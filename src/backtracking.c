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
    inicializaMatriz(fazenda, N, M);
    rotaOtima(fazenda);
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
    fazenda->rota = (int*)malloc((N * M) * sizeof(int));
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

void movimentar(Fazenda *fazenda){
    int N, M, i, j;
    int **caminho;
    N = getN(fazenda);
    M = getM(fazenda);
    caminho = (int**)malloc(N * sizeof(int*));
    for(i = 0; i < M; i++){
        // Aloca memoria e preenche cada posição da linha com 0
        // 1 - siguinifica que a posição ja foi vizitada / 0 - siguinifica que a posição ainda não foi vizitada
        caminho[i] = (int*)calloc(M, sizeof(int));
    }
    bool caminhoOtimo = false;
    for(i = 0; i < M; i++){
        movimentarAuxiliar(fazenda, 0, &caminhoOtimo, &caminho, N, M, 0, i, 0);
        if(caminhoOtimo == true){
            break;
        }
    }
}

void movimentarAuxiliar(Fazenda *fazenda, int posicaoNaRota, bool *caminhoOtimo, int ***caminho, int N, int M, int l, int c, int deOndeVeio){
    /*
    * A variavel deOndeVeio representa de onde veio a função movimentarAuxiliar
    * 1 - Representa que veio de cima
    * 2 - Representa que veio da esquerda
    * 3 - Representa que veio da direita
    * 4 - Representa que veio de baixo
    * */
    if(l == N){
        *caminhoOtimo = true;
        return;
    }
    else if(l >= 0 && l < N && c >= 0 && c < M){
        if(fazenda->campo[l][c] == fazenda->rota[posicaoNaRota]){
            (*caminho)[l][c] = 1; // 1 - siguinifica que a posição ja foi vizitada / 0 - siguinifica que a posição ainda não foi vizitada
            if(*caminhoOtimo == false && deOndeVeio != 4){
                movimentarAuxiliar(fazenda,  posicaoNaRota + 1, caminhoOtimo, caminho, N, M, l + 1, c, 1);
            }
            if(*caminhoOtimo == false && deOndeVeio != 3){
                movimentarAuxiliar(fazenda,  posicaoNaRota + 1, caminhoOtimo, caminho, N, M, l, c + 1, 2);
            }
            if(*caminhoOtimo == false && deOndeVeio != 2){
                movimentarAuxiliar(fazenda,  posicaoNaRota + 1, caminhoOtimo, caminho, N, M, l, c - 1, 3);
            }
            if(*caminhoOtimo == false && deOndeVeio != 1){
                movimentarAuxiliar(fazenda,  posicaoNaRota + 1, caminhoOtimo, caminho, N, M, l - 1, c, 4);
            }
            if(*caminhoOtimo == false){
                    (*caminho)[l][c] = 0;
                }
        }
    }
}
