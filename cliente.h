// Protótipo das funções

// Struct do cliente:
struct cliente;
// Função para coleta de dados:
void coletaDados(struct cliente *clientes, int qtdC);
// Função para contar quantos clientes existem no arquivo e alocação de memória:
struct cliente *contaClientes(int *qtdC);
// Função para mostrar dados (verificação do array)
void mostrarDados(struct cliente *Cliente, int qtdClientes);