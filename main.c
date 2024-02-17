// Bibliotecas usadas aqui:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

int main(void)
{
    int qtdClientes;
    // Criando um ponteiro para struct e chamando a função para a contagem e alocação:
    struct cliente *clientes = contaClientes(&qtdClientes);

    // Passo o array e a quantidade de clientes obtida:
    coletaDados(clientes, qtdClientes);
    mostrarDados(clientes, qtdClientes);

    // Liberando a memória:
    free(clientes);

    return 0;
}
