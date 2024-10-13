#include <stdio.h>      // Biblioteca padrão para entrada e saída
#include <stdlib.h>     // Biblioteca para funções de alocação de memória e controle do sistema
#include <string.h>     // Biblioteca para manipulação de strings
#include <time.h>       // Biblioteca para manipulação de tempo
#include <locale.h>     //Biblioteca para reconhecer pontuação em portugues.
#include <unistd.h>
#include <conio.h>      // Para usar getch()
#include <windows.h>    //Biblioteca para mudar cor do texto

#include "main.h"


// Definições
#define LINHA "\t\t\t=========================================================================\n"
#define TRACO "\t\t\t|----------------------------------------------------------------------|\n"

//variaveis
int senha; //Armazena a senha digitada pelo tecnico.
int opcao_tecnica; //Armazena a opção solicitada no menu do tecnico.
int ticket; //Armazena ticket do menu principal.


//Funções

//Função para escolher imprimir ou não
void escolher_imprimir() {
    char resposta;
    printf("\n\n\t\t\tDeseja imprimir o arquivo? (s/n):\n\n\t\t\t ");
    scanf(" %c", &resposta);

    if (resposta == 's' || resposta == 'S') {
        imprimir_arquivo("chamado.txt");
    } else {
        printf("Impressão cancelada.\n");
    }
}


// Função para imprimir um arquivo
void imprimir_arquivo(const char *filename){

    // Verifique se o arquivo existe antes de tentar imprimir
    if (access(filename, F_OK) != 0) {
        printf("Arquivo %s não encontrado.\n", filename);
        return;
    }


    //Imprimir utilizando PDF
    char comando[256];
    sprintf(comando,"print /d:\"Microsoft Print to PDF\" \%s\"",filename);

    system("start chamado.txt");
}

// Função para salvar os detalhes do chamado em um arquivo
void salvar_chamado(const Chamado* chamado){
    FILE *arquivo = fopen("chamado.txt","w");
    if (arquivo == NULL){
        printf("Erro ao criar o arquivo de impressão\n");
        return;
    }

    fprintf(arquivo,"==========================\n");
    fprintf(arquivo,"ID: %d\n",chamado->id);
    fprintf(arquivo,"Cliente: %s\n",chamado->nome);
    fprintf(arquivo,"Telefone: %s\n",chamado->telefone);
    fprintf(arquivo,"Email: %s\n",chamado->email);
    fprintf(arquivo,"Texto: %s\n",chamado->texto);
    fprintf(arquivo,"Status: %s\n",chamado->status);
    fprintf(arquivo,"==========================\n");

    if(chamado->resolucao[0] != '\0'){
        fprintf(arquivo,"Resolução: %s\n",chamado->resolucao);
    }

    if(chamado->valor[0] != '\0'){
        fprintf(arquivo,"Valor: %s\n",chamado->valor);
    }

    fclose(arquivo);

}


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
        printf("\n\n\t\t\t _______________\n");
        printf("\t\t\t| Saindo.       |\n");
        printf("\t\t\t|_______________|\n");
        sleep(1);
        limpa();
        printf("\n\n\t\t\t _______________\n");
        printf("\t\t\t| Saindo..      |\n");
        printf("\t\t\t|_______________|\n");
        sleep(1);
        limpa();
        printf("\n\n\t\t\t _______________\n");
        printf("\t\t\t| Saindo...     |\n");
        printf("\t\t\t|_______________|\n");
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


// Função para validar o telefone
int validarTelefone(const char *telefone) {
    int length = strlen(telefone);

// Verifica se o comprimento está entre 10 e 11
int validarTelefone(const char *telefone); {
    int length = strlen(telefone);

    // Verifica se o comprimento está entre 10 e 11
    if (length < 10 || length > 11) {
        return 0; // Telefone inválido
    }

    // Verifica se todos os caracteres são dígitos
    for (int i = 0; i < length; i++) {
        if (!isdigit(telefone[i])) {
            return 0; // Telefone inválido
        }
    }
}
    return 1; // Telefone válido
}

// Função para registrar um novo chamado
void registrarChamado(Chamado* chamado, int id) {
    printf("\n\t\t\tRegistrando chamado com ID: %d\n", id);
    chamado->id = id;   // Atribui o ID ao chamado

    // Atribui o Status ao chamado como "ABERTO"
    strncpy(chamado->status, "ABERTO", MAX_TAM);
    chamado->resolucao[0] = '\0'; // Inicializa a resolução como uma string vazia
    chamado->valor[0] = '\0'; // Inicializa o valor como uma string vazia

    printf("\n\t\t\tDigite o nome do cliente:\n\n\t\t\t");
    fgets(chamado->nome, MAX_TAM, stdin);   // Lê o nome do cliente
    chamado->nome[strcspn(chamado->nome, "\n")] = '\0'; // Remove a nova linha gerada pelo fgets
    limpa();

    int telefoneValido = 0;
    while (!telefoneValido) {
        printf("\n\t\t\tDigite o telefone do cliente: exemplo: ddd 9nnnnnnn\n\t\t\t ");
        fgets(chamado->telefone, MAX_TAM, stdin);
        chamado->telefone[strcspn(chamado->telefone, "\n\t\t\t")] = '\0';
        limpa();

        if (validarTelefone(chamado->telefone)) {
            telefoneValido = 1;
        } else {
            printf("\n\t\t\tTelefone inválido. Por favor, insira um número de telefone válido.\n");
        }
    }

    printf("\n\t\t\tDigite o email do cliente:\n\n\t\t\t");
    fgets(chamado->email, MAX_TAM, stdin);  // Lê o email do cliente
    chamado->email[strcspn(chamado->email, "\n")] = '\0'; // Remove a nova linha
    limpa();

    printf("\n\t\t\tDigite o texto do chamado:\n\n\t\t\t");
    fgets(chamado->texto, MAX_TAM, stdin);  // Lê a descrição do chamado
    chamado->texto[strcspn(chamado->texto, "\n")] = '\0'; // Remove a nova linha
    limpa();
    salvar_chamado(chamado); //Salva os detalhes do chamado
    carregando();

}

// Função para exibir as informações de um chamado
void exibirChamado(const Chamado* chamado) {

    printf("\a\n\t\t\tChamado Registrado:\n\n");
    printf("\t\t _____________________________________________________________________________________________\n");
    printf("\t\t| ID: %-80d       |\n", chamado->id);          // Exibe o ID do chamado
    printf("\t\t| Nome: %-80s     |\n", chamado->nome);      // Exibe o nome do cliente
    printf("\t\t| Telefone: %-80s |\n", chamado->telefone);  // Exibe o telefone do cliente
    printf("\t\t| Email: %-80s    |\n", chamado->email);    // Exibe o email do cliente
    printf("\t\t| Texto: %-80s    |\n", chamado->texto);    // Exibe a descrição do chamado
    printf("\t\t| Status:%-80s    |\n", chamado->status);  // Exibe o status do chamado
    printf("\t\t|____________________________________________________________________________________________|\n");
    if (chamado->resolucao[0] != '\0') {      // Exibe a resolução se estiver presente
        setColor(2,0);
        printf("\t\t|____________________________________________________________________________________________|\n");
        printf("\t\t|Resolução: %-80s |\n", chamado->resolucao);
        printf("\t\t|____________________________________________________________________________________________|\n");
        setColor(7,0);
    } else {
        setColor(4,0);
        printf("\t\t|____________________________________________________________________________________________|\n");
        printf("\t\t|Resolução: Nenhuma                                                                          |\n");
        printf("\t\t|____________________________________________________________________________________________|\n");
        setColor(7,0);
    }
    if (chamado->valor[0] != '\0') {      // Exibe a resolução se estiver presente
        setColor(2,0);
        printf("\t\t|____________________________________________________________________________________________|\n");
        printf("\t\t|Valor: %-80s     |\n", chamado->valor);
        printf("\t\t|____________________________________________________________________________________________|\n");
        setColor(7,0);
    } else {
        setColor(4,0);
        printf("\t\t|____________________________________________________________________________________________|\n");
        printf("\t\t|Valor: Sem valor no momento                                                                 |\n");
        printf("\t\t|____________________________________________________________________________________________|\n");
        setColor(7,0);
    }
}


// Função para consultar um chamado pelo ID
void consultarChamadoPorID(Chamado** chamados, int numChamados, int id) {
    // Percorre a lista de chamados
    for (int i = 0; i < numChamados; i++) {
        if (chamados[i]->id == id) {    // Verifica se o ID corresponde
            carregando();
            exibirChamado(chamados[i]); // Se encontrado, exibe o chamado
            return;
        }
    }
    // Se o ID não for encontrado, informa que o chamado não foi achado
            carregando();
            setColor(4,0);
        printf("\n\n\t\t ________________________________________________________________________________________\n");
            printf("\t\t|                          Chamado com ID %d não encontrado.                              |\n", id);
            printf("\t\t|________________________________________________________________________________________|\n");
            setColor(7,0);
}


// Função para atualizar o status e a resolução de um chamado
void atualizarChamado(Chamado** chamados, int numChamados, int id) {
    // Percorre a lista de chamados
    for (int i = 0; i < numChamados; i++) {
        if (chamados[i]->id == id) {    // Verifica se o ID corresponde
            carregando();
            printf("Chamado encontrado.\n");

            // Lê o novo status
            printf("Digite o novo status (ex: 'FECHADO', 'PENDENTE'): ");
            fgets(chamados[i]->status, MAX_TAM, stdin);
            chamados[i]->status[strcspn(chamados[i]->status, "\n")] = '\0'; // Remove a nova linha

            // Lê a resolução do chamado
            printf("Digite a resolução do chamado: ");
            fgets(chamados[i]->resolucao, MAX_TAM, stdin);
            chamados[i]->resolucao[strcspn(chamados[i]->resolucao, "\n")] = '\0'; // Remove a nova linha

            // Lê o valor do serviço
            printf("Digite o valor do serviço: ");
            fgets(chamados[i]->valor, MAX_TAM, stdin);
            chamados[i]->valor[strcspn(chamados[i]->valor, "\n")] = '\0'; // Remove a nova linha
            limpa();
            carregando();
            printf("Chamado atualizado com sucesso.\n");
            return;
        }
    }
    // Se o ID não for encontrado, informa que o chamado não foi achado
            setColor(4,0);
        printf("\n\n\t\t ________________________________________________________________________________________\n");
            printf("\t\t|                          Chamado com ID %d não encontrado.                              |\n", id);
            printf("\t\t|________________________________________________________________________________________|\n");
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
        limpa();
        printf("\t\t\tNenhum chamado com status '%s' encontrado.\n", statusDesejado);
    }
}


//Imprime o menu do tecnico
void menu_tecnico (Chamado** chamados, int numChamados){

    int opcao_tecnica;

    do{
  // Menu da área técnica
        printf("\n\n\t\t\t\t----- Área Técnica -----\n\n");
        printf("\t\t\t\tEscolha a opção desejada:\n");
        printf("\t\t\t\t1. Consultar chamados ABERTOS\n");
        printf("\t\t\t\t2. Consultar chamados FECHADOS\n");
        printf("\t\t\t\t3. Atualizar chamado\n");
        printf("\t\t\t\t4. Voltar ao menu principal\n\n\t\t\t\t");
        scanf("%d", &opcao_tecnica);
        getchar();

        switch (opcao_tecnica) {
            case 1:
                // Consultar chamados ABERTOS
                if (numChamados > 0) {
                    listarChamadosPorStatus(chamados, numChamados, "ABERTO");
                } else {
                    limpa();
                    printf("\n\t\t\t\tNão há chamados em aberto.\n");
                }
                break;

            case 2:
                // Consultar chamados FECHADOS
                if (numChamados > 0) {
                    listarChamadosPorStatus(chamados, numChamados, "FECHADO");
                } else {
                    limpa();
                    printf("\n\t\t\t\tNão há chamados fechados.\n");
                }
                break;

            case 3: {
                // Atualizar um chamado
                limpa();
                int idChamado;
                printf("\n\n\t\t\t\tDigite o ID do chamado que deseja atualizar: ");
                scanf("%d", &idChamado);
                getchar(); // Consumir o caractere de nova linha após o scanf
                atualizarChamado(chamados, numChamados, idChamado);
                break;
            }
            case 4: {
                // Voltar ao menu principal
                limpa();
                return;
            }
            default:
                printf("\n\n\t\t\t\tOpção inválida, tente novamente.\n");
                break;
        }
    }
    while (opcao_tecnica != 4);
}



//Valida se a senha do tecnico esta correta ou não.
void login_tecnico(Chamado** chamados, int numChamados, int consultaID){
 // Obter a data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int dia = tm.tm_mday;
    int mes = tm.tm_mon + 1; // tm_mon retorna meses de 0 a 11
    int ano = tm.tm_year % 100; // Obter os dois últimos dígitos do ano

    int senha_correta = dia * mes * ano;
    int senha_digitada = 0;
    char ch;

    printf("\n\n\t\t\t\tDigite a senha para a área técnica: \n\t\t\t\t");
    // Capturar cada caractere digitado até que Enter seja pressionado (limite de 6 dígitos)
    while (1) {
        ch = getch(); // Captura o caractere sem exibir no terminal

        if (ch == 13) {  // 13 é o código ASCII para Enter
            break;  // Sai do loop ao pressionar Enter
        } else if (ch >= '0' && ch <= '9') {  // Se for um número
            senha_digitada = senha_digitada * 10 + (ch - '0'); // Constrói a senha
            printf("*");  // Exibe um asterisco no lugar do número
        } else if (ch == 8 && senha_digitada > 0) {  // 8 é o código ASCII para Backspace
            // Apaga o último dígito
            senha_digitada /= 10;  // Remove o último dígito
            printf("\b \b");  // Volta o cursor, apaga o último caractere e volta o cursor novamente
        }
    }

    printf("\n");

    // Verifica se a senha está correta
    if (senha_digitada == senha_correta) {
        menu_tecnico(chamados, numChamados);  // Chama o menu técnico se a senha estiver correta
    } else {
        printf("\n\t\t\t\tSenha incorreta\n");
    }

    return;
}


// Exibe o menu principal
void imprime_menu() {
    printf("\t\t\t\tEscolha a opção desejada:\n");
    printf("\t\t\t\t1- ABRIR TICKET\n");
    printf("\t\t\t\t2- CONSULTAR TICKET POR ID\n");
    printf("\t\t\t\t3- ÁREA TÉCNICA\n");
    printf("\t\t\t\t4- SAIR\n");
    printf(LINHA);
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

        limpa();
        bemvindo();

    while (1) {
        printf("\n\n");
        imprime_menu();
        printf("\n\t\t\t\t");
        scanf("%d", &ticket);
        getchar(); // Consumir o caractere de nova linha deixado pelo scanf
        limpa();

        switch (ticket) {
            case 1:
                // Loop para registrar chamados enquanto a resposta for "sim"
                do {
                    limpa();

                    // Realoca memória para armazenar um novo chamado
                    chamados = (Chamado**)realloc(chamados, (numChamados + 1) * sizeof(Chamado));
                    if (chamados == NULL) {
                        printf("\t\t\t\tErro ao alocar memória.\n\t\t\t\t");
                        limpa();
                        exit(1);
                    }

                    // Aloca memória para o novo chamado
                    chamados[numChamados] = (Chamado*)malloc(sizeof(Chamado));
                    if (chamados[numChamados] == NULL) {
                        printf("\t\t\t\tErro ao alocar memória.\n\t\t\t\t");
                        limpa();
                        exit(1);
                    }

                    // Registra o chamado
                    registrarChamado(chamados[numChamados], id);
                    // Exibe o chamado registrado
                    limpa();
                    exibirChamado(chamados[numChamados]);

                    numChamados++; // Incrementa o número de chamados registrados
                    id++;          // Incrementa o ID do próximo chamado
                    escolher_imprimir();
                    limpa();
                    printf("\n\n\t\t\t\tDeseja abrir outro ticket? (sim/nao)\n\n\t\t\t\t");
                    scanf("%s", sair);
                } while (strcmp(sair, "sim") == 0);

                limpa();
                break;

            case 2:
                // Consulta chamado por ID
                printf("\t\t\tDigite o ID do chamado a ser consultado:\n\t\t\t");
                scanf("%d", &consultaID);
                getchar(); // Consumir nova linha
                consultarChamadoPorID(chamados, numChamados, consultaID); // Chama a função para consultar

                break;

            case 3:
                // Área técnica (implementar conforme necessário)
                login_tecnico(chamados, numChamados, consultaID);
                break;

            case 4:
                // Sair do programa
                saindo();
                exit(0);
                break;

            default:
                printf("Opção inválida.\n");
                break;
        }
    }

    return 0;
}
