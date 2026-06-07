#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

// Prototipação das funções
int abrirBanco(sqlite3 **db);
int criarTabela(sqlite3 *db);
int cadastrarCliente(sqlite3 *db, const char *nome, const char *tel, const char *cpf);
int cpfExiste(sqlite3 *db, const char *cpf);
int countClientes();
int consultarCliente(sqlite3 *db, const char *cpf);
int alterarCliente(sqlite3 *db, const char *cpf, const char *novoNome, const char *novoTel);
int countClientes();
int inserirRelato(sqlite3 *db, int id_cliente, const char *relato);
int alterarChamado(sqlite3 *db, int id_ticket, const char *resolucao, const char *status, int valor);
int consultarTickets(sqlite3 *db);
int consultarStatusChamados(sqlite3 *db, int *abertos, int *fechados, int *pendentes);

#endif // DATABASE_H


