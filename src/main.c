#include "backtracking.h"

int main(){
    /*
    * As funções movientar e movimentarAuxiliar estão corretas, para o caso de teste apresentado
    * na especificação do tp
    * */
    Fazenda fazenda;
    bool l = leituraDados(&fazenda);
    if(l == false){
        return 0;
    }

    clock_t tempoIncial = clock();

    movimentar(&fazenda, tempoIncial);

    return 0;
}