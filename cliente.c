// Bibliotecas usadas aqui:
#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"

struct cliente
{
    char nome[50];
    char endereco[70];
    int id;
};
// Como utilizo essa função para contar e alocar, preciso receber o array, então:
struct cliente *contaClientes(int *qtdC)
{
    // Declarando variáveis:
    int tamanho = 0;
    char linha[101];
    FILE *arquivo;

    arquivo = fopen("DataBase.txt", "r");

    // No arquivo de texto, uma linha representa um cliente. Então contamos:
    while (fscanf(arquivo, "%[^\n]\n", linha) != EOF)
    {
        tamanho++;
    }

    // Fechando...
    fclose(arquivo);

    // Aloca memória para o número de clientes
    struct cliente *clientes = malloc(tamanho * sizeof(struct cliente));

    // Retorna o número de clientes através do ponteiro qtdC
    *qtdC = tamanho;

    // Retorna o array para que possa ser utilizado em outros lugares do código:
    return clientes;
}

// Função para leitura e coleta dos dados:
void coletaDados(struct cliente *clientes, int qtdC)
{
    // Declarando as variáveis:
    int i = 0;

    FILE *dados;
    dados = fopen("DataBase.txt", "r");

    // Criando um loop até o fim do arquivo...
    while (i < qtdC)
    {
        fscanf(dados, " %[^\t]\t %[^\t]\t%d", clientes[i].nome, clientes[i].endereco, &clientes[i].id);
        i++;
    }

    // Fechando...
    fclose(dados);
}
// Função para mostrar dados (apenas para fins de verificação):
void mostrarDados(struct cliente *Cliente, int qtdClientes)
{
    int j;
    for (j = 0; j < qtdClientes; j++)
    {
        printf("Nome: %s, Endereço: %s, ID: %d\n", Cliente[j].nome, Cliente[j].endereco, Cliente[j].id);
    }
};