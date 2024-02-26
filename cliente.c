#include "cliente.h"

struct cliente
{
    char nome[200];
    char endereco[200];
    int id;
};

struct cliente *contaClientes(int *qtdC){
    int tamanho = 0;
    char linha[101];
    FILE *arquivo;

    arquivo = fopen("DataBase.txt", "r");

    while (fscanf(arquivo, "%[^\n]\n", linha) != EOF){
        tamanho++;
    }

    fclose(arquivo);

    struct cliente *clientes = malloc(tamanho * sizeof(struct cliente));

    *qtdC = tamanho;

    return clientes;
}

void coletaDados(struct cliente *clientes, int qtdC){
    int i = 0;

    FILE *dados;
    dados = fopen("DataBase.txt", "r");

    while (i < qtdC){
        fscanf(dados, " %[^\t]\t %[^\t]\t%d", clientes[i].nome, clientes[i].endereco, &clientes[i].id);
        i++;
    }

    fclose(dados);
}

void mostrarDados(struct cliente *Cliente, int qtdClientes){
    int j;
    for (j = 0; j < qtdClientes; j++){
        printf("Nome: %s, Endereço: %s, ID: %d\n", Cliente[j].nome, Cliente[j].endereco, Cliente[j].id);
    }
}

int comparaID(const void * pointerA, const void * pointerB){
    const struct cliente * pointer1 = pointerA;
    const struct cliente * pointer2 = pointerB;
    return pointer1->id - pointer2->id;
}

void ordenaId(struct cliente *Cliente, int qtdClientes){
    qsort(Cliente, qtdClientes, sizeof(struct cliente), comparaID);
}

int comparaNome(const void * pointerA, const void * pointerB){
    const struct cliente * pointer1 = pointerA;
    const struct cliente * pointer2 = pointerB;
    return strcmp(pointer1->nome, pointer2->nome);
}

void ordenaNome(struct cliente *Cliente, int qtdClientes){
    qsort(Cliente, qtdClientes, sizeof(struct cliente), comparaNome);
}

// Função para buscar o cliente pelo ID (Busca Binária por ID).
void buscaBinariaId(struct cliente *clientes, int qtdClientes){
    ordenaId(clientes, qtdClientes);
    int numeroDesejado = 0;
    int encontrado = 0; 
    printf("Informe o Id do cliente: \n");
    scanf(" %d", &numeroDesejado);
    int max = qtdClientes - 1; 
    int min = 0; 
    int meio = 0;

    clock_t inicio = clock();
    while(min <= max){
        meio = ((max + min)/2); 

        if(clientes[meio].id == numeroDesejado){ 
            printf("Nome: %s\n", clientes[meio].nome);
            printf("Endereco: %s\n", clientes[meio].endereco);
            printf("ID: %d\n", clientes[meio].id);
            encontrado = 1;
            break;
        }else{
            if (clientes[meio].id > numeroDesejado){ 
                max = meio - 1; 
            }else{
                min = meio + 1;
            }
        }
    }
    if (!encontrado) {
        printf("ID nao encontrado.\n");
    } 

    long double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %Le\n", tempo);
}

void buscaBinariaNome(struct cliente *clientes, int qtdClientes)
{
    ordenaNome(clientes, qtdClientes);
    char nomeDesejado[50];
    int encontrado = 0; 
    int min = 0; 
    int max = qtdClientes - 1;
    int meio = 0;
    printf("Digite o nome desejado: \n");
    scanf(" %[^\n]", nomeDesejado);

    clock_t inicio = clock();
    while(min <= max ){
        meio = (min+max)/2;
        
        int comparacao = strcmp(clientes[meio].nome, nomeDesejado);
            if(comparacao == 0){
                printf("================================\n");
                printf("Nome: %s\n", clientes[meio].nome);
                printf("Endereço: %s \n", clientes[meio].endereco);
                printf("ID: %d\n", clientes[meio].id);
                printf("================================\n");
                break;
            } 
            else if(comparacao > 0) { 
                max = meio -1;
           }else{
                min = meio + 1;
            }
    }
    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }

    long double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %Le\n", tempo);
}

int addCliente(int *num, struct cliente **clientes) {
    FILE *arquivo;
    arquivo = fopen("DataBase.txt", "a");

    printf("Digite o nome do cliente: \n");
    getchar();
    scanf(" %[^\n]", (*clientes)[*num].nome);
    printf("Digite o endereço do cliente: \n");
    scanf(" %[^\n]", (*clientes)[*num].endereco);
    (*clientes)[*num].id = *num + 1;
    fprintf(arquivo, "%s\t%s\t%d\n", (*clientes)[*num].nome, (*clientes)[*num].endereco, (*clientes)[*num].id);
    fclose(arquivo);

    *clientes = realloc(*clientes, (*num + 1) * sizeof(struct cliente));
    if (*clientes == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    return ++*num;
}