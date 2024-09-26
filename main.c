#include <stdio.h>      // Biblioteca padrão para entrada e saída
#include <stdlib.h>     // Biblioteca para funções de alocação de memória e controle do sistema
#include <string.h>     // Biblioteca para manipulação de strings
#include <time.h>       // Biblioteca para manipulação de tempo
#include<locale.h>      //Biblioteca para reconhecer pontuação em portugues.
#include "main.h"




//variaveis
int senha; //Armazena a senha digitada pelo tecnico.
int opcao_tecnica; //Armazena a opção solicitada no menu do tecnico.
int ticket; //Armazena ticket do menu principal.


//Funções

//Imprime o nome da empresa e horas
void imprime_cabec(void)
{
    printf("******************************\n");
    printf("* \t\tTICKETING\t\t *\n");
    printf("******************************\n\n");

    // Exibe o horário atual
    time_t tempo;
    time(&tempo);
    struct tm *tempo0 = localtime(&tempo);
    printf("*___________________________*\n");
    printf("|  Horario atual: %02d:%02d:%02d   |\n", tempo0->tm_hour, tempo0->tm_min, tempo0->tm_sec);
    printf("*___________________________*\n\n");
    return;
}

//Imprime uma imagem de bem vindo
void bemvindo(void)
{
    // Exibe uma mensagem de boas-vindas em arte de texto
    printf("BBBB   EEEEE M   M      V   V  I  N   N DDDD   OOO  \n");
    printf("B   B  E     MM MM      V   V  I  NN  N D   D O   O \n");
    printf("BBBB   EEEE  M M M      V   V  I  N N N D   D O   O \n");
    printf("B   B  E     M   M       V V   I  N  NN D   D O   O \n");
    printf("BBBB   EEEEE M   M        V    I  N   N DDDD   OOO  \n\n");
    printf("\n------- Bem vindo ao Ticketing  -------\n");

    return;
}

//Limpa a tela.
void limpa(void)
{
    system("cls");
    return;
}

// Função para registrar um novo chamado
void registrarChamado(Chamado* chamado, int id) {
    chamado->id = id;   // Atribui o ID ao chamado

    // Atribui o Status ao chamado como "ABERTO"
    strncpy(chamado->status, "ABERTO", MAX_TAM);
    chamado->resolucao[0] = '\0'; // Inicializa a resolução como uma string vazia

    printf("Digite o nome do cliente: ");
    fgets(chamado->nome, MAX_TAM, stdin);   // Lê o nome do cliente
    chamado->nome[strcspn(chamado->nome, "\n")] = '\0'; // Remove a nova linha gerada pelo `fgets`

    printf("Digite o telefone do cliente: ");
    fgets(chamado->telefone, MAX_TAM, stdin);  // Lê o telefone do cliente
    chamado->telefone[strcspn(chamado->telefone, "\n")] = '\0'; // Remove a nova linha

    printf("Digite o email do cliente: ");
    fgets(chamado->email, MAX_TAM, stdin);  // Lê o email do cliente
    chamado->email[strcspn(chamado->email, "\n")] = '\0'; // Remove a nova linha

    printf("Digite o texto do chamado: ");
    fgets(chamado->texto, MAX_TAM, stdin);  // Lê a descrição do chamado
    chamado->texto[strcspn(chamado->texto, "\n")] = '\0'; // Remove a nova linha
    limpa();
}

// Função para exibir as informações de um chamado
void exibirChamado(const Chamado* chamado) {
    printf("\nChamado Registrado:\n");
    printf("ID: %d\n", chamado->id);          // Exibe o ID do chamado
    printf("Nome: %s\n", chamado->nome);      // Exibe o nome do cliente
    printf("Telefone: %s\n", chamado->telefone);  // Exibe o telefone do cliente
    printf("Email: %s\n", chamado->email);    // Exibe o email do cliente
    printf("Texto: %s\n", chamado->texto);    // Exibe a descrição do chamado
    printf("Status: %s\n", chamado->status);  // Exibe o status do chamado
    if (chamado->resolucao[0] != '\0') {      // Exibe a resolução se estiver presente
        printf("Resolução: %s\n", chamado->resolucao);
    } else {
        printf("Resolução: Nenhuma\n\n");
    }
}

// Função para consultar um chamado pelo ID
void consultarChamadoPorID(Chamado** chamados, int numChamados, int id) {
    // Percorre a lista de chamados
    for (int i = 0; i < numChamados; i++) {
        if (chamados[i]->id == id) {    // Verifica se o ID corresponde
            exibirChamado(chamados[i]); // Se encontrado, exibe o chamado
            return;
        }
    }
    // Se o ID não for encontrado, informa que o chamado não foi achado
    printf("Chamado com ID %d não encontrado.\n", id);
}


// Função para atualizar o status e a resolução de um chamado
void atualizarChamado(Chamado** chamados, int numChamados, int id) {
    // Percorre a lista de chamados
    for (int i = 0; i < numChamados; i++) {
        if (chamados[i]->id == id) {    // Verifica se o ID corresponde
            printf("Chamado encontrado.\n");
            printf("Digite o novo status (ex: 'FECHADO', 'PENDENTE'): ");
            fgets(chamados[i]->status, MAX_TAM, stdin);
            chamados[i]->status[strcspn(chamados[i]->status, "\n")] = '\0'; // Remove a nova linha

            printf("Digite a resolução do chamado: ");
            fgets(chamados[i]->resolucao, MAX_TAM, stdin);
            chamados[i]->resolucao[strcspn(chamados[i]->resolucao, "\n")] = '\0'; // Remove a nova linha

            printf("Chamado atualizado com sucesso.\n");
            return;
        }
    }
    // Se o ID não for encontrado, informa que o chamado não foi achado
    printf("Chamado com ID %d não encontrado.\n", id);
}

// Função para listar chamados por status
void listarChamadosPorStatus(Chamado** chamados, int numChamados, const char* statusDesejado) {
    int encontrado = 0;
    for (int i = 0; i < numChamados; i++) {
        if (strcmp(chamados[i]->status, statusDesejado) == 0) {
            exibirChamado(chamados[i]);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("Nenhum chamado com status '%s' encontrado.\n", statusDesejado);
    }
}

//Valida se a senha do tecnico esta correta ou não.
void login_tecnico(){
    // Obter a data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int dia = tm.tm_mday;
    int mes = tm.tm_mon + 1; // tm_mon retorna meses de 0 a 11
    int ano = tm.tm_year % 100; // Obter os dois últimos dígitos do ano

    int senha_correta = dia * mes * ano;

    printf("Digite a senha para a área técnica: ");
    scanf("%d", &senha);
    if (senha == senha_correta) {
        menu_tecnico();
    }else{
        printf("Senha incorreta\n");
        printf("Deseja voltar ao menu principal?");
        scanf("%d", &ticket);
    }
    return;
}

//Imprime o menu do tecnico
void menu_tecnico (){
  // Menu da área técnica
        printf("\n----- Área Técnica -----\n");
        printf("Escolha a opção desejada:\n");
        printf("1. Consultar chamados ABERTOS\n");
        printf("2. Consultar chamados FECHADOS\n");
        printf("3. Atualizar chamado\n");
        printf("4. Voltar ao menu principal\n");
        scanf("%d", &opcao_tecnica);
        return;
}

//codigo fonte
int main (){

        setlocale(LC_ALL, "Portuguese");

        Chamado** chamados = NULL;   // Ponteiro para um vetor de ponteiros de chamados
        int numChamados = 0;         // Número de chamados registrados
        int id = 1;                  // ID inicial para os chamados
        int opcao, ticket, senha;    // Variáveis para armazenar a opção do menu, ticket e senha
        char resposta[4];            // Resposta do usuário para continuar registrando chamados (sim/não)
        int consultaID;              // Armazena o ID a ser consultado

        imprime_cabec();
        bemvindo();

// Loop principal do programa
while (1) {

        // Exibe o menu principal

        printf("Escolha a opcao desejada:\n");
        printf("1-ABRIR TICKET\n2-CONSULTAR TICKET POR ID\n3-AREA TECNICA\n4-SAIR\n");
        scanf("%d", &ticket);
        getchar(); // Consumir o caractere de nova linha deixado pelo scanf
        limpa();

        switch (ticket) {
            case 1:
                // Loop para registrar chamados enquanto a resposta for "sim"
                limpa();
                imprime_cabec();
                // Realoca memória para armazenar um novo chamado
                chamados = (Chamado**)realloc(chamados, (numChamados + 1) * sizeof(Chamado*));
                if (chamados == NULL) {
                printf("Erro ao alocar memória.\n");
                limpa();
                exit(1);
                }

                // Aloca memória para o novo chamado
                chamados[numChamados] = (Chamado*)malloc(sizeof(Chamado));
                if (chamados[numChamados] == NULL) {
                printf("Erro ao alocar memória.\n");
                limpa();
                exit(1);
                }

                // Registra o chamado
                registrarChamado(chamados[numChamados], id);
                // Exibe o chamado registrado
                imprime_cabec();
                exibirChamado(chamados[numChamados]);

                numChamados++; // Incrementa o número de chamados registrados
                id++;          // Incrementa o ID do próximo chamado
                break;

            case 2:
                // Consulta chamado por ID
                printf("Digite o ID do chamado a ser consultado: ");
                scanf("%d", &consultaID);
                getchar(); // Consumir nova linha
                consultarChamadoPorID(chamados, numChamados, consultaID); // Chama a função para consultar
                break;

            case 3:
                // Área técnica protegida por senha
                login_tecnico();



                }


}
    return 0;
}
