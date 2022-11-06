#include "backtracking.h"

bool leituraDados(Fazenda *fazenda){
    int N, M, numeroCampo, i, j;
    char nomeArquivo[50] = "tests/test01.txt";
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

void movimentar(Fazenda *fazenda, clock_t tempoIncial){
    int  i, j;
    int **caminho;
    caminho = (int**)malloc(fazenda->N * sizeof(int*));
    for(i = 0; i < fazenda->M; i++){
        // Aloca memoria e preenche cada posição da linha com 0
        // 1 - siguinifica que a posição ja foi vizitada / 0 - siguinifica que a posição ainda não foi vizitada
        caminho[i] = (int*)calloc(fazenda->M, sizeof(int));
    }
    int contRecursoes = 0;
    int maxRecursoes = 0;
    int maxAuxiliar = 0;
    bool caminhoOtimo = false;

    ListaEncadeada listaEncadeada;
    inicializaListaEncadeada(&listaEncadeada);
    for(i = 0; i < fazenda->M; i++){
        movimentarAuxiliar(fazenda, &listaEncadeada, 0, &caminhoOtimo, &caminho, 0, i, &contRecursoes, &maxRecursoes, &maxAuxiliar);
        if(caminhoOtimo == true){
            break;
        }
    }

    if (ANALISE == 1){
        clock_t tempoFinal = clock();
        printf("Quantidade de Recursoes: %d \nMaximo de Recursao alcancado %d \n", contRecursoes, maxRecursoes);
        printf("Tempo de execucao: %f ms\n", ((float)(tempoFinal-tempoIncial)) * 1000/(CLOCKS_PER_SEC));
    }

    if(caminhoOtimo == true){
        imprimirListaEncadeada(&listaEncadeada);
        return;
    }

    printf("IMPOSSIVEL!\n");

}

void movimentarAuxiliar(Fazenda *fazenda, ListaEncadeada *listaEncadeada, int posicaoNaRota, bool *caminhoOtimo, int ***caminho, int l, int c, int *contRecursoes, int *maxRecursoes, int *maxAuxiliar){
    (*maxAuxiliar)++;
    (*contRecursoes)++;
    if(l == fazenda->N){
        *caminhoOtimo = true;
        return;
    }
    else if(l >= 0 && l < fazenda->N && c >= 0 && c < fazenda->M && fazenda->campo[l][c] == fazenda->rota[posicaoNaRota] && (*caminho)[l][c] != 1){
        (*caminho)[l][c] = 1; // 1 - siguinifica que a posição ja foi vizitada / 0 - siguinifica que a posição ainda não foi vizitada

        //BAIXO
        movimentarAuxiliar(fazenda, listaEncadeada, posicaoNaRota + 1, caminhoOtimo, caminho, l + 1, c, contRecursoes, maxRecursoes, maxAuxiliar);

        //DIREITA
        if(*caminhoOtimo == false){
            movimentarAuxiliar(fazenda, listaEncadeada, posicaoNaRota + 1, caminhoOtimo, caminho, l, c + 1, contRecursoes, maxRecursoes, maxAuxiliar);
        }
        //ESQUERDA
        if(*caminhoOtimo == false) {
            movimentarAuxiliar(fazenda, listaEncadeada, posicaoNaRota + 1, caminhoOtimo, caminho, l, c - 1, contRecursoes, maxRecursoes, maxAuxiliar);
        }
        //CIMA
        if(*caminhoOtimo == false){
            movimentarAuxiliar(fazenda, listaEncadeada, posicaoNaRota + 1, caminhoOtimo, caminho,l - 1, c, contRecursoes, maxRecursoes, maxAuxiliar);
        }
        if(*caminhoOtimo == false){
            (*caminho)[l][c] = 0;
        }
        else{
            inserirListaEncadeada(listaEncadeada, l + 1, c + 1);
        }
    }else{
        if(*maxAuxiliar > *maxRecursoes){
            *maxRecursoes = *maxAuxiliar;
        }
        *maxAuxiliar = 0;
    }
}
void inicializaListaEncadeada(ListaEncadeada *listaEncadeada){
    listaEncadeada->primeira = (proximaCelula)malloc(sizeof(Celula));
    listaEncadeada->primeira = NULL;
}

void inserirListaEncadeada(ListaEncadeada *listaEncadeada, int linha, int coluna){
    proximaCelula proxCelula;
    proxCelula = (proximaCelula)malloc(sizeof(Celula));
    proxCelula->coluna = coluna;
    proxCelula->linha = linha;
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
        printf("%d %d\n", proxCelula->linha, proxCelula->coluna);
        proxCelula = proxCelula->proxima;
    }
}
