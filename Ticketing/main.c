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


int consultarStatusChamados(sqlite3 *db, int *abertos, int *fechados, int *pendentes) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT STATUS, COUNT(*) FROM TICKET GROUP BY STATUS";
    int rc;

    // Prepara a consulta SQL
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    // Executa a consulta e obtém os resultados
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char *status = sqlite3_column_text(stmt, 0);
        int count = sqlite3_column_int(stmt, 1);

        if (strcmp((const char *)status, "Aberto") == 0) {
            *abertos = count;
        } else if (strcmp((const char *)status, "Fechado") == 0) {
            *fechados = count;
        } else if (strcmp((const char *)status, "Pendente") == 0) {
            *pendentes = count;
        }
    }

    // Finaliza a consulta
    sqlite3_finalize(stmt);

    return SQLITE_OK;
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


// Função para consultar um cliente por CPF
int consultarClientePorCPF(sqlite3 *db, const char *cpf, int *id_cliente) {
    char *errMsg = 0;
    const char *sql = "SELECT ID_CLIENTE FROM CLIENTE WHERE CPF = ?;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    sqlite3_bind_text(stmt, 1, cpf, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *id_cliente = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return SQLITE_OK;
    } else {
        printf("Cliente não encontrado.\n");
        sqlite3_finalize(stmt);
        return SQLITE_NOTFOUND;
    }
}

// Função para alterar o cadastro de um cliente
int alterarCliente(sqlite3 *db, const char *cpf, const char *novoNome, const char *novoTel) {
    const char *sql = "UPDATE CLIENTE SET NOME = ?, TEL = ? WHERE CPF = ?;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar statement: %s\n", sqlite3_errmsg(db));
        return rc;
    }
    sqlite3_bind_text(stmt, 1, novoNome, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, novoTel, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, cpf, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro ao atualizar dados: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Dados do cliente atualizados com sucesso.\n");
    }
    sqlite3_finalize(stmt);
    return rc;
}


int inserirRelato(sqlite3 *db, int id_cliente, const char *relato) {
    char *errMsg = 0;
    char sql[512];
    sprintf(sql, "INSERT INTO TICKET (ID_CLIENTE, RELATO, RESOLUCAO, STATUS) VALUES (%d, '%s', 'Pendente', 'Aberto');", id_cliente, relato);

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return rc;
    } else {
        printf("Relato inserido com sucesso\n");
    }
    return SQLITE_OK;
}

int alterarChamado(sqlite3 *db, int id_ticket, const char *resolucao, const char *status, int valor) {
    char *errMsg = 0;
    char sql[512];
    sprintf(sql, "UPDATE TICKET SET RESOLUCAO = '%s', STATUS = '%s', VALOR = %d WHERE ID_TICKET = %d;", resolucao, status, valor, id_ticket);

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return rc;
    } else {
        printf("Chamado alterado com sucesso\n");
    }
    return SQLITE_OK;
}


int consultarTickets(sqlite3 *db) {
    char *errMsg = 0;
    const char *sql = "SELECT * FROM TICKET;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id_ticket = sqlite3_column_int(stmt, 0);
        int id_cliente = sqlite3_column_int(stmt, 1);
        const unsigned char *relato = sqlite3_column_text(stmt, 2);
        const unsigned char *resolucao = sqlite3_column_text(stmt, 3);
        const unsigned char *status = sqlite3_column_text(stmt, 4);
        int valor = sqlite3_column_int(stmt, 5);

        printf("ID_TICKET: %d\n", id_ticket);
        printf("ID_CLIENTE: %d\n", id_cliente);
        printf("RELATO: %s\n", relato);
        printf("RESOLUCAO: %s\n", resolucao);
        printf("STATUS: %s\n", status);
        printf("VALOR: %d\n", valor);
        printf("\n");
    }

    sqlite3_finalize(stmt);
    return SQLITE_OK;
}
