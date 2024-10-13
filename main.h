#include <string.h>

#define MAX_TAM 100


// Definição de uma estrutura que representa um chamado
typedef struct {
    char valor[MAX_TAM];
    int id;                // ID do chamado
    char nome[80];     // Nome do cliente
    char telefone[15]; // Telefone do cliente
    char email[100];    // Email do cliente
    char texto[MAX_TAM];    // Texto do chamado (a dúvida ou questão do cliente)
    char status[MAX_TAM];   // Status do chamado (ex.: "ABERTO", "PENDENTE" ,"FECHADO")
    char resolucao[MAX_TAM]; // Resolução do chamado (se houver)
    char cpf[MAX_TAM];
} Chamado;
