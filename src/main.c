#include "backtracking.h"

void main(){
    /*
    * As funções movientar e movimentarAuxiliar estão corretas, para o caso de teste apresentado
    * na especificação do tp
    * */
    Fazenda fazenda;
    bool l = leituraDados(&fazenda);
    if(l == false){
        return;
    }

    clock_t tempoIncial, tempoFinal;
    tempoIncial = clock();

    movimentar(&fazenda);

    tempoFinal = clock();
    printf("Tempo de execucao: %f ms\n", ((float)(tempoFinal-tempoIncial)) * 1000/(CLOCKS_PER_SEC));
}