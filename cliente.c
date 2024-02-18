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

int comparaID(const void * pa, const void * pb){
    const struct cliente * p1 = pa;
    const struct cliente * p2 = pb;
    return p1->id - p2->id;
}

void ordenaId(struct cliente *Cliente, int qtdClientes){
    qsort(Cliente, qtdClientes, sizeof(struct cliente), comparaID);
}

int comparaNome(const void * pa, const void * pb){
    const struct cliente * p1 = pa;
    const struct cliente * p2 = pb;
    return strcmp(p1->nome, p2->nome);
}

void ordenaNome(struct cliente *Cliente, int qtdClientes){
    qsort(Cliente, qtdClientes, sizeof(struct cliente), comparaNome);
}

// Função para buscar o cliente pelo ID (Busca Binária por ID).
void buscaBinaria_id(struct cliente *clientes, int qtdC){
    int Numero_desejado;
    char continuar;
    do {
        int encontrado = 0; 
        printf("Informe o algarismo correspondente ao ID caro senhor(a):\n");
        scanf("%d", &Numero_desejado);
        int MAX_posicion = qtdC - 1; // Define a maior posição de (0 - 49) = 50 - 1 = 49.
        int MIN_posicion = 0; // Define a menor posição que o número deve estar.
        int Middle_posicion = 0; // A posição média será max + min/ 2 quebrando ao meio.

        while(MIN_posicion <= MAX_posicion){
            // Middle será a posição do meio no caso sempre será o resultado dessa conta.
            Middle_posicion = ((MAX_posicion + MIN_posicion)/2); 

            if(clientes[Middle_posicion].id == Numero_desejado){ 
                // Quando o middle for o numero desejado ele imprime os dados.
                printf("Nome: %s\n", clientes[Middle_posicion].nome);
                printf("Endereco: %s\n", clientes[Middle_posicion].endereco);
                printf("ID: %d\n", clientes[Middle_posicion].id);
                encontrado = 1; // se o id e seus dados correspondentes forem encontrado.
                break;
            }else{
                if (clientes[Middle_posicion].id > Numero_desejado){ 
                    MAX_posicion = Middle_posicion - 1; 
                    //  Se a middle for maior que o número desejado, a direita é deletada.
                }else{
                    MIN_posicion = Middle_posicion + 1;
                    //  Se o Middle_posicion for menor que o número desejado, .a esquerda é deletada. 
                }
            }
        }

        if (!encontrado) {
            // Se o id e seus dados correspondentes não forem encontrado.
            printf("ID nao encontrado.\n");
        } 
// loop para o usuário escolher escolher se continua a procurar.
        printf("Deseja continuar procurando IDs ?\n s = Sim\n n = Nao\n");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');
}
