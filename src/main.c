#include "backtracking.h"

int main(){
    Fazenda fazenda;
    RotaOtima rotaOtima;
    int continuarExecucao = 1;
    int gerarTesteAleatorio, N, M;
    bool leituraDadosOK, criaTesteOK;
    char arquivoLeitura[50];
    char arquivoCriar[50];
    while (continuarExecucao == 1){
        printf("-----------------------------------------------------------------------------------\n");
        srand(time(NULL));
        do{
            printf("Deseja gerar um teste aleatorio [0 - Nao/1 - Sim]: ");
            scanf("%d", &gerarTesteAleatorio);
        } while (gerarTesteAleatorio < 0 || gerarTesteAleatorio > 1);

        if(gerarTesteAleatorio == 1){
            printf("Digite o nome do arquivo de onde deve ser lido os dados: ");
            scanf("%s", &arquivoCriar);
            printf("Digite quantas linhas deve ter o campo: ");
            scanf("%d", &N);
            printf("Digite quantas colunas deve ter o campo: ");
            scanf("%d", &M);
            criaTesteOK = criaCassoTeste(arquivoCriar, N, M);
        }
        printf("\n");
        printf("Digite o nome do arquivo de onde deve ser lido os dados: ");
        scanf("%s", &arquivoLeitura);

        leituraDadosOK = leituraDados(&fazenda, &rotaOtima, arquivoLeitura);
        if(leituraDadosOK == true){
            clock_t tempoIncial = clock();
            printf("------------------------------------------------------------------------------------------------\n");
            movimentar(&fazenda, &rotaOtima , tempoIncial);
            printf("------------------------------------------------------------------------------------------------\n");
        }
        printf("\n");
        do{
            printf("Deseja executar o programa outra vez [0 - Nao/1 - Sim]: ");
            scanf("%d", &continuarExecucao);
        } while (continuarExecucao < 0 || continuarExecucao > 1);
        
    }
    return 0;
}