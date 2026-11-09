#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#define ARQUIVO_DADOS "acoes.dat"

typedef struct {
    int codigo;
    char nome[100];
    char escola[100];
    char tema[500];
    char data[12];
    char publico[100];
    char responsaveis[100];
    int participantes;
    int participantesPrevistos;
    int participantesReais;
    char situacao[20];
} Acao;

Acao *acoes = NULL;
int quantidadeAcoes = 0;

int validarEntrada(char mensagem[]);
void lerTexto(char mensagem[], char destino[], int tamanho);
int validarData(char data[]);
int lerQuantidade(char mensagem[]);
int contemTexto(char texto[], char termo[]);
void limparTela();
void pausar();
void cadastroAcao();
void menuBusca();
void buscarAcao(int codigo);
void buscarPorTexto(int campo, char termo[]);
void listarAcoes();
void atualizarAcao(int codigo);
void atualizarSituacao(Acao *acao);
void exibirAcao(Acao *acao);
void resumoAcoes();
void salvarAcoes();
void carregarAcoes();

int main() {

    int opcao, codigoAcao;
    carregarAcoes();
    
    do {
        printf("\n=========================================\n");
        printf("\t\tPSE Sonora\n");
        printf("\tSaude Auditiva nas Escolas\n");
        printf("=========================================\n");
        printf("1 - Cadastro acao\n");
        printf("2 - Buscar acao\n");
        printf("3 - Listar acao\n");
        printf("4 - Atualizar acao\n");
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
                    menuBusca();
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
    
    salvarAcoes();
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

int lerQuantidade(char mensagem[]) {

    int valor;

    do {
        valor = validarEntrada(mensagem);

        if(valor < 0) {
            printf("\nA quantidade nao pode ser negativa!\n\n");
        }

    } while(valor < 0);

    return valor;
}

int contemTexto(char texto[], char termo[]) {

    char textoMinusculo[500];
    char termoMinusculo[500];
    int i;

    for(i = 0; texto[i] != '\0' && i < 499; i++) {
        textoMinusculo[i] = tolower((unsigned char)texto[i]);
    }
    textoMinusculo[i] = '\0';

    for(i = 0; termo[i] != '\0' && i < 499; i++) {
        termoMinusculo[i] = tolower((unsigned char)termo[i]);
    }
    termoMinusculo[i] = '\0';

    return strstr(textoMinusculo, termoMinusculo) != NULL;
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
    lerTexto("Escola: ", acoes[quantidadeAcoes].escola, 100);              
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
        acoes[quantidadeAcoes].participantesPrevistos =                     
            validarEntrada("Quantidade de participantes: ");

        if(acoes[quantidadeAcoes].participantesPrevistos < 0) {            
            printf("\nA quantidade nao pode ser negativa!\n\n");
        }

    } while(acoes[quantidadeAcoes].participantesPrevistos < 0);             

    acoes[quantidadeAcoes].participantesReais = 0;                          

    strcpy(acoes[quantidadeAcoes].situacao, "Planejada");                   

    quantidadeAcoes++;

    salvarAcoes();                                                          

    printf("\nAcao cadastrada com sucesso!\n");
    printf("Situacao inicial: Planejada\n");                                

    pausar();
}

void menuBusca() {

    int opcao;
    char termo[500];

    limparTela();

    printf("\n=============== Buscar acao ===============\n");
    printf("1 - Buscar por codigo\n");
    printf("2 - Buscar por escola\n");
    printf("3 - Buscar por tema\n");
    printf("0 - Voltar\n");

    opcao = validarEntrada("\nEscolha uma opcao: ");

    switch(opcao) {

        case 1:
            buscarAcao(validarEntrada("\nDigite o codigo da acao: "));
            break;

        case 2:
            lerTexto("\nDigite o nome (ou parte do nome) da escola: ", termo, 100);
            buscarPorTexto(1, termo);
            break;

        case 3:
            lerTexto("\nDigite o tema (ou parte do tema): ", termo, 500);
            buscarPorTexto(2, termo);
            break;

        case 0:
            break;

        default:
            printf("\nOpcao nao identificada!\n");
            pausar();
    }
}

void buscarPorTexto(int campo, char termo[]) {

    int i;
    int encontradas = 0;
    char *textoDoCampo;

    limparTela();

    printf("\n========== RESULTADO DA BUSCA: \"%s\" ==========\n", termo);

    for(i = 0; i < quantidadeAcoes; i++) {

        if(campo == 1) {
            textoDoCampo = acoes[i].escola;
        } else {
            textoDoCampo = acoes[i].tema;
        }

        if(contemTexto(textoDoCampo, termo)) {
            exibirAcao(&acoes[i]);
            encontradas++;
        }
    }

    if(encontradas == 0) {
        printf("\nNenhuma acao encontrada!\n");
    } else {
        printf("\n%d acao(oes) encontrada(s).\n", encontradas);
    }

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
    printf("Escola: %s\n", acao->escola);
    printf("Tema: %s\n", acao->tema);
    printf("Data: %s\n", acao->data);
    printf("Publico-alvo: %s\n", acao->publico);
    printf("Responsaveis: %s\n", acao->responsaveis);
    printf("Participantes previstos: %d\n", acao->participantesPrevistos);

    if(strcmp(acao->situacao, "Realizada") == 0) {
        printf("Participantes reais: %d\n", acao->participantesReais);
    }

    printf("Situacao: %s\n", acao->situacao);
    printf("==================================================\n");
}

void atualizarAcao(int codigo) {

    int i, opcao;

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
                        lerTexto("Escola: ", acoes[i].escola, 100);
                        lerTexto("Tema da acao: ", acoes[i].tema, 500);

                        do {
                            lerTexto("Data (DD/MM/AAAA): ", acoes[i].data, 12);

                            if(!validarData(acoes[i].data)) {
                                printf("\nData invalida! Tente novamente.\n\n");
                            }

                        } while(!validarData(acoes[i].data));

                        lerTexto("Publico-alvo: ", acoes[i].publico, 100);
                        lerTexto("Responsaveis: ", acoes[i].responsaveis, 100);

                        acoes[i].participantesPrevistos =
                            lerQuantidade("Quantidade prevista de participantes: ");

                        salvarAcoes();

                        printf("\nDados atualizados com sucesso!\n");
                        pausar();
                        break;

                    case 2:
                        atualizarSituacao(&acoes[i]);
                        salvarAcoes();
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

void atualizarSituacao(Acao *acao) {

    int novaSituacao;

    printf("\n========== Atualizar situacao ==========\n");
    printf("1 - Planejada\n");
    printf("2 - Realizada\n");
    printf("3 - Cancelada\n");

    novaSituacao = validarEntrada("\nNova situacao: ");

    switch(novaSituacao) {

        case 1:
            strcpy(acao->situacao, "Planejada");
            acao->participantesReais = 0;
            printf("\nSituacao atualizada para Planejada!\n");
            break;

        case 2:
            strcpy(acao->situacao, "Realizada");
            printf("\nParticipantes previstos: %d\n", acao->participantesPrevistos);
            acao->participantesReais =
                lerQuantidade("Quantidade real de participantes: ");
            printf("\nSituacao atualizada para Realizada!\n");
            break;

        case 3:
            strcpy(acao->situacao, "Cancelada");
            acao->participantesReais = 0;
            printf("\nSituacao atualizada para Cancelada!\n");
            break;

        default:
            printf("\nSituacao nao identificada!\n");
    }
}

void resumoAcoes() {

    int i;
    int planejadas = 0;
    int realizadas = 0;
    int canceladas = 0;
    int previstosRealizadas = 0;
    int totalParticipantes = 0;
    float percentual;

    limparTela();

    for(i = 0; i < quantidadeAcoes; i++) {

        if(strcmp(acoes[i].situacao, "Planejada") == 0) {
            planejadas++;
        } else if(strcmp(acoes[i].situacao, "Realizada") == 0) {
            realizadas++;
            totalParticipantes += acoes[i].participantesReais;
            previstosRealizadas += acoes[i].participantesPrevistos;
        } else if(strcmp(acoes[i].situacao, "Cancelada") == 0) {
            canceladas++;
        }
    }

    printf("\n========== RESUMO DAS ACOES ==========\n");
    printf("Total de acoes: %d\n", quantidadeAcoes);
    printf("Acoes planejadas: %d\n", planejadas);
    printf("Acoes realizadas: %d\n", realizadas);
    printf("Acoes canceladas: %d\n", canceladas);
    printf("Total de participantes (acoes realizadas): %d\n", totalParticipantes);

    if(previstosRealizadas > 0) {
        percentual = (float)totalParticipantes / previstosRealizadas * 100;
        printf("Percentual de participacao: %.1f%%\n", percentual);
    } else {
        printf("Percentual de participacao: sem acoes realizadas\n");
    }

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

// Grava todas as acoes no arquivo: primeiro a quantidade, depois o vetor
void salvarAcoes() {

    FILE *arquivo = fopen(ARQUIVO_DADOS, "wb");

    if(arquivo == NULL) {
        printf("\nAviso: nao foi possivel salvar os dados!\n");
        return;
    }

    fwrite(&quantidadeAcoes, sizeof(int), 1, arquivo);

    if(quantidadeAcoes > 0) {
        fwrite(acoes, sizeof(Acao), quantidadeAcoes, arquivo);
    }

    fclose(arquivo);
}

void carregarAcoes() {

    FILE *arquivo = fopen(ARQUIVO_DADOS, "rb");
    int quantidade;

    if(arquivo == NULL) {
        return;
    }

    if(fread(&quantidade, sizeof(int), 1, arquivo) != 1 || quantidade <= 0) {
        fclose(arquivo);
        return;
    }

    acoes = malloc(quantidade * sizeof(Acao));

    if(acoes == NULL) {
        printf("\nErro ao alocar memoria para carregar os dados!\n");
        fclose(arquivo);
        return;
    }

    if(fread(acoes, sizeof(Acao), quantidade, arquivo) != (size_t)quantidade) {
        printf("\nAviso: arquivo de dados corrompido. Iniciando sem acoes.\n");
        free(acoes);
        acoes = NULL;
        fclose(arquivo);
        return;
    }

    quantidadeAcoes = quantidade;

    fclose(arquivo);
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
