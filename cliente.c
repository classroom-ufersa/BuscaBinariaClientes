#include "cliente.h"

struct cliente
{
    char nome[200];
    char endereco[200];
    int id;
};

struct cliente *contaClientes(int *qtdC)
{
    int tamanho = 0;
    char linha[101];
    FILE *arquivo;

    arquivo = fopen("DataBase.txt", "r");

    while (fscanf(arquivo, "%[^\n]\n", linha) != EOF)
    {
        tamanho++;
    }

    fclose(arquivo);

    struct cliente *clientes = malloc(tamanho * sizeof(struct cliente));

    *qtdC = tamanho;

    return clientes;
}

void coletaDados(struct cliente *clientes, int qtdC)
{
    int i = 0;

    FILE *dados;
    dados = fopen("DataBase.txt", "r");

    while (i < qtdC)
    {
        fscanf(dados, " %[^\t]\t %[^\t]\t%d", clientes[i].nome, clientes[i].endereco, &clientes[i].id);
        i++;
    }

    fclose(dados);
}

int comparaID(const void *pointerA, const void *pointerB)
{
    const struct cliente *pointer1 = pointerA;
    const struct cliente *pointer2 = pointerB;
    return pointer1->id - pointer2->id;
}

void ordenaId(struct cliente *Cliente, int qtdClientes)
{
    qsort(Cliente, qtdClientes, sizeof(struct cliente), comparaID);
}

int comparaNome(const void *pointerA, const void *pointerB)
{
    const struct cliente *pointer1 = pointerA;
    const struct cliente *pointer2 = pointerB;
    return strcmp(pointer1->nome, pointer2->nome);
}

void ordenaNome(struct cliente *Cliente, int qtdClientes)
{
    qsort(Cliente, qtdClientes, sizeof(struct cliente), comparaNome);
}

void buscaBinariaId(struct cliente *clientes, int qtdClientes)
{
    int numeroDesejado = 0;
    int encontrado = 0;

    while (1)
    {
        printf("Digite O ID do cliente: \n");

        if (scanf("%d", &numeroDesejado) == 1)
        {
            break;
        }
        else
        {
            while (getchar() != '\n');
            printf("Entrada invalida. Por favor, insira um numero inteiro.\n");
        }
    }

    int max = qtdClientes - 1;
    int min = 0;
    int meio = 0;

    clock_t inicio = clock();
    while (min <= max && clientes[meio].id != numeroDesejado)
    {
        meio = ((max + min) / 2);

        if (clientes[meio].id == numeroDesejado)
        {
            printf("Nome: %s\n", clientes[meio].nome);
            printf("Endereco: %s\n", clientes[meio].endereco);
            printf("ID: %d\n", clientes[meio].id);
            encontrado = 1;
            break;
        }
        else
        {
            if (clientes[meio].id > numeroDesejado)
            {
                max = meio - 1;
            }
            else
            {
                min = meio + 1;
            }
        }
    }
    if (!encontrado)
    {
        printf("ID nao encontrado.\n");
    }

    double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %Lf\n", tempo);
}

void buscaBinariaNome(struct cliente *clientes, int qtdClientes)
{
    char nomeDesejado[200];
    int encontrado = 0;
    int min = 0;
    int max = qtdClientes - 1;
    int meio = 0;
    printf("Digite o nome desejado: \n");
    scanf(" %[^\n]", nomeDesejado);

    clock_t inicio = clock();
    while (min <= max && strcmp(clientes[meio].nome, nomeDesejado) != 0)
    {
        meio = (min + max) / 2;

        int comparacao = strcmp(clientes[meio].nome, nomeDesejado);
        if (comparacao == 0)
        {
            printf("================================\n");
            printf("Nome: %s\n", clientes[meio].nome);
            printf("Endereço: %s \n", clientes[meio].endereco);
            printf("ID: %d\n", clientes[meio].id);
            printf("================================\n");
            encontrado = 1;
            break;
        }
        else if (comparacao > 0)
        {
            max = meio - 1;
        }
        else
        {
            min = meio + 1;
        }
    }
    if (!encontrado)
    {
        printf("Cliente nao encontrado.\n");
    }

    double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %Lf\n", tempo);
}

void addCliente(int num)
{
    int numeroValido;
    FILE *arquivo;
    struct cliente aux;
    arquivo = fopen("DataBase.txt", "a");
    do
    {
        printf("Digite o nome do cliente: \n");
        scanf(" %[^\n]", aux.nome);
        numeroValido = verificarDados(aux.nome);
    } while (numeroValido != 0);

    printf("Digite o endereço do cliente: \n");
    scanf(" %[^\n]", aux.endereco);
    aux.id = num + 1;
    fprintf(arquivo, "\n%s\t%s\t%d", aux.nome, aux.endereco, aux.id);
    fclose(arquivo);

}

int verificarDados(const char *str)
{
    while (*str)
    {
        if (!((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z') || *str == ' '))
        {
            printf("Digite uma entrada valida \n");
            return 1;
        }
        str++;
    }
    return 0;
}