#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOLD "\033[1m"
#define RESET "\033[0m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define CYAN "\033[36m"

#define USERNAME "cadm"
#define PASSWORD "c123"


typedef struct {
    int id;
    char nome[50];
    float preco;
    int estoque;
} Produto;

typedef struct {
    int id;
    char nome[50];
    char email[50];
} Cliente;

typedef struct {
    int id;
    int id_produto;
    int id_cliente;
    int quantidade;
} Venda;


void salvarProdutos(Produto *produtos, int quantidade);
void carregarProdutos(Produto *produtos, int *quantidade);
void salvarClientes(Cliente *clientes, int quantidade);
void carregarClientes(Cliente *clientes, int *quantidade);
void salvarVendas(Venda *vendas, int quantidade);
void carregarVendas(Venda *vendas, int *quantidade);


void login();
void menu();
void adicionarProduto(Produto *produtos, int *quantidade);
void editarProduto(Produto *produtos, int quantidade);
void removerProduto(Produto *produtos, int *quantidade);
void consultarProdutos(Produto *produtos, int quantidade);
void controleEstoque(Produto *produtos, int quantidade);
void registrarVenda(Venda *vendas, int *quantidade_vendas, Produto *produtos, int quantidade_produtos, Cliente *clientes, int quantidade_clientes);
void relatorioVendas(Venda *vendas, int quantidade_vendas, Produto *produtos, int quantidade_produtos, Cliente *clientes, int quantidade_clientes);
void cadastrarCliente(Cliente *clientes, int *quantidade_clientes);
void limparTela();
void pressionarQualquerTecla();

int main() {
    Produto produtos[100];
    Cliente clientes[100];
    Venda vendas[100];
    int quantidade_produtos = 0, quantidade_clientes = 0, quantidade_vendas = 0;
    int opcao;

    
    login();

    
    carregarProdutos(produtos, &quantidade_produtos);
    carregarClientes(clientes, &quantidade_clientes);
    carregarVendas(vendas, &quantidade_vendas);

    while (1) {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarProduto(produtos, &quantidade_produtos);
                salvarProdutos(produtos, quantidade_produtos);
                break;
            case 2:
                editarProduto(produtos, quantidade_produtos);
                salvarProdutos(produtos, quantidade_produtos);
                break;
            case 3:
                removerProduto(produtos, &quantidade_produtos);
                salvarProdutos(produtos, quantidade_produtos);
                break;
            case 4:
                consultarProdutos(produtos, quantidade_produtos);
                break;
            case 5:
                controleEstoque(produtos, quantidade_produtos);
                break;
            case 6:
                registrarVenda(vendas, &quantidade_vendas, produtos, quantidade_produtos, clientes, quantidade_clientes);
                salvarVendas(vendas, quantidade_vendas);
                salvarProdutos(produtos, quantidade_produtos); // Salva o estoque atualizado
                break;
            case 7:
                relatorioVendas(vendas, quantidade_vendas, produtos, quantidade_produtos, clientes, quantidade_clientes);
                break;
            case 8:
                cadastrarCliente(clientes, &quantidade_clientes);
                salvarClientes(clientes, quantidade_clientes);
                break;
            case 9:
                printf(GREEN "\nSaindo do sistema. Até logo!\n" RESET);
                exit(0);
            default:
                printf(RED "Opção inválida! Tente novamente.\n" RESET);
        }
        pressionarQualquerTecla();
    }
    return 0;
}
