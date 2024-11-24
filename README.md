# Sistema de Solicitação de Serviços

## Descrição
Este é um programa em C desenvolvido para gerenciar solicitações de serviços. O sistema permite o cadastro de clientes, geração de tickets de serviço, registro de relatos, status e valores cobrados, além de gerenciar a área do técnico responsável.

## Funcionalidades
- Cadastro de clientes
- Geração de tickets de serviço
- Registro de relatos e resoluções de serviços
- Atualização de status dos serviços
- Registro de valores cobrados
- Gerenciamento da área do técnico

## Estrutura do Projeto
- `main.c`: Arquivo principal que contém a lógica do programa.
- `main.h`: Arquivo de cabeçalho para `main.c`.
  
## Como Compilar e Executar
1. Clone o repositório:
    ```sh
    git clone https://github.com/seu-usuario/seu-repositorio.git
    ```
2. Navegue até o diretório do projeto:
    ```sh
    cd seu-repositorio
    ```
3. Compile o projeto:
    ```sh
    gcc -o sistema main.c cliente.c ticket.c tecnico.c relato.c status.c valor.c
    ```
4. Execute o programa:
    ```sh
    ./sistema
    ```

## Contribuições
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues e enviar pull requests.

## Licença
Este projeto está licenciado sob a Licença MIT. Veja o arquivo LICENSE para mais detalhes.
