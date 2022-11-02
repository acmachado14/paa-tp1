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
    int *fibo = gerarSequencia(15);
    for(int i = 0; i < 15; i++){
        printf("%d ", fibo[i]);
    }
}