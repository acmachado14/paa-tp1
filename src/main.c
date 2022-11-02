#include "backtracking.h"

void main(){
    int **arestas;
    arestas = (int**)malloc(quantidadeVertices * sizeof(int*));
    for(i = 0; i < quantidadeVertices; i++){
        arestas[i] = (int*)malloc(quantidadeVertices * sizeof(int));
    }

}