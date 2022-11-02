#include "backtracking.h"

void main(){
    int *fibo = gerarSequencia(15);
    for(int i = 0; i < 15; i++){
        printf("%d ", fibo[i]);
    }
}