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

void pausar();
void cadastroAcao();
void buscarAcao();

int main(int argc, char *argv[]) {

    int opcao, codigoAcao;
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
	    printf("0 - Sair\n");
	    printf("=========================================\n");
	    printf("Escolha uma opcao: ");
	    scanf("%d", &opcao);
	
	    switch(opcao) {
	
			case 0:
				printf("\nOk, ate mais...\n");
				pausar();
				condicao = 0;
				break;
				
	        case 1:
	            cadastroAcao();
	            break;
	
	        case 2:
	        	
	        	if(quantidadeAcoes == 0){
	        		printf("Ainda nao foi cadastrada nenhuma acao!");
	        		pausar();
	        		return 0;
				}else{
					printf("Digite o codigo da acao que deseja: ");
					scanf("%d", &codigoAcao);
					buscarAcao(codigoAcao);
				}
	        	
	        	
	        	
	            break;
	
	        case 3:
	            break;
	
	        case 4:
	            break;
	
	        case 5:
	            break;
	            
	        default:
	            printf("Opcao nao identificada!");
	    }
	}while(condicao == 1);
	    free(acoes);

    return 0;
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
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
	
	int i;
	for(i = 0; i < quantidadeAcoes; i++){
		if(acoes[i].codigo == codigo){
			printf("\n========== ACAO ENCONTRADA ==========\n");

		    printf("Codigo: %d\n", acoes[i].codigo);
		    printf("Nome: %s\n", acoes[i].nome);
		    printf("Tema: %s\n", acoes[i].tema);
		    printf("Data: %s\n", acoes[i].data);
		    printf("Publico-alvo: %s\n", acoes[i].publico);
		    printf("Responsaveis: %s\n", acoes[i].responsaveis);
		    printf("Participantes: %d\n", acoes[i].participantes);
		    pausar();
		    break;
		}
	}
	
	
	
	
	
	
	
	
}
