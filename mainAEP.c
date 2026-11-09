#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

typedef struct {
    int codigo;
    char nome[100];
    char tema[500];
    char data[12];
    char publico[100];
    char responsaveis[100];
    int participantes;
    char situacao[20];
} Acao;

Acao *acoes = NULL;
int quantidadeAcoes = 0;

int validarEntrada(char mensagem[]);
void lerTexto(char mensagem[], char destino[], int tamanho);
int validarData(char data[]);
int codigoExiste(int codigo);
void limparTela();
void pausar();
void cadastroAcao();
void buscarAcao(int codigo);
void listarAcoes();
void atualizarAcao(int codigo);
void exibirAcao(Acao *acao);
void resumoAcoes();

int main() {

    int opcao, codigoAcao;

    do {
        printf("\n=========================================\n");
        printf("\t\tPSE Sonora\n");
        printf("\tSaude Auditiva nas Escolas\n");
        printf("=========================================\n");
        printf("1 - Cadastro acao\n");
        printf("2 - Buscar acao\n");
        printf("3 - Listar acao\n");
        printf("4 - Atualizar situacao\n");
        printf("5 - Resumo das acoes\n");
        printf("0 - Sair\n");
        printf("=========================================\n");

        opcao = validarEntrada("Escolha uma opcao: ");

        switch(opcao) {

            case 0:
                printf("\nAte mais!\n");
                break;

            case 1:
                cadastroAcao();
                break;

            case 2:
                if(quantidadeAcoes == 0) {
                    printf("\nNenhuma acao cadastrada!\n");
                    pausar();
                } else {
                    codigoAcao = validarEntrada("\nDigite o codigo da acao: ");
                    buscarAcao(codigoAcao);
                }
                break;

            case 3:
                listarAcoes();
                break;

            case 4:
                if(quantidadeAcoes == 0) {
                    printf("\nNenhuma acao cadastrada!\n");
                    pausar();
                } else {
                    codigoAcao = validarEntrada("\nDigite o codigo da acao: ");
                    atualizarAcao(codigoAcao);
                }
                break;

            case 5:
                resumoAcoes();
                break;

            default:
                printf("\nOpcao nao identificada!\n");
                pausar();
        }

        limparTela();

    } while(opcao != 0);

    free(acoes);

    return 0;
}

int validarEntrada(char mensagem[]) {

    char entrada[100];
    char *fimDaConversao;
    long valorConvertido;

    while(1) {

        printf("%s", mensagem);

        if(fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("\nErro na leitura da entrada!\n");
            exit(EXIT_FAILURE);
        }

        // Verifica se a entrada ultrapassou o limite do buffer
        if(strchr(entrada, '\n') == NULL && !feof(stdin)) {
            int caractere;
            while((caractere = getchar()) != '\n' && caractere != EOF);
            printf("\nEntrada muito longa!\n\n");
            continue;
        }

        errno = 0;
        valorConvertido = strtol(entrada, &fimDaConversao, 10);

        // Verifica se existe um numero
        if(fimDaConversao == entrada) {
            printf("\nEntrada invalida! Digite um numero inteiro.\n\n");
            continue;
        }

        // Ignora espacos depois do numero
        while(isspace((unsigned char)*fimDaConversao)) {
            fimDaConversao++;
        }

        // Verifica caracteres adicionais e limites
        if(*fimDaConversao != '\0' || errno == ERANGE ||
           valorConvertido < INT_MIN || valorConvertido > INT_MAX) {

            printf("\nEntrada invalida! Digite um numero inteiro valido.\n\n");
            continue;
        }

        return (int)valorConvertido;
    }
}

void lerTexto(char mensagem[], char destino[], int tamanho) {

    while(1) {

        printf("%s", mensagem);

        if(fgets(destino, tamanho, stdin) == NULL) {
            printf("\nErro na leitura da entrada!\n");
            exit(EXIT_FAILURE);
        }

        if(strchr(destino, '\n') == NULL && !feof(stdin)) {
            int caractere;
            while((caractere = getchar()) != '\n' && caractere != EOF);
            printf("\nTexto muito longo! Tente novamente.\n\n");
            continue;
        }

        destino[strcspn(destino, "\n")] = '\0';

        if(strlen(destino) == 0) {
            printf("\nO campo nao pode ficar vazio!\n\n");
            continue;
        }

        break;
    }
}

int codigoExiste(int codigo) {

    int i;

    for(i = 0; i < quantidadeAcoes; i++) {
        if(acoes[i].codigo == codigo) {
            return 1;
        }
    }
    return 0;
}

void cadastroAcao() {

    Acao *temporario;

    limparTela();

    temporario = realloc(acoes, (quantidadeAcoes + 1) * sizeof(Acao));

    if(temporario == NULL) {
        printf("\nErro ao alocar memoria!\n");
        return;
    }

    acoes = temporario;

    acoes[quantidadeAcoes].codigo = quantidadeAcoes + 1;

    printf("\n=============== Nova acao ==============\n");
    printf("Codigo da acao: %d\n\n", acoes[quantidadeAcoes].codigo);

    lerTexto("Nome da acao: ", acoes[quantidadeAcoes].nome, 100);
    lerTexto("Tema da acao: ", acoes[quantidadeAcoes].tema, 500);

    do {
        lerTexto("Data (DD/MM/AAAA): ", acoes[quantidadeAcoes].data, 12);

        if(!validarData(acoes[quantidadeAcoes].data)) {
            printf("\nData invalida! Tente novamente.\n\n");
        }

    } while(!validarData(acoes[quantidadeAcoes].data));

    lerTexto("Publico-alvo: ", acoes[quantidadeAcoes].publico, 100);
    lerTexto("Responsaveis: ", acoes[quantidadeAcoes].responsaveis, 100);

    do {
        acoes[quantidadeAcoes].participantes =
            validarEntrada("Quantidade de participantes: ");

        if(acoes[quantidadeAcoes].participantes < 0) {
            printf("\nA quantidade nao pode ser negativa!\n\n");
        }

    } while(acoes[quantidadeAcoes].participantes < 0);

    strcpy(acoes[quantidadeAcoes].situacao, "Pendente");

    quantidadeAcoes++;

    printf("\nAcao cadastrada com sucesso!\n");
    printf("Situacao inicial: Pendente\n");

    pausar();
}

void buscarAcao(int codigo) {

    int i;

    limparTela();

    for(i = 0; i < quantidadeAcoes; i++) {

        if(acoes[i].codigo == codigo) {
            printf("\n========== ACAO ENCONTRADA ==========\n");
            exibirAcao(&acoes[i]);
            pausar();
            return;
        }
    }

    printf("\nNenhuma acao encontrada com esse codigo!\n");
    pausar();
}

void listarAcoes() {

    int i;

    limparTela();

    if(quantidadeAcoes == 0) {
        printf("\nNenhuma acao cadastrada!\n");
        pausar();
        return;
    }

    printf("\n=============== Acoes cadastradas ===============\n");

    for(i = 0; i < quantidadeAcoes; i++) {
        exibirAcao(&acoes[i]);
    }

    pausar();
}

void exibirAcao(Acao *acao) {

    printf("\nCodigo: %d\n", acao->codigo);
    printf("Nome: %s\n", acao->nome);
    printf("Tema: %s\n", acao->tema);
    printf("Data: %s\n", acao->data);
    printf("Publico-alvo: %s\n", acao->publico);
    printf("Responsaveis: %s\n", acao->responsaveis);
    printf("Participantes: %d\n", acao->participantes);
    printf("Situacao: %s\n", acao->situacao);
    printf("==================================================\n");
}

void atualizarAcao(int codigo) {

    int i, opcao, novaSituacao;

    limparTela();

    for(i = 0; i < quantidadeAcoes; i++) {

        if(acoes[i].codigo == codigo) {

            do {
                printf("\n========== Atualizar acao ==========\n");
                printf("Acao: %s\n", acoes[i].nome);
                printf("Situacao atual: %s\n", acoes[i].situacao);

                printf("\n1 - Editar dados da acao\n");
                printf("2 - Atualizar situacao\n");
                printf("0 - Voltar\n");

                opcao = validarEntrada("\nEscolha uma opcao: ");

                switch(opcao) {

                    case 1:

                        printf("\n========== Editar dados ==========\n");

                        lerTexto("Nome da acao: ", acoes[i].nome, 100);
                        lerTexto("Tema da acao: ", acoes[i].tema, 500);

                        do {
                            lerTexto("Data (DD/MM/AAAA): ", acoes[i].data, 11);

                            if(!validarData(acoes[i].data)) {
                                printf("\nData invalida! Tente novamente.\n\n");
                            }

                        } while(!validarData(acoes[i].data));

                        lerTexto("Publico-alvo: ", acoes[i].publico, 100);
                        lerTexto("Responsaveis: ", acoes[i].responsaveis, 100);

                        do {
                            acoes[i].participantes =
                                validarEntrada("Quantidade de participantes: ");

                            if(acoes[i].participantes < 0) {
                                printf("\nQuantidade invalida!\n\n");
                            }

                        } while(acoes[i].participantes < 0);

                        printf("\nDados atualizados com sucesso!\n");
                        pausar();
                        break;

                    case 2:

                        printf("\n========== Atualizar situacao ==========\n");
                        printf("1 - Pronta\n");
                        printf("2 - Pendente\n");
                        printf("3 - Finalizada\n");

                        novaSituacao = validarEntrada("\nNova situacao: ");

                        switch(novaSituacao) {

                            case 1:
                                strcpy(acoes[i].situacao, "Pronta");
                                printf("\nSituacao atualizada para Pronta!\n");
                                break;

                            case 2:
                                strcpy(acoes[i].situacao, "Pendente");
                                printf("\nSituacao atualizada para Pendente!\n");
                                break;

                            case 3:
                                strcpy(acoes[i].situacao, "Finalizada");
                                printf("\nSituacao atualizada para Finalizada!\n");
                                break;

                            default:
                                printf("\nSituacao nao identificada!\n");
                        }

                        pausar();
                        break;

                    case 0:
                        printf("\nVoltando ao menu principal...\n");
                        break;

                    default:
                        printf("\nOpcao nao identificada!\n");
                        pausar();
                }

                limparTela();

            } while(opcao != 0);

            return;
        }
    }

    printf("\nNenhuma acao encontrada com esse codigo!\n");
    pausar();
}

void resumoAcoes() {

    int i;
    int prontas = 0;
    int pendentes = 0;
    int finalizadas = 0;
    int totalParticipantes = 0;

    limparTela();

    for(i = 0; i < quantidadeAcoes; i++) {

        totalParticipantes += acoes[i].participantes;

        if(strcmp(acoes[i].situacao, "Pronta") == 0) {
            prontas++;
        } else if(strcmp(acoes[i].situacao, "Pendente") == 0) {
            pendentes++;
        } else if(strcmp(acoes[i].situacao, "Finalizada") == 0) {
            finalizadas++;
        }
    }

    printf("\n========== RESUMO DAS ACOES ==========\n");
    printf("Total de acoes: %d\n", quantidadeAcoes);
    printf("Acoes prontas: %d\n", prontas);
    printf("Acoes pendentes: %d\n", pendentes);
    printf("Acoes finalizadas: %d\n", finalizadas);
    printf("Total de participantes: %d\n", totalParticipantes);
    printf("======================================\n");

    pausar();
}

int validarData(char data[]) {

    int dia, mes, ano;
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i;

    if(strlen(data) != 10 || data[2] != '/' || data[5] != '/') {
        return 0;
    }

    for(i = 0; i < 10; i++) {
        if(i != 2 && i != 5 && !isdigit((unsigned char)data[i])) {
            return 0;
        }
    }

    dia = (data[0] - '0') * 10 + (data[1] - '0');
    mes = (data[3] - '0') * 10 + (data[4] - '0');

    ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');

    if(mes < 1 || mes > 12 || ano < 1) {
        return 0;
    }

    if(mes == 2 && ((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0))){
        diasPorMes[1] = 29;
    }

    return dia >= 1 && dia <= diasPorMes[mes - 1];
}

void limparTela() {

    int i;

    for(i = 0; i < 25; i++) {
        printf("\n");
    }
}

void pausar() {

    printf("\nPressione ENTER para continuar...");
    getchar();
}
