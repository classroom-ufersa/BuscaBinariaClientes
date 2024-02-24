#include "cliente.h"

int main(void)
{
    int qtdClientes;
    // Criando um ponteiro para struct e chamando a função para a contagem e alocação:
    struct cliente *clientes = contaClientes(&qtdClientes);

    // Passo o array e a quantidade de clientes obtida:
    coletaDados(clientes, qtdClientes);
    // Chamada da função buscaBinaria_id.
    buscaBinariaId(clientes, qtdClientes);

    // Liberando a memória:
    free(clientes);

    return 0;
}
