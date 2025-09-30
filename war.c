#include <stdio.h>
#include <string.h>

// Definição da struct  = Territorio
// Esta estrutura agrupa as informações do território:
// - nome: nome do território
// - cor: cor do exército 
// - tropas: quantidade de tropas disponíveis de cada exército
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    // Vetor para armazenar até 5 territórios
    Territorio territorios[5];

    // Entrada de dados para os 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("\nCadastro do Territorio %d:\n", i + 1);

        // Leitura do nome do território
        printf("Digite o nome do territorio: ");
        scanf(" %[^\n]", territorios[i].nome); // lê até encontrar ENTER

        // Leitura da cor do exército
        printf("Digite a cor do exercito: ");
        scanf(" %s", territorios[i].cor); // lê apenas uma palavra

        // Leitura do número de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados cadastrados
    printf("\n===== Dados dos Territorios Cadastrados =====\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exercito: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}