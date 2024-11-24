#include <stdio.h>
#include <time.h>       // Biblioteca para manipulação de tempo
#include <windows.h>    //Biblioteca para mudar cor do texto
#include "main.h"       // Inclui as declarações de funções
#include "database.h"
#include <locale.h>     //Biblioteca para reconhecer pontuação em portugues.


// Definições
#define LINHA "\t\t\t=========================================================================\n"
#define TRACO "\t\t\t|----------------------------------------------------------------------|\n"


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
    printf(LINHA);
    printf("\t\t\t|  **********              Sistema de Ticketing             **********  |\n");
    printf("\t\t\t|                          %02d:%02d                                        |\n", tempo0->tm_hour, tempo0->tm_min);
    printf(LINHA);
    setColor(7, 0); // Volta as cores ao padrão windows.
    return;
}


// Função para imprimir o menu
void imprime_menu() {
    printf("\n\t\t\t\t\t------- Menu Principal -------\n");
    printf("\t\t\t\t\t1. Cadastrar Cliente\n");
    printf("\t\t\t\t\t2. Cadastrar Ticket por CPF\n");
    printf("\t\t\t\t\t3. Alterar Ticket\n");
    printf("\t\t\t\t\t4. Consultar ticket\n");
    printf("\t\t\t\t\t5. Dashboard\n");
    printf("\t\t\t\t\t6. Sair\n");
    printf("\t\t\t\t\t7. Sair\n");
    printf("\t\t\t\t\tEscolha uma opção: ");
}

//Limpa a tela.
void limpa(void)
{
    system("cls");
    imprime_cabec();
    return;
}


//Imprime uma imagem de bem vindo
void bemvindo()
{
    // Exibe uma mensagem de boas-vindas em arte de texto
    setColor(9, 0); // azul claro
    printf("\n\t\t\t\tBBBB   EEEEE M   M      V   V  I  N   N DDDD   OOO  \n");
    printf("\t\t\t\tB   B  E     MM MM      V   V  I  NN  N D   D O   O \n");
    printf("\t\t\t\tBBBB   EEEE  M M M      V   V  I  N N N D   D O   O \n");
    printf("\t\t\t\tB   B  E     M   M       V V   I  N  NN D   D O   O \n");
    printf("\t\t\t\tBBBB   EEEEE M   M        V    I  N   N DDDD   OOO  \n\n");
    printf("\n\t\t\t\t\t------- Bem vindo ao Ticketing  -------\n\n");
    setColor(7, 0); // Volta as cores ao padrão windows.
    setColor(13,0);  // 2 = azul claro
    printf("\n\t\t\t\t Feito por: Carlos - Gabriela - Lucas - Leticia \n\n");
    setColor(7, 0); // Volta as cores ao padrão windows.
    return;
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


//Função para exibir tela de carregando.
void carregando (void){
    int i;
    for(i = 0; i < 1; i++){
        limpa();
        //setColor(9,15);
        printf("\n\n\t\t\t\t\t\t _______________\n");
        printf("\t\t\t\t\t\t| Carregando.   |\n");
        printf("\t\t\t\t\t\t|_______________|\n");
        sleep(1);
        limpa();
        printf("\n\n\t\t\t\t\t\t _______________\n");
        printf("\t\t\t\t\t\t| Carregando..  |\n");
        printf("\t\t\t\t\t\t|_______________|\n");
        sleep(1);
        limpa();
        printf("\n\n\t\t\t\t\t\t _______________\n");
        printf("\t\t\t\t\t\t| Carregando... |\n");
        printf("\t\t\t\t\t\t|_______________|\n");
        sleep(1);
        limpa();
        setColor(7,0);
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
        setColor(4,4);  // 4 = vermelho
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
    setlocale(LC_ALL, "Portuguese");

    sqlite3 *db;

    // Variáveis
    int ticket;
    char cpf[20], nome[100], tel[20];
    int id_cliente, id_ticket, valor;
    char relato[256], resolucao[256], status[50];

    // Abre o banco de dados
    if (abrirBanco(&db) != SQLITE_OK) {
        return 1;
    }

    // Cria as tabelas, se não existirem
    if (criarTabela(db) != SQLITE_OK) {
        sqlite3_close(db);
        return 1;
    }

    bemvindo();
    sleep(2);

    while (1) {
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

                // Cadastrar Cliente
                printf("\n\t\t\tDigite o nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0; // Remover o caractere de nova linha

                printf("\n\t\t\tDigite o telefone: ");
                fgets(tel, sizeof(tel), stdin);
                tel[strcspn(tel, "\n")] = 0; // Remover o caractere de nova linha

                printf("\n\t\t\tDigite o CPF: ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = 0; // Remover o caractere de nova linha

                if (cadastrarCliente(db, nome, tel, cpf) != SQLITE_OK) {
                  setColor(2, 0);
                   printf("\n\t\t\tCliente cadastrado com sucesso.\n");
                   setColor(7, 0); // Volta as cores ao padrão windows.
                } else {
                     setColor(4, 0);  // 4 = vermelho
                    printf("\n\t\t\tErro ao cadastrar cliente.\n");
                    setColor(7, 0); // Volta as cores ao padrão windows.
                }
                break;
                limpa();
            case 2:
                 // Consultar Cliente pelo CPF antes de Inserir Relato

                printf("\n\t\t\t\t\tDigite o CPF do cliente: ");
                scanf("%19s", cpf);

                if (consultarClientePorCPF(db, cpf, &id_cliente) == SQLITE_OK) {
                    printf("\n\t\t\t\t\tDigite o relato: ");
                    getchar(); // Consumir o caractere de nova linha deixado pelo scanf
                    fgets(relato, sizeof(relato), stdin);
                    relato[strcspn(relato, "\n")] = 0; // Remover o caractere de nova linha

                    if (inserirRelato(db, id_cliente, relato) != SQLITE_OK) {
                        printf("\n\t\t\t\t\tErro ao inserir relato.\n");
                    } else {
                        printf("\n\t\t\t\t\tRelato inserido com sucesso.\n");
                    }
                }
                break;
            case 3:
                // Alterar Chamado

                printf("\n\t\t\t\t\tDigite o ID do ticket: ");
                scanf("%d", &id_ticket);
                getchar(); // Consumir o caractere de nova linha deixado pelo scanf
                printf("\n\t\t\t\t\tDigite a resolução: ");
                fgets(resolucao, sizeof(resolucao), stdin);
                resolucao[strcspn(resolucao, "\n")] = 0; // Remover o caractere de nova linha
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
                break;

            case 5:

                // Consultar Status dos Chamados e Gerar Gráfico
            do {
                grafico_clientes();
                graficoChamados(db);
            printf("\n\n\t\t\tDigite 0 para voltar ao menu: ");
            scanf("%d", &ticket);
            } while (ticket != 0);
                limpa();
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
