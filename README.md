# Busca Binária

## Problemática
- Implementar um algoritmo que manipula um tipo estruturado Clientes e possui a funcionalidade de buscar os clientes em um arquivo.

## Desenvolvedores
- Artur Carvalho Gama
- Gustavo Rodrigues
- José Kayque
- Maria Eduarda 

## Requisitos atendidos
-  A execução do programa, carrega os dados (armazenados em um arquivo texto);
-  O programa  pergunta ao usuário  qual cliente ele deseja buscar por nome ou código com o algoritmo Busca Binária;
-  É computado o tempo de execução do processo de busca.
-  Informado a complexidade do algoritmo do algoritmo Busca Binária.

## Implementação das Funções e a Struct
- O arquivo de código-fonte cliente.c contém todas as funções-chave para a Busca Binária. Vamos apresentá-las e explicar suas funcionalidades.

## A Struct cliente
- Nesta struct, estão as variáveis que serão manipuladas.
``` c
- struct cliente
{
    char nome[50];
    char endereco[70];
    int id;
};
``` 
## A Função contaClientes
- Essa função é responsável por ler o arquivo de texto chamado “DataBase.txt”, conta quantas linhas (Com representativa clientes) estão presentes no arquivo e aloca memória para armazenar os dados dos clientes. 
- O número total de clientes será retornado através do ponteiro qtdC, e o array de clientes é devolvido para uso em outras partes do código. 

``` c 
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
```

## Função coletaDados
- Resposável por coletar os dados de um arquivo chamado "DataBase.txt", tornandos os dados disponíveis para as demais partes do programa.

-  A função abre o arquivo "DataBase.txt" no modo de leitura "r". 

- Em seguida temos um loop que lê cada linha do arquivo até atingir o número total de clientes na "qtdC". Para cada linha, ela utiliza "fscanf" para extrair informações, como o nome, endereço e ID do cliente.

- Logo depois, os dados lidos são armazenados na estrutura de dados "clientes", que é um array de estruturas do tipo "struct cliente". Assim, ao finalizar é fechado o arquivo.

```c
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
```
## Função mostrarDados
- Essa função tem a finalidade de exibir os dados dos clientes.

- Com os parâmetros de entrada, acompanhados com um loop de exibição e finalmente o formatdo de entrada é mostrado e exibido na final todos os dados do "DataBase.txt".

```c 
// Função para mostrar dados (apenas para fins de verificação):
void mostrarDados(struct cliente *Cliente, int qtdClientes)
{
    int j;
    for (j = 0; j < qtdClientes; j++)
    {
        printf("Nome: %s, Endereço: %s, ID: %d\n", Cliente[j].nome, Cliente[j].endereco, Cliente[j].id);
    }
};

```

## Função comparaID
- Ela é "int", porque é uma função de comparação usada em algoritmos de ordenação.

- A comparação é feita como os parâmetros "pointerA" e "pointerB", que são ponteiros apontados para a struct cliente.

- Esses ponteiros são convertidos para ponteiros específicos do tipo const struct cliente *.

- Temos os cálculo da diferença entre os IDs dos clientes apontados por pointer1 e pointer2.

- O resultado será inteiro, assim teremos em síntese que: 
. Se for negativo, significa que o ID de pointer1 é menor que o de pointer2.
. Se for positivo, significa o contrário.
. Se for zero, os IDs são iguais.

```c
int comparaID(const void * pointerA, const void * pointerB){
    const struct cliente * pointer1 = pointerA;
    const struct cliente * pointer2 = pointerB;
    return pointer1->id - pointer2->id;
}
```

## Função ordenaID e ordenaNome
- Nessa função temos qsort é uma função de biblioteca padrão em C que realiza a ordenação.

```c
 void ordenaId(struct cliente *Cliente, int qtdClientes){
    qsort(Cliente, qtdClientes, sizeof(struct cliente), comparaID);
}
```
```c
void ordenaNome(struct cliente *Cliente, int qtdClientes){
    qsort(Cliente, qtdClientes, sizeof(struct cliente), comparaNome);
}
```

## Função comparaNome
- Essa funcionalidade  é usada para comparar os nomes dos clientes. 

- Na entrada pointerA e pointerB são ponteiros para dados. Nesse caso, eles apontam para estruturas do tipo struct cliente.
- Esses ponteiros são convertidos para ponteiros específicos do tipo const struct cliente *.

- Na Comparação de Nomes temos,o comando strcmp na comparação de nomes apontados por pointer1 e pointer2.
- O resultado será inteiro e teremos:
. Se for negativo, significa que o nome de pointer1 vem antes do nome de pointer2 na ordem alfabética.
. Se for positivo, significa o contrário.
. Se for zero, os nomes são iguais.

- Retornado o resultado ordenado.

```c
int comparaNome(const void * pointerA, const void * pointerB){
    const struct cliente * pointer1 = pointerA;
    const struct cliente * pointer2 = pointerB;
    return strcmp(pointer1->nome, pointer2->nome);
}

```

## Função BuscBinariaId
. Terá funcionalidade para buscar um cliente pelo ID usando o método de busca binária. 

. A função começa ordenando os clientes pelo ID usando a função ordenaId.

. Em seguida, solicita ao usuário que informe o ID do cliente que deseja buscar.

. Define max como a maior posição possível (quantidade de clientes - 1) e min como a menor posição possível (0).

. Teremos um loop enquanto min for menor ou igual a max. Dentro deste loop:

   . Calcula meio como a posição média entre min e max.

   . Se o ID do cliente na posição meio for igual ao número desejado, imprime os dados do cliente e define encontrado como 1 (verdadeiro).

   . Se o ID do cliente na posição meio for maior que o número desejado, atualiza max para ser meio - 1.

   . Se o ID do cliente na posição meio for menor que o número desejado, atualiza min para ser meio + 1.

 . Se o loop encontrar encontrar o cliente, imprime os dados correspondente  se não imprime "ID não encontrado".

 . Finalmente, calcula e imprime o tempo de execução da função.

```c
// Função para buscar o cliente pelo ID (Busca Binária por ID).
void buscaBinariaId(struct cliente *clientes, int qtdClientes){
    ordenaId(clientes, qtdClientes);
    int numeroDesejado = 0;
    int encontrado = 0; 
    printf("Informe o Id do cliente: \n");
    scanf("%d", &numeroDesejado);
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

```

## Função buscaBinariaNome

. A função buscaBinariaNome busca um cliente pelo nome em um vetor de clientes usando a busca binária. 

. A função ordena os clientes pelo nome.

. Solicita que digite o nome do cliente que deseja buscar.

. Entra em um loop enquanto o valor inicial do vetor for menor ou igual ao final.

. Calcula a posição média entre o início e o fim do vetor.

. Compara o nome na posição média com o nome desejado.

. Se os nomes forem iguais, imprime os detalhes do cliente e sai do loop.

. Se o nome na posição média for maior que o nome desejado, atualiza o fim do vetor para ser a posição média - 1.

. Se o nome na posição média for menor que o nome desejado, atualiza o início do vetor para ser a posição média + 1.

. Se o loop terminar sem encontrar o cliente, imprime "Cliente não encontrado".

. Finalmente, calcula e imprime o tempo de execução da função. 

```c
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

```

## Em cliente.h 
- Teremos a chamada das funções e da struct.
```h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Struct do cliente*/
struct cliente;

/*Função para coleta de dados*/
void coletaDados(struct cliente *clientes, int qtdC);

/*Função para contar quantos clientes existem no arquivo e alocação de memória*/
struct cliente *contaClientes(int *qtdC);

/*Função para mostrar dados (verificação do array)*/
void mostrarDados(struct cliente *Cliente, int qtdClientes);

/*Função para compara o id dos clientes*/
int comparaID(const void * pa, const void * pb);

/*Função que ordena os clientes pelo id*/
void ordenaId(struct cliente *Cliente, int qtdClientes);

/*Função para buscar o ID do cliente(Busca binária por ID)*/
void buscaBinariaId(struct cliente *clientes, int qtdC);

/*Função para compara o nome dos clientes*/
int comparaNome(const void * pa, const void * pb);

/*Função que ordena os clientes pelo nome*/
void ordenaNome(struct cliente *Cliente, int qtdClientes);

/*Função que realiza a Busca Binária pelo nome do cliente*/
void buscaBinariaNome(struct cliente *clientes, int qtdClientes);

/*Função para adicionar um novo cliente ao arquivo*/
int addCliente(int *num, struct cliente **clientes);

```

## Em main.c 
- O programa começa incluindo o arquivo "cliente.h".

. A quantidade de clientes é determinada pela função contaClientes.

. O programa entra em um loop do-while, que continua até que o usuário insira o comando 4 para sair.

. Dentro do loop, o programa exibe um menu com quatro opções.

. O programa coleta os dados dos clientes e pede ao usuário para digitar a opção desejada.

. Dependendo da opção escolhida pelo usuário, o programa executa uma das ações.

. Finalmente, o programa libera a memória alocada para os clientes e termina.

````c
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
        printf("Digite a opcao desejada: ");
        scanf(" %d", &comando);

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
````


## Complexidade do código: 
. A essência da busca binária é a divisão sucessiva de N , onde N é o tamanho do vetor (início do vetor + última posição do vetor), por 2k, em que k é o total de possibilidades, até ser encontrado o target, ou, no pior caso, ( N)/2^k =1. Assim, podemos definir K como: 
````

                            N/2^k =1
                            N=2^k
                        log_2⁡ N=log_2⁡ 2^k 
                        ∴ log _2⁡ N=k

````
-- Na análise de complexidade da busca binária po ID:
````
C1+C2+(X(C3+C4))+C5+C6+C7+C8+N/2^K(C9+C10+C11+C12+C13+C14+C15+C16+C17+C18)+C19+C20+C21+C22 
````
- (N)/(2^K) pode ser escrito por log2(n):
````
T(N)= C1+C2+(X(C3+C4))+C5+C6+C7+C8+log2N(C9+C10+C11+C12+C13+C14+C15+C16+C17+C18)+C19+C20+C21+C22 
````
- Considerando:
````
C1+C2+C5+C6+C7+C8+C19+C20+C21+C22  = A;
(X(C3+C4)) = B
C9+C10+C11+C12+C13+C14+C15+C16+C17+C18 = C
````
Temos:
T(N)= A + B+log(2) N(C)
- Em notação BigO, temos que a complexidade é O(log(2)N).
- No melhor caso temos que a complexidade será O(1),  já que para isso o valor estará no meio, realizando apenas uma divisão.

-- Agora, na busca binária por nome temos a complexidade no pior caso: 
````
T(N)= C1+C2+C3+C4+C5+C6+ C7+〖log〗_(2 ) N(C8+C9+C10+C11+C12+C13+C14+C15+C16+C17+C18+C19+C20)+C21+C22 
````
- Considerando:
````
C1+C2+C3+C4+C5+C6+ C7+C21+C22  = A;
C8+C9+C10+C11+C12+C13+C14+C15+C16+C17 +C18+C19+C20 = B
````
- Temos:
T(N)= A+(log(2)N(B)
Em notação BigO, temos que a complexidade é O(log(2)N).

- Considerando:
. C1+C2+C5+C6+C7+C8+C9+C20+C21+C22 = A;
. C8+C9+C10+C11+C12+C13+C14+C15+C16+C17+C18+C19+C20 = B
- Temos: T(N) = A+log2N(B).
- Em notação BigO, temos que a complexidade é O(log2N).
````
- E no melhor caso a complexidade será igual ao da busca binaria por ID: O(1).

## Concluímos, então, que a complexidade do algoritmo de busca binária é (O(log2⁡(N) no pior caso e O(1) no melhor caso.


## Complexidade de Espaço
Como a busca binária não usa nenhum espaço de memória extra para procurar elementos, tanto na busca binaria por id como na busca binaria por nome, temos que a sua complexidade de espaço é constante: O(1).


