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
    int max = qtdClientes - 1; // Define a maior posição de (0 - 49) = 50 - 1 = 49.
    int min = 0; // Define a menor posição que o número deve estar.
    int meio = 0; // A posição média será max + min/ 2 quebrando ao meio.

    clock_t inicio = clock();
    while(min <= max){
        // Middle será a posição do meio no caso sempre será o resultado dessa conta.
        meio = ((max + min)/2); 

        if(clientes[meio].id == numeroDesejado){ 
            // Quando o middle for o numero desejado ele imprime os dados.
            printf("Nome: %s\n", clientes[meio].nome);
            printf("Endereco: %s\n", clientes[meio].endereco);
            printf("ID: %d\n", clientes[meio].id);
            encontrado = 1; // se o id e seus dados correspondentes forem encontrado.
            break;
        }else{
            if (clientes[meio].id > numeroDesejado){ 
                max = meio - 1; 
                //  Se a middle for maior que o número desejado, a direita é deletada.
            }else{
                min = meio + 1;
                //  Se o Middle_posicion for menor que o número desejado, .a esquerda é deletada. 
            }
        }
    }
    if (!encontrado) {
        // Se o id e seus dados correspondentes não forem encontrado.
        printf("ID nao encontrado.\n");
    } 

    long double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %Le\n", tempo);
}

void buscaBinariaNome(struct cliente *clientes, int qtdClientes)
{
    ordenaNome(clientes, qtdClientes);
    char nomeDesejado[50]; //vai armazenar o nome que o usário deseja buscar
    int encontrado = 0; 
    int min = 0; //parte iniical do vetor
    int max = qtdClientes - 1; //fim do vetor
    int meio = 0;
    printf("Digite o nome desejado: \n");
    scanf(" %[^\n]", nomeDesejado); //está recebendo o nome que deve ser buscado

    clock_t inicio = clock();
    while(min <= max ){ //enquanto o valor inicial do vetor for menor ou igual ao final, vai realizar a operação até que se encontre o nome desejadoo
        meio = (min+max)/2;
        
        int comparacao = strcmp(clientes[meio].nome, nomeDesejado); //realiza a comparação das strings
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
           }else{ //se o nome buscado é menor que o do meio do vetor
                min = meio + 1; //atualiza o índice para a parte que é superior do vetor
            }
    }
    if (!encontrado) {
        // Se o id e seus dados correspondentes não forem encontrado.
        printf("Cliente nao encontrado.\n");
    }

    long double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %Le\n", tempo);
}

int addCliente(int *num, struct cliente **clientes) {
    FILE *arquivo;
    arquivo = fopen("DataBase.txt", "a");

    printf("Digite o nome do cliente: \n");
    scanf(" %[^\n]", (*clientes)[*num].nome);
    printf("Digite o endereço do cliente: \n");
    scanf(" %[^\n]", (*clientes)[*num].endereco);
    (*clientes)[*num].id = *num + 1;
    fprintf(arquivo, "%s\t%s\t%d\n", (*clientes)[*num].nome, (*clientes)[*num].endereco, (*clientes)[*num].id);
    fclose(arquivo);

    *clientes = realloc(*clientes, (*num + 2) * sizeof(struct cliente));
    if (*clientes == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    return ++*num;
}


