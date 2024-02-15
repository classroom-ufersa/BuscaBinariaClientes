// Bibliotecas usadas aqui:
#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"

int main(void)
{
    int qtdClientes, j;
    // Criando um ponteiro para struct e chamando a função para contagem e alocação:
    struct cliente *clientes = contaClientes(&qtdClientes);
    // Passo o array e a quantidade de clientes obtida:
    coletaDados(clientes, qtdClientes);

    // Imprimindo os dados coletados (para fins de verificação):
    for (j = 0; j < qtdClientes; j++)
    {
        printf("Nome: %s, Endereço: %s, ID: %d\n", clientes[j].nome, clientes[j].endereco, clientes[j].id);
    }

    // Liberando a memória:
    free(clientes);

    return 0;
}
