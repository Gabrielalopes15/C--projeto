
#ifndef MAIN_H
#define MAIN_H

#include <sqlite3.h>

// Definição da estrutura Chamado
typedef struct {
    int id;
    char descricao[256];
    char status[50];

    // Adicione outros campos conforme necessário
} Chamado;

// Declarações de funções
void setColor(int textColor, int bgColor);
void imprime_cabec(void);
void limpa(void);
void bemvindo(void);
void saindo(void);
void carregando(void);
void grafico_clientes(void);
void imprime_menu(void);
void registrarChamado(Chamado *chamado, int id);
void exibirChamado(Chamado *chamado);
void escolher_imprimir(void);
void consultarChamadoPorID(Chamado **chamados, int numChamados, int consultaID);
void login_tecnico(Chamado **chamados, int numChamados, int consultaID);
void graficoChamados(sqlite3 *db);

#endif // MAIN_H
