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
    movimentar(&fazenda);
}