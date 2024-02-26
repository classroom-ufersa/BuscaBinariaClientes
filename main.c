#include "cliente.h"

int main(void)
{
    printf("Inicializando sistema...\n");
    int qtdClientes, comando;
    struct cliente *clientes = contaClientes(&qtdClientes);
    
    do
    {
        printf("_-_-_- M E N U _-_-_-\n");
        printf("1 - Buscar cliente por ID\n");
        printf("2 - Buscar cliente por nome\n");
        printf("3 - Adicionar novo cliente\n");
        printf("4 - Sair\n");
        printf("_-_-_-_-_-_-_-_-_-_-_-_-\n");
        coletaDados(clientes, qtdClientes);
            while (1) {
        printf("Digite a opcao desejada: \n");
        if (scanf("%d", &comando) == 1) {
            break;
        } else {
            while (getchar() != '\n');
            printf("Entrada invalida. Por favor, insira um numero inteiro.\n");
        }
    }
        switch (comando)
        {
        case 1:
            buscaBinariaId(clientes, qtdClientes);
            break;
        case 2:
            buscaBinariaNome(clientes, qtdClientes);
            break;
        case 3:
            qtdClientes = addCliente(&qtdClientes, &clientes);
            break;
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (comando != 4);

    free(clientes);
    return 0;
}
