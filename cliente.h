// A struct com as credenciais necessárias:
struct cliente
{
    char nome[50];
    char endereco[70];
    int id;
};

// Prototipos das demais funções:
void coletaDados(struct cliente *clientes, int qtdC);
struct cliente *contaClientes(int *qtdC);