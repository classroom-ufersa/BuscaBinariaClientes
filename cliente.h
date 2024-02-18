#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct do cliente:
struct cliente;
// Função para coleta de dados:
void coletaDados(struct cliente *clientes, int qtdC);
// Função para contar quantos clientes existem no arquivo e alocação de memória:
struct cliente *contaClientes(int *qtdC);
// Função para mostrar dados (verificação do array)
void mostrarDados(struct cliente *Cliente, int qtdClientes);

/*Função para compara o id dos clientes*/
int comparaID(const void * pa, const void * pb);

/*Função que ordena os clientes pelo id*/
void ordenaId(struct cliente *Cliente, int qtdClientes);

// Função para buscar o ID do cliente(Busca binária por ID)
void buscaBinaria_id(struct cliente *clientes, int qtdC);

/*Função para compara o nome dos clientes*/
int comparaNome(const void * pa, const void * pb);

/*Função que ordena os clientes pelo nome*/
void ordenaNome(struct cliente *Cliente, int qtdClientes);