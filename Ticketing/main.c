#include <stdio.h>
#include <time.h>       // Biblioteca para manipulação de tempo
#include <windows.h>    //Biblioteca para mudar cor do texto
#include "main.h"       // Inclui as declarações de funções


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
    printf("\n\t\t\t\t Feito por: Carlos - Gabriela - Lucas - Leticia \n\n");
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
        printf("Erro ao obter o número de clientes.\n");
        return;
    }

    printf("Gráfico:\n");
    printf("Total de clientes: ");
    for (int i = 0; i < cont; i++) {
        printf("\\");
    }
    printf("\nTotal de clientes: %d\n", cont);
}



int main() {
    sqlite3 *db;

    // Abre o banco de dados
    if (abrirBanco(&db) != SQLITE_OK) {
        return 1;
    }

    // Cria as tabelas, se não existirem
    if (criarTabela(db) != SQLITE_OK) {
        sqlite3_close(db);
        return 1;
    }

    char nome[100], tel[20], cpf[20];

    grafico_clientes();

    // Conta o número de clientes
    countClientes();

    // Captura os dados do usuário
    printf("Digite o nome: ");
    scanf("%99s", nome);
    printf("Digite o telefone: ");
    scanf("%19s", tel);
    printf("Digite o CPF: ");
    scanf("%19s", cpf);

    // Tenta cadastrar o cliente
    if (cadastrarCliente(db, nome, tel, cpf) != SQLITE_OK) {
        sqlite3_close(db);
        return 1;
    }



    // Fecha o banco de dados
    sqlite3_close(db);
    return 0;
}

