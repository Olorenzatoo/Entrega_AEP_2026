
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
    char situacao[20];
} Acao;

Acao *acoes = NULL;
int quantidadeAcoes = 0;

void limparTela();
void pausar();
void cadastroAcao();
void buscarAcao(int codigo);
void listarAcoes();
void atualizarAcao(int codigo);


int main(int argc, char *argv[]) {

    int opcao, codigoAcao;
    int condicao = 1;

    do {

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
                condicao = 0;
                pausar();

                break;

            case 1:
                cadastroAcao();
                break;

            case 2:

                if(quantidadeAcoes == 0) {

                    printf("\nAinda nao foi cadastrada nenhuma acao!");

                } else {

                    printf("\nDigite o codigo da acao que deseja: ");
                    scanf("%d", &codigoAcao);

                    buscarAcao(codigoAcao);
                }

                break;

            case 3:
                listarAcoes();
                break;

            case 4:

                if(quantidadeAcoes == 0) {

                    printf("\nAinda nao foi cadastrada nenhuma acao!");

                } else {

                    printf("\nDigite o codigo da acao: ");
                    scanf("%d", &codigoAcao);

                    atualizarAcao(codigoAcao);
                }

                break;

            case 5:
                break;

            default:
                printf("\nOpcao nao identificada!");
                pausar();
        }

	limparTela();

    } while(condicao == 1);

    free(acoes);

    return 0;
}


void pausar() {

    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();

}


void limparTela() {

    int i;

    for(i = 0; i < 25; i++) {

        printf("\n");

    }
}


void cadastroAcao() {

	limparTela();

    Acao *temp = realloc(acoes, (quantidadeAcoes + 1) * sizeof(Acao));

    if(temp == NULL) {

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

    strcpy(acoes[quantidadeAcoes].situacao, "Pendente");

    quantidadeAcoes++;

    printf("\nAcao cadastrada com sucesso!\n");
    printf("Situacao inicial: Pendente\n");

}


void buscarAcao(int codigo) {

	limparTela();
	
    int i;
    int encontrada = 0;

    for(i = 0; i < quantidadeAcoes; i++) {

        if(acoes[i].codigo == codigo) {

            encontrada = 1;

            printf("\n========== ACAO ENCONTRADA ==========\n");

            printf("Codigo: %d\n", acoes[i].codigo);
            printf("Nome: %s\n", acoes[i].nome);
            printf("Tema: %s\n", acoes[i].tema);
            printf("Data: %s\n", acoes[i].data);
            printf("Publico-alvo: %s\n", acoes[i].publico);
            printf("Responsaveis: %s\n", acoes[i].responsaveis);
            printf("Participantes: %d\n", acoes[i].participantes);
            printf("Situacao: %s\n", acoes[i].situacao);

            printf("=====================================\n");

            break;

        }
	
    }

    if(encontrada == 0) {

        printf("\nNenhuma acao encontrada com esse codigo!\n");

    }
	pausar();
}


void listarAcoes() {

    int i;

    if(quantidadeAcoes == 0) {

        printf("\nAinda nao foi cadastrada nenhuma acao!\n");
        return;

    }

	limparTela();

    printf("\n=============== Acoes cadastradas ===============\n");

    for(i = 0; i < quantidadeAcoes; i++) {

        printf("\nCodigo: %d\n", acoes[i].codigo);
        printf("Nome: %s\n", acoes[i].nome);
        printf("Tema: %s\n", acoes[i].tema);
        printf("Data: %s\n", acoes[i].data);
        printf("Publico-alvo: %s\n", acoes[i].publico);
        printf("Responsaveis: %s\n", acoes[i].responsaveis);
        printf("Participantes: %d\n", acoes[i].participantes);
        printf("Situacao: %s\n", acoes[i].situacao);

        printf("==================================================\n");

    }
    
	pausar();
}


void atualizarAcao(int codigo) {

    int i;
    int encontrada = 0;
    int opcao;
    int novaSituacao;

	limparTela();

    for(i = 0; i < quantidadeAcoes; i++) {

        if(acoes[i].codigo == codigo) {

            encontrada = 1;

            do {

                printf("\n========== Atualizar acao ==========\n");

                printf("Acao: %s\n", acoes[i].nome);
                printf("Situacao atual: %s\n", acoes[i].situacao);

                printf("\n1 - Editar dados da acao\n");
                printf("2 - Atualizar situacao\n");
                printf("0 - Voltar\n");

                printf("\nEscolha uma opcao: ");
                scanf("%d", &opcao);

                switch(opcao) {

                    case 1:

                        printf("\n========== Editar dados ==========\n");

                        printf("Nome da acao: ");
                        scanf(" %99[^\n]", acoes[i].nome);

                        printf("Tema da acao: ");
                        scanf(" %499[^\n]", acoes[i].tema);

                        printf("Data (DD/MM/AAAA): ");
                        scanf(" %10s", acoes[i].data);

                        printf("Publico-alvo: ");
                        scanf(" %99[^\n]", acoes[i].publico);

                        printf("Responsaveis: ");
                        scanf(" %99[^\n]", acoes[i].responsaveis);

                        printf("Quantidade de participantes: ");
                        scanf("%d", &acoes[i].participantes);

                        printf("\nDados da acao atualizados com sucesso!\n");

						pausar();
						limparTela();
                        break;


                    case 2:

                        printf("\n========== Atualizar situacao ==========\n");

                        printf("1 - Pronta\n");
                        printf("2 - Pendente\n");
                        printf("3 - Finalizada\n");

                        printf("\nNova situacao: ");
                        scanf("%d", &novaSituacao);

                        switch(novaSituacao) {

                            case 1:

                                strcpy(acoes[i].situacao, "Pronta");

                                printf("\nSituacao atualizada para Pronta!\n");
									
								limparTela();	
                                break;


                            case 2:

                                strcpy(acoes[i].situacao, "Pendente");

                                printf("\nSituacao atualizada para Pendente!\n");
								
								limparTela();
                                break;


                            case 3:

                                strcpy(acoes[i].situacao, "Finalizada");

                                printf("\nSituacao atualizada para Finalizada!\n");

								limparTela();
                                break;


                            default:

                                printf("\nSituacao nao identificada!\n");

                        }

                        break;


                    case 0:

                        printf("\nVoltando ao menu principal...\n");

                        break;


                    default:

                        printf("\nOpcao nao identificada!\n");

                }

            } while(opcao != 0);

            break;

        }

    }

    if(encontrada == 0) {

        printf("\nNenhuma acao encontrada com esse codigo!\n");

    }
    
    pausar();

}
