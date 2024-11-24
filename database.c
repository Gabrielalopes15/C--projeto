#include <stdlib.h>
#include <stdio.h>
#include "main.h"

// Função para abrir o banco de dados
int abrirBanco(sqlite3 **db) {
    int rc = sqlite3_open("ticketing.db", db);
    if (rc) {
        fprintf(stderr, "Não foi possível abrir o banco de dados: %s\n", sqlite3_errmsg(*db));
        return rc;
    }
    return SQLITE_OK;
}


// Função para criar a tabela CLIENTE
int criarTabela(sqlite3 *db) {
    const char *sql =
        "CREATE TABLE IF NOT EXISTS CLIENTE ("
        "ID_CLIENTE INTEGER PRIMARY KEY AUTOINCREMENT, "
        "NOME TEXT NOT NULL, "
        "TEL TEXT NOT NULL, "
        "CPF TEXT NOT NULL);"

        "CREATE TABLE IF NOT EXISTS TICKET ("
        "ID_TICKET INTEGER PRIMARY KEY AUTOINCREMENT, "
        "ID_CLIENTE INTEGER, "
        "RELATO TEXT NOT NULL, "
        "RESOLUCAO TEXT NOT NULL, "
        "STATUS TEXT NOT NULL, "
        "VALOR INTEGER, "
        "FOREIGN KEY(ID_CLIENTE) REFERENCES CLIENTE(ID_CLIENTE));"

        "CREATE TABLE IF NOT EXISTS TECNICO ("
        "ID_TECNICO INTEGER PRIMARY KEY AUTOINCREMENT, "
        "ID_TICKET INTEGER, "
        "NOME TEXT NOT NULL, "
        "TEL TEXT NOT NULL, "
        "EMAIL TEXT NOT NULL, "
        "SENHA TEXT NOT NULL, "
        "FOREIGN KEY(ID_TICKET) REFERENCES TICKET(ID_TICKET));";

    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabela: %s\n", errMsg);
        sqlite3_free(errMsg);
        return rc;
    }
    return SQLITE_OK;
}


// Função para verificar se o CPF já existe
int cpfExiste(sqlite3 *db, const char *cpf) {
    const char *sql = "SELECT COUNT(*) FROM CLIENTE WHERE CPF = ?;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_text(stmt, 1, cpf, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count > 0;
    } else {
        fprintf(stderr, "Erro ao executar query: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
}


// Função para cadastrar um cliente
int cadastrarCliente(sqlite3 *db, const char *nome, const char *tel, const char *cpf) {
    if (cpfExiste(db, cpf)) {
        printf("CPF já cadastrado!\n");
        return -1;
    }

    const char *sql = "INSERT INTO CLIENTE (NOME, TEL, CPF) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
        return rc;
    }
    sqlite3_bind_text(stmt, 1, nome, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, tel, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, cpf, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro ao inserir dados: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
    return rc;
}


int countClientes() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM cliente";
    int rc, count = 0;

    // Abre a conexão com o banco de dados
    rc = sqlite3_open("ticketing.db", &db);
    if (rc) {
        fprintf(stderr, "Não foi possível abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    // Prepara a consulta SQL
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    // Executa a consulta e obtém o resultado
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    } else {
        fprintf(stderr, "Erro ao executar a consulta: %s\n", sqlite3_errmsg(db));
    }

    // Finaliza a consulta e fecha a conexão
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return count;
}

