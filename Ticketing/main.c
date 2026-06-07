#include <stdio.h>
#include <time.h>       // Biblioteca para manipulação de tempo
#include <windows.h>    //Biblioteca para mudar cor do texto
#include "main.h"       // Inclui as declarações de funções
#include "database.h"
#include <locale.h>     //Biblioteca para reconhecer pontuação em portugues.


// Definições
// Função para centralizar o texto
void centralizeText(const char *text) {
    int consoleWidth = getConsoleWidth();
    int padding = (consoleWidth - strlen(text)) / 2;
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s\n", text);
}

// Definições centralizadas
#define LINHA "=========================================================================             "
#define TRACO "|----------------------------------------------------------------------                   |"



// Função para definir a cor do texto
void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}


// Função para obter a largura da tela do console
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    return columns;
}


// Função para abrir o console em tela cheia
void abrirTelaCheia() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
}


// Função para imprimir o cabeçalho centralizado
void imprime_cabec(void) {

    // Exibe o horário atual
    time_t tempo;
    time(&tempo);
    struct tm *tempo0 = localtime(&tempo);

    int consoleWidth = getConsoleWidth();
    int padding = (consoleWidth - 70) / 2; // 70 é a largura do texto

    setColor(15, 13); // 1 = azul, 15 = fundo branco
    printf("\n\n");
    for (int i = 0; i < padding; i++) printf(" ");
    printf("----------------------------------------------------------------------                                                \n");
    for (int i = 0; i < padding; i++) printf(" ");
    printf("|  **********              Sistema de Ticketing          **********  |                                                \n");
    for (int i = 0; i < padding; i++) printf(" ");
    printf("|                          %02d:%02d                                     |                                                \n", tempo0->tm_hour, tempo0->tm_min);
    for (int i = 0; i < padding; i++) printf(" ");
    printf("----------------------------------------------------------------------                                                \n");
    setColor(7, 0); // Volta as cores ao padrão windows.
    return;
}


// Função para imprimir o menu centralizado
void imprime_menu() {
    int consoleWidth = getConsoleWidth();
    const char *menu_items[] = {
        "------- Menu Principal -------",
        "1. Cadastrar Cliente",
        "2. Cadastrar Ticket por CPF",
        "3. Alterar Ticket",
        "4. Consultar ticket",
        "5. Dashboard",
        "6. Sair"
    };
    int num_items = sizeof(menu_items) / sizeof(menu_items[0]);

    for (int i = 0; i < num_items; i++) {
        int padding = (consoleWidth - strlen(menu_items[i])) / 2;
        for (int j = 0; j < padding; j++) printf(" ");
        printf("%s\n", menu_items[i]);
    }

    int padding = (consoleWidth - strlen("Escolha uma opção: ")) / 2;
    for (int j = 0; j < padding; j++) printf(" ");
    printf("Escolha uma opção: ");
}

//Limpa a tela.
void limpa(void)
{
    system("cls");
    imprime_cabec();
    return;
}

//Limpa a tela.
void limpaTudo(void)
{
    system("cls");

    return;
}


// Função para imprimir a mensagem de boas-vindas centralizada
void bemvindo() {
    int consoleWidth = getConsoleWidth();
    const char *welcome_message[] = {
        "BBBB   EEEEE M   M      V   V  I  N   N DDDD   OOO  ",
        "B   B  E     MM MM      V   V  I  NN  N D   D O   O ",
        "BBBB   EEEE  M M M      V   V  I  N N N D   D O   O ",
        "B   B  E     M   M       V V   I  N  NN D   D O   O ",
        "BBBB   EEEEE M   M        V    I  N   N DDDD   OOO  ",
        "------- Bem vindo ao Ticketing  -------",
        "Feito por: Carlos - Gabriela - Lucas - Leticia"
    };
    int num_lines = sizeof(welcome_message) / sizeof(welcome_message[0]);

    setColor(9, 0); // azul claro
    for (int i = 0; i < 5; i++) {
        int padding = (consoleWidth - strlen(welcome_message[i])) / 2;
        for (int j = 0; j < padding; j++) printf(" ");
        printf("%s\n", welcome_message[i]);
    }
    setColor(7, 0); // Volta as cores ao padrão windows.

    setColor(13, 0); // rosa claro
    for (int i = 5; i < num_lines; i++) {
        int padding = (consoleWidth - strlen(welcome_message[i])) / 2;
        for (int j = 0; j < padding; j++) printf(" ");
        printf("%s\n", welcome_message[i]);
    }
    setColor(7, 0); // Volta as cores ao padrão windows.
}


//Função para exibir tela de Saindo.
void saindo (){
    int i;
    for(i = 0; i < 2; i++){
        //setColor(9,15);
        printf("\n\n\t\t\t\t\t\t _______________\n");
        printf("\t\t\t\t\t\t| Saindo.       |\n");
        printf("\t\t\t\t\t\t|_______________|\n");
        sleep(1);
        limpa();
        printf("\n\n\t\t\t\t\t\t _______________\n");
        printf("\t\t\t\t\t\t| Saindo..      |\n");
        printf("\t\t\t\t\t\t|_______________|\n");
        sleep(1);
        limpa();
        printf("\n\n\t\t\t\t\t\t _______________\n");
        printf("\t\t\t\t\t\t| Saindo...     |\n");
        printf("\t\t\t\t\t\t|_______________|\n");
        sleep(1);
        limpa();
        setColor(7,0);
    }
exit(0);

}


// Função para exibir tela de carregando
void carregando(void) {
    int i;
    for (i = 0; i < 1; i++) {
        limpa();
        // setColor(9, 13);
        printf("\n\n\n\n\n\n\n\n\n\n");
        centralizeText(" _______________ ");
        centralizeText("|  Carregando.  |");
        centralizeText("|_______________|");
        sleep(1);
        limpa();
        printf("\n\n\n\n\n\n\n\n\n\n");
        centralizeText(" _______________ ");
        centralizeText("|  Carregando.. |");
        centralizeText("|_______________|");
        sleep(1);
        limpa();
        printf("\n\n\n\n\n\n\n\n\n\n");
        centralizeText(" _______________ ");
        centralizeText("|  Carregando...|");
        centralizeText("|_______________|");
        sleep(1);
        limpa();
        setColor(7, 0);
    }
    return;
}



//Função para criar grafico
void grafico_clientes() {
    int cont = countClientes();
    if (cont < 0) {
        setColor(4,4);  // 4 = vermelho
        printf("Erro ao obter o número de clientes.\n");
        setColor(7, 0); // Volta as cores ao padrão windows.
        return;
    }
    imprime_cabec();
    printf("\n\t\t\tGráfico de clientes:\n");
    printf("\n\n\t\t\tClientes Cadastrados: %d - ", cont);
    for (int i = 0; i < cont; i++) {
        setColor(15, 1); // 1 = azul, 15 = fundo branco
        printf(" ");
        setColor(7, 0); // Volta as cores ao padrão windows.
    }
}


void graficoChamados(sqlite3 *db) {
    int abertos = 0, fechados = 0, pendentes = 0;

    if (consultarStatusChamados(db, &abertos, &fechados, &pendentes) != SQLITE_OK) {
        setColor(4,0);  // 4 = vermelho
        printf("Erro ao obter os status dos chamados.\n");
        setColor(7, 0); // Volta as cores ao padrão windows.
        return;
    }

    printf("\n\n\n\n\t\t\tGráfico Tickets:\n");
    printf("\n\n\t\t\tAbertos: %d - ", abertos);
    for (int i = 0; i < abertos; i++) {
        setColor(11, 11); // 11 = azul claro
        printf(" ");
        setColor(7, 0); // Volta as cores ao padrão windows.
    }
    printf("\n\n\t\t\tFechados:  %d - ", fechados);
    for (int i = 0; i < fechados; i++) {
        setColor(2, 2); // 1 = verde
        printf(" ");
        setColor(7, 0); // Volta as cores ao padrão windows.
    }

    printf("\n\n\t\t\tPendentes: %d - ", pendentes);
    for (int i = 0; i < pendentes; i++) {
        setColor(4,4);  // 4 = vermelho
        printf(" ");
        setColor(7, 0); // Volta as cores ao padrão windows.
    }

}




int main() {
    abrirTelaCheia();
    setlocale(LC_ALL, "Portuguese");
    sqlite3 *db;
    int ticket;
    char cpf[20], nome[100], tel[20];
    int id_cliente, id_ticket, valor;
    char relato[256], resolucao[256], status[50];

    if (abrirBanco(&db) != SQLITE_OK) {
        return 1;
    }

    if (criarTabela(db) != SQLITE_OK) {
        sqlite3_close(db);
        return 1;
    }

    bemvindo();
    sleep(2);

    while (1) {
        limpaTudo();
        printf("\n\n");
        imprime_cabec();
        imprime_menu();
        printf("\n\t\t\t\t\t");
        scanf("%d", &ticket);
        getchar(); // Consumir o caractere de nova linha deixado pelo scanf
        limpa();

        switch (ticket) {
            case 1:
                // Cadastrar Cliente
                printf("\n\t\t\tDigite o nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                printf("\n\t\t\tDigite o telefone: ");
                fgets(tel, sizeof(tel), stdin);
                tel[strcspn(tel, "\n")] = 0;

                printf("\n\t\t\tDigite o CPF: ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = 0;
                carregando();
                if (cadastrarCliente(db, nome, tel, cpf) != SQLITE_OK) {
                    setColor(2, 0);
                    printf("\n\t\t\tCliente cadastrado com sucesso.\n");
                    sleep(3);
                    setColor(7, 0);
                } else {
                    setColor(4, 0);
                    printf("\n\t\t\tErro ao cadastrar cliente.\n");
                    setColor(7, 0);
                }
                limpaTudo();
                break;

            case 2:
                // Consultar Cliente pelo CPF antes de Inserir Relato
                printf("\n\t\t\t\t\tDigite o CPF do cliente: ");
                scanf("%19s", cpf);

                if (consultarClientePorCPF(db, cpf, &id_cliente) == SQLITE_OK) {
                    printf("\n\t\t\t\t\tDigite o relato: ");
                    getchar();
                    fgets(relato, sizeof(relato), stdin);
                    relato[strcspn(relato, "\n")] = 0;

                    if (inserirRelato(db, id_cliente, relato) != SQLITE_OK) {
                        setColor(2, 0);
                        printf("\n\t\t\t\t\tRelato inserido com sucesso.\n");
                        setColor(7, 0);
                    } else {
                        setColor(4, 0);
                        printf("\n\t\t\t\t\tErro ao inserir relato.\n");
                        setColor(7, 0);
                    }
                }

                break;

            case 3:
                // Alterar Chamado
                printf("\n\t\t\t\t\tDigite o ID do ticket: ");
                scanf("%d", &id_ticket);
                getchar();
                printf("\n\t\t\t\t\tDigite a resolução: ");
                fgets(resolucao, sizeof(resolucao), stdin);
                resolucao[strcspn(resolucao, "\n")] = 0;
                printf("\n\t\t\t\t\tDigite o status: ");
                scanf("%49s", status);
                printf("\n\t\t\t\t\tDigite o valor: ");
                scanf("%d", &valor);

                if (alterarChamado(db, id_ticket, resolucao, status, valor) != SQLITE_OK) {
                    printf("\n\t\t\t\t\tErro ao alterar chamado.\n");
                } else {
                    printf("\n\t\t\t\t\tChamado alterado com sucesso.\n");
                }

                break;

            case 4:
                // Consultar Tickets
                do {
                    if (consultarTickets(db) != SQLITE_OK) {
                        printf("\n\t\t\t\t\tErro ao consultar tickets.\n");
                    }
                    printf("\n\t\t\t\t\tDigite 0 para voltar ao menu: ");
                    scanf("%d", &ticket);
                } while (ticket != 0);
                limpaTudo();
                break;

            case 5:
                // Consultar Status dos Chamados e Gerar Gráfico
                do {
                    grafico_clientes();
                    graficoChamados(db);

                    printf("\n\n\t\t\tDigite 0 para voltar ao menu: ");
                    scanf("%d", &ticket);
                } while (ticket != 0);

                break;

            case 6:
                saindo();
                sqlite3_close(db);
                return 0;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}
