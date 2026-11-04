#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[100];
    char tema[500];
    char data[11];
    char publico[100];
    char responsaveis[100];
    int participantes;
} Acao;


Acao *acoes = NULL;
int quantidadeAcoes = 0;

void cadastroAcao();
void buscarAcao();

int main(int argc, char *argv[]) {

    int opcao;
    int condicao = 1;
    
	do{
	    printf("\n=========================================\n");
	    printf("\n\t\tPSE Sonora\n");
	    printf("\n\tSaude Auditiva nas Escolas\n");
	    printf("\n=========================================\n");
	    printf("1 - Cadastro acao\n");
	    printf("2 - Buscar acao\n");
	    printf("3 - Listar acao\n");
	    printf("4 - Atualizar situacao\n");
	    printf("5 - Resumo das acoes\n");
	    printf("6 - Avaliacao de conhecimento\n");
	    printf("7 - Ranking de participacao\n");
	    printf("0 - Sair\n");
	    printf("=========================================\n");
	    printf("Escolha uma opcao: ");
	    scanf("%d", &opcao);
	
	    switch(opcao) {
	
			case 0:
				printf("Ok, ate mais...");
				condicao = 0;
				break;
				
	        case 1:
	            cadastroAcao();
	            break;
	
	        case 2:
	        	
	        	if(quantidadeAcoes == 0){
	        		printf("Ainda nao foi cadastrada nenhuma acao!");
	        		scanf("");
	        		return 0;
				}else{
					printf("Digite o codigo da acao que deseja: ");
				}
	        	
	        	
	        	
	            break;
	
	        case 3:
	            break;
	
	        case 4:
	            break;
	
	        case 5:
	            break;
	
	        case 6:
	            break;
	
	        case 7:
	            break;
	
	        default:
	            printf("Opcao nao identificada!");
	    }
	}while(condicao == 1);
	    free(acoes);

    return 0;
}

void cadastroAcao() {

    Acao *temp = realloc(acoes, (quantidadeAcoes + 1) * sizeof(Acao));

    if (temp == NULL) {
        printf("\nErro ao alocar memoria!\n");
        return;
    }

    acoes = temp;

    acoes[quantidadeAcoes].codigo = quantidadeAcoes + 1;

    printf("\n=============== Nova acao ==============\n");

	printf("Codigo da acao: %d\n\n", acoes[quantidadeAcoes].codigo);

    printf("Nome da acao: ");
    scanf(" %99[^\n]", acoes[quantidadeAcoes].nome);

    printf("Tema da acao: ");
    scanf(" %499[^\n]", acoes[quantidadeAcoes].tema);

    printf("Data (DD/MM/AAAA): ");
    scanf(" %10s", acoes[quantidadeAcoes].data);

    printf("Publico-alvo: ");
    scanf(" %99[^\n]", acoes[quantidadeAcoes].publico);

    printf("Responsaveis: ");
    scanf(" %99[^\n]", acoes[quantidadeAcoes].responsaveis);

    printf("Quantidade de participantes: ");
    scanf("%d", &acoes[quantidadeAcoes].participantes);

    quantidadeAcoes++;

    printf("\nAcao cadastrada com sucesso!\n");
}

void buscarAcao(int codigo){
	
	
	
	
	
	
	
	
	
	
}
