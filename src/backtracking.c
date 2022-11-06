#include "backtracking.h"

bool leituraDados(Fazenda *fazenda, char *nomeArquivo){
    int N, M, numeroCampo, i, j;
    char nomeArquivo[50] = "tests/test01.txt";
    char diretorio[100];
    strcpy(diretorio, "tests/");
    strcat(strcat(diretorio, nomeArquivo), ".txt");
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

void inserirNumeroCampo(Fazenda *fazenda, int  numeroCampo,int i, int j){
    fazenda->campo[i][j] = numeroCampo;
}

void CriaRotaOtimaMaxima(RotaOtima *rotaOtima, int N, int M){
    int maximoTermos = N * M;
    int termoAtual, qtdSequenciaFibonacci, i, pegaValorNaPosicao;
    rotaOtima->rota[0] = 1;
    rotaOtima->rota[1] = 1;
    rotaOtima->rota[2] = 1;
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
                rotaOtima->rota[termoAtual - 1] = (rotaOtima->rota[termoAtual - 2] + rotaOtima->rota[termoAtual - 3]);
            }
            else{
                rotaOtima->rota[termoAtual - 1] = rotaOtima->rota[pegaValorNaPosicao];
            }
        }

    }
    
}

void inicializaRotaOtima(RotaOtima *rotaOtima, int N, int M){
    rotaOtima->rota = (int*)malloc((N * M) * sizeof(int));
}

bool criaCassoTeste(RotaOtima *rotaOtima, char *nomeArquivoTeste, int N, int M){
    int i, j, posicao;
    int maximaPosicao = N * M;
    char diretorio[100];
    strcpy(diretorio, "tests/");
    strcat(strcat(diretorio, nomeArquivoTeste), ".txt");
    FILE *file;
    file = fopen(diretorio,"w");
    if(file == NULL){
        printf("\nErro na criacao do arquivo de teste !!!!!!!!\n\n");
        return false;
    }
    fprintf(file, "%d %d\n", N, M);
    for(i = 0; i < N; i++){
        for(j = 0; j < M; j++){
            posicao = rand() % maximaPosicao;
            fprintf(file, "%d ", rotaOtima->rota[posicao]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return true;
}

void rotaOtima(Fazenda *fazenda){
    int maximoTermos = fazenda->N * fazenda->M;
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
    int  i, j;
    int **caminho;
    caminho = (int**)malloc(fazenda->N * sizeof(int*));
    for(i = 0; i < fazenda->M; i++){
        // Aloca memoria e preenche cada posição da linha com 0
        // 1 - siguinifica que a posição ja foi vizitada / 0 - siguinifica que a posição ainda não foi vizitada
        caminho[i] = (int*)calloc(fazenda->M, sizeof(int));
    }
    bool caminhoOtimo = false;
    ListaEncadeada listaEncadeada;
    inicializaListaEncadeada(&listaEncadeada);
    for(i = 0; i < fazenda->M; i++){
        movimentarAuxiliar(fazenda, &listaEncadeada, 0, &caminhoOtimo, &caminho, 0, i);
        if(caminhoOtimo == true){
            break;
        }
    }
    if(caminhoOtimo == true){
        imprimirListaEncadeada(&listaEncadeada);
    }
    else{
        printf("IMPOSSIVEL!\n");
    }
}

void movimentarAuxiliar(Fazenda *fazenda, ListaEncadeada *listaEncadeada, int posicaoNaRota, bool *caminhoOtimo, int ***caminho, int l, int c){
    if(l == fazenda->N){
        *caminhoOtimo = true;
        return;
    }
    else if(l >= 0 && l < fazenda->N && c >= 0 && c < fazenda->M){
        if(fazenda->campo[l][c] == fazenda->rota[posicaoNaRota] && (*caminho)[l][c] != 1){
            (*caminho)[l][c] = 1; // 1 - siguinifica que a posição ja foi vizitada / 0 - siguinifica que a posição ainda não foi vizitada
            
            movimentarAuxiliar(fazenda, listaEncadeada, posicaoNaRota + 1, caminhoOtimo, caminho, l + 1, c);
            
            if(*caminhoOtimo == false){
                movimentarAuxiliar(fazenda, listaEncadeada, posicaoNaRota + 1, caminhoOtimo, caminho, l, c + 1);
            }
            if(*caminhoOtimo == false) {
                movimentarAuxiliar(fazenda, listaEncadeada, posicaoNaRota + 1, caminhoOtimo, caminho, l, c - 1);
            }
            if(*caminhoOtimo == false){
                movimentarAuxiliar(fazenda, listaEncadeada, posicaoNaRota + 1, caminhoOtimo, caminho,l - 1, c);
            }
            if(*caminhoOtimo == false){
                    (*caminho)[l][c] = 0;
                }
            else{
                inserirListaEncadeada(listaEncadeada, l + 1, c + 1, fazenda->rota[posicaoNaRota]);
            }
        }
    }
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

void inicializaListaEncadeada(ListaEncadeada *listaEncadeada){
    listaEncadeada->primeira = (proximaCelula)malloc(sizeof(Celula));
    listaEncadeada->primeira = NULL;
}

void inserirListaEncadeada(ListaEncadeada *listaEncadeada, int linha, int coluna, int numeroRota){
    proximaCelula proxCelula;
    proxCelula = (proximaCelula)malloc(sizeof(Celula));
    proxCelula->coluna = coluna;
    proxCelula->linha = linha;
    proxCelula->numeroRota = numeroRota;
    proxCelula->proxima = NULL;
    if(listaEncadeada->primeira == NULL){
        listaEncadeada->primeira = proxCelula;
    }
    else{
        proxCelula->proxima = listaEncadeada->primeira;
        listaEncadeada->primeira = proxCelula;
    }
}

void imprimirListaEncadeada(ListaEncadeada *listaEncadeada){
    proximaCelula proxCelula;
    proxCelula = listaEncadeada->primeira;
    while (proxCelula != NULL){
        printf("[%-2d %-2d] = %d\n", proxCelula->linha, proxCelula->coluna, proxCelula->numeroRota);
        proxCelula = proxCelula->proxima;
    }
}
