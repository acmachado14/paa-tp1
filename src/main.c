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
    srand(time(NULL));
    movimentar(&fazenda);
    printf("----------------------------------------------\n");
    RotaOtima rotaOtima;
    bool r = criaCassoTeste(&rotaOtima, "teste1", 5, 5);
    printf("----------------------------------------------\n");
    return 0;
}