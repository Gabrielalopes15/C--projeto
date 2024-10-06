#include <stdio.h>      // Biblioteca padrão para entrada e saída
#include <stdlib.h>     // Biblioteca para funções de alocação de memória e controle do sistema
#include <string.h>     // Biblioteca para manipulação de strings
#include <time.h>       // Biblioteca para manipulação de tempo
#include <locale.h>      //Biblioteca para reconhecer pontuação em portugues.
#include <unistd.h>
#include <windows.h> //Biblioteca para mudar cor do texto

#include "main.h"




//variaveis
int senha; //Armazena a senha digitada pelo tecnico.
int opcao_tecnica; //Armazena a opção solicitada no menu do tecnico.
int ticket; //Armazena ticket do menu principal.


//Funções

//Função para mudar cor e fundo de texto.
void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

//Imprime o nome da empresa e horas
void imprime_cabec(void)
{
        // Exibe o horário atual
    time_t tempo;
    time(&tempo);
    struct tm *tempo0 = localtime(&tempo);
    setColor(15, 1); // 1 = azul, 15 = fundo branco
    printf("                                                                                             ______________________    \n");

    printf("   ******************************                                                           | Horario atual: %02d:%02d |   \n", tempo0->tm_hour, tempo0->tm_min);
    printf("   *         TICKETING          *                                                           |______________________|   \n");
    printf("   ******************************                                                                                      \n");
    printf("                                                                                                                       \n");
    printf("______________________________________________________________________________________________________________________ \n");
    setColor(7, 0); // Volta as cores ao padrão windows.
    return;
}


//Imprime uma imagem de bem vindo
void bemvindo(void)
{
    // Exibe uma mensagem de boas-vindas em arte de texto
    setColor(1, 0); // 7 = cinza claro
    printf("\n\t\t\t\tBBBB   EEEEE M   M      V   V  I  N   N DDDD   OOO  \n");
    printf("\t\t\t\tB   B  E     MM MM      V   V  I  NN  N D   D O   O \n");
    printf("\t\t\t\tBBBB   EEEE  M M M      V   V  I  N N N D   D O   O \n");
    printf("\t\t\t\tB   B  E     M   M       V V   I  N  NN D   D O   O \n");
    printf("\t\t\t\tBBBB   EEEEE M   M        V    I  N   N DDDD   OOO  \n\n");
    printf("\n\t\t\t\t\t------- Bem vindo ao Ticketing  -------\n\n");
    setColor(7, 0); // Volta as cores ao padrão windows.
    return;
}

//Função para exibir tela de carregando.
void carregando (void){
    int i;
    for(i = 0; i < 2; i++){
        setColor(9,0);
        printf("\n\n\t _______________\n");
        printf("\t| Carregando.   |\n");
        printf("\t|_______________|\n");
        sleep(1);
        limpa();
        setColor(9,0);
        printf("\n\n\t _______________\n");
        printf("\t| Carregando..  |\n");
        printf("\t|_______________|\n");
        sleep(1);
        limpa();
        setColor(9,0);
        printf("\n\n\t _______________\n");
        printf("\t| Carregando... |\n");
        printf("\t|_______________|\n");
        sleep(1);
        limpa();
        setColor(7,0);
    }
return;

}

//Limpa a tela.
void limpa(void)
{
    system("cls");
    imprime_cabec();
    return;
}

// Função para registrar um novo chamado
void registrarChamado(Chamado* chamado, int id) {
    chamado->id = id;   // Atribui o ID ao chamado

    // Atribui o Status ao chamado como "ABERTO"
    strncpy(chamado->status, "ABERTO", MAX_TAM);
    chamado->resolucao[0] = '\0'; // Inicializa a resolução como uma string vazia

    printf("\n\n\tDigite o nome do cliente:\n\n\t ");
    fgets(chamado->nome, MAX_TAM, stdin);   // Lê o nome do cliente
    chamado->nome[strcspn(chamado->nome, "\n")] = '\0'; // Remove a nova linha gerada pelo `fgets`
    limpa();

    printf("\n\n\tDigite o telefone do cliente:\n\n\t ");
    fgets(chamado->telefone, MAX_TAM, stdin);  // Lê o telefone do cliente
    chamado->telefone[strcspn(chamado->telefone, "\n")] = '\0'; // Remove a nova linha
    limpa();

    printf("\n\n\tDigite o email do cliente:\n\n\t ");
    fgets(chamado->email, MAX_TAM, stdin);  // Lê o email do cliente
    chamado->email[strcspn(chamado->email, "\n")] = '\0'; // Remove a nova linha
    limpa();

    printf("\n\n\tDigite o texto do chamado:\n\n\t ");
    fgets(chamado->texto, MAX_TAM, stdin);  // Lê a descrição do chamado
    chamado->texto[strcspn(chamado->texto, "\n")] = '\0'; // Remove a nova linha
    limpa();

}

// Função para exibir as informações de um chamado
void exibirChamado(const Chamado* chamado) {

    printf("\a\n\t\t\t\t\tChamado Registrado:\n\n");
    printf("\t\t ___________________________________________________________________________________________\n");
    printf("\t\t| ID: %-80d      |    \n", chamado->id);          // Exibe o ID do chamado
    printf("\t\t| Nome: %-80s    |    \n", chamado->nome);      // Exibe o nome do cliente
    printf("\t\t| Telefone: %-80s|    \n", chamado->telefone);  // Exibe o telefone do cliente
    printf("\t\t| Email: %-80s   |       \n", chamado->email);    // Exibe o email do cliente
    printf("\t\t| Texto: %-80s   |       \n", chamado->texto);    // Exibe a descrição do chamado
    printf("\t\t| Status:%-80s   |       \n", chamado->status);  // Exibe o status do chamado
    printf("\t\t|___________________________________________________________________________________________|\n");
    if (chamado->resolucao[0] != '\0') {      // Exibe a resolução se estiver presente
        setColor(2,0);
        printf("\t\t ___________________________________________________________________________________________\n");
        printf("\n\n\t\t|Resolução: %-80s |\n", chamado->resolucao);
        printf("\t\t|___________________________________________________________________________________________|\n");
        setColor(7,0);
    } else {
        setColor(4,0);
        printf("\t\t ___________________________________________________________________________________________\n");
        printf("\t\t|Resolução: Nenhuma                                                                         |\n");
        printf("\t\t|___________________________________________________________________________________________|\n");
        setColor(7,0);
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
            setColor(4,0);
        printf("\n\n\t\t ___________________________________________________________________________________________\n");
            printf("\t\t|                          Chamado com ID %d não encontrado.                                |\n", id);
            printf("\t\t|___________________________________________________________________________________________|\n");
            setColor(7,0);
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
    setColor(4,0);
        printf("\n\n\t\t ___________________________________________________________________________________________\n");
            printf("\t\t|                          Chamado com ID %d não encontrado.                                |\n", id);
            printf("\t\t|___________________________________________________________________________________________|\n");
            setColor(7,0);
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
        limpa();
        menu_tecnico();
    }else{
        printf("Senha incorreta\n");

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

// Exibe o menu principal
void imprime_menu(){

        printf("\t\t\t\t\tEscolha a opcao desejada:\n");
        printf("\t\t\t\t\t1-ABRIR TICKET\n");
        printf("\t\t\t\t\t2-CONSULTAR TICKET POR ID\n");
        printf("\t\t\t\t\t3-AREA TECNICA\n");
        printf("\t\t\t\t\t4-SAIR\n\t\t\t\t\t");
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
        char sair[3];

        imprime_cabec();
        bemvindo();

    while (1) {
        imprime_menu();
        scanf("%d", &ticket);
        getchar(); // Consumir o caractere de nova linha deixado pelo scanf
        limpa();

        switch (ticket) {
            case 1:
                // Loop para registrar chamados enquanto a resposta for "sim"
                do {
                    limpa();

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
                    limpa();
                    carregando();
                    exibirChamado(chamados[numChamados]);

                    numChamados++; // Incrementa o número de chamados registrados
                    id++;          // Incrementa o ID do próximo chamado

                    printf("\n\n\t\t\t\tDeseja abrir outro ticket? (sim/nao)\n\n\t\t\t\t");
                    scanf("%s", sair);
                } while (strcmp(sair, "sim") == 0);

                limpa();
                break;

            case 2:
                // Consulta chamado por ID
                printf("\t\tDigite o ID do chamado a ser consultado:\n\t ");
                scanf("%d", &consultaID);
                getchar(); // Consumir nova linha
                consultarChamadoPorID(chamados, numChamados, consultaID); // Chama a função para consultar
                break;

            case 3:
                // Área técnica (implementar conforme necessário)
                login_tecnico();
                break;

            case 4:
                // Sair do programa
                printf("Saindo...\n");
                exit(0);
                break;

            default:
                printf("Opção inválida.\n");
                break;
        }
    }

    return 0;
}