
#ifndef MAIN_H
#define MAIN_H

#include <sqlite3.h>

// Prototipação das funções
int abrirBanco(sqlite3 **db);
int criarTabela(sqlite3 *db);
int cpfExiste(sqlite3 *db, const char *cpf);
int cadastrarCliente(sqlite3 *db, const char *nome, const char *tel, const char *cpf);
int countClientes();

#endif // MAIN_H

