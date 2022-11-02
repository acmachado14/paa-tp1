#include "backtracking.h"

void main(){
    /*
    * Tenho quase certeza que as funções movientar e movimentarAuxiliar estão corretas,
    * Falta armazenar o caminho que percorrmos
    * */
    Fazenda fazenda;
    bool l = leituraDados(&fazenda);
    if(l == false){
        return;
    }
    movimentar(&fazenda);
}