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

void login() {
    char username[50];
    char password[50];

    printf(BOLD BLUE "\n EASY-STORE™ - Sistema de Gestão\n" RESET);
    printf("\n" BOLD "Digite seu usuário: " RESET);
    scanf("%s", username);

    printf(BOLD "Digite sua senha: " RESET);
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf(GREEN "\nLogin bem-sucedido! Bem-vindo(a), %s!\n\n" RESET, username);
    } else {
        printf(RED "\nUsuário ou senha incorretos. Encerrando o sistema.\n" RESET);
        exit(0);
    }
}

void menu() {
    limparTela();
    printf(CYAN "\n==================== MENU ====================\n" RESET);
    printf(BOLD "1. " RESET "Adicionar Produto\n");
    printf(BOLD "2. " RESET "Editar Produto\n");
    printf(BOLD "3. " RESET "Remover Produto\n");
    printf(BOLD "4. " RESET "Consultar Produtos\n");
    printf(BOLD "5. " RESET "Controle de Estoque\n");
    printf(BOLD "6. " RESET "Registrar Venda\n");
    printf(BOLD "7. " RESET "Relatório de Vendas\n");
    printf(BOLD "8. " RESET "Cadastrar Cliente\n");
    printf(BOLD "9. " RESET "Sair\n");
    printf(CYAN "==============================================\n" RESET);
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pressionarQualquerTecla() {
    printf("\nPressione qualquer tecla para continuar...");
    getchar(); 
    getchar(); 
}

void adicionarProduto(Produto *produtos, int *quantidade) {
    Produto p;
    p.id = *quantidade + 1;
    printf(BOLD "\nAdicionando novo produto:\n" RESET);
    printf("Nome do Produto: ");
    getchar(); 
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = 0; 
    printf("Preço do Produto: ");
    scanf("%f", &p.preco);
    printf("Quantidade em Estoque: ");
    scanf("%d", &p.estoque);
    produtos[*quantidade] = p;
    (*quantidade)++;
    printf(GREEN "Produto adicionado com sucesso!\n" RESET);
}

void editarProduto(Produto *produtos, int quantidade) {
    int id;
    printf(BOLD "\nEditar Produto\n" RESET);
    printf("ID do Produto para editar: ");
    scanf("%d", &id);
    if (id < 1 || id > quantidade) {
        printf(RED "Produto não encontrado!\n" RESET);
        return;
    }
    Produto *p = &produtos[id - 1];
    printf("Novo Nome: ");
    getchar(); 
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = 0; 
    printf("Novo Preço: ");
    scanf("%f", &p->preco);
    printf("Nova Quantidade em Estoque: ");
    scanf("%d", &p->estoque);
    printf(GREEN "Produto atualizado com sucesso!\n" RESET);
}

void removerProduto(Produto *produtos, int *quantidade) {
    int id;
    printf(BOLD "\nRemover Produto\n" RESET);
    printf("ID do Produto para remover: ");
    scanf("%d", &id);
    if (id < 1 || id > *quantidade) {
        printf(RED "Produto não encontrado!\n" RESET);
        return;
    }
    for (int i = id - 1; i < *quantidade - 1; i++) {
        produtos[i] = produtos[i + 1];
    }
    (*quantidade)--;
    printf(GREEN "Produto removido com sucesso!\n" RESET);
}

void consultarProdutos(Produto *produtos, int quantidade) {
    printf(BOLD "\nConsulta de Produtos\n" RESET);
    for (int i = 0; i < quantidade; i++) {
        printf("ID: %d, Nome: %s, Preço: %.2f, Estoque: %d\n", produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
    }
}