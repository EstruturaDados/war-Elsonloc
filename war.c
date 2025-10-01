#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==============================
// Definição da struct Territorio
// ==============================
// Esta estrutura representa um território no jogo
// - nome: nome do território (string)
// - cor: cor do exército que controla o território (string)
// - tropas: quantidade de tropas no território (inteiro)
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ==============================
// Função para cadastrar territórios
// ==============================
// Parâmetros: ponteiro para vetor de Territorio e quantidade de territórios
// Objetivo: preencher os campos nome, cor e tropas de cada território
void cadastrarTerritorios(Territorio* territorios, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do Territorio %d:\n", i + 1);

        // Leitura do nome do território
        printf("Digite o nome do territorio: ");
        scanf(" %[^\n]", territorios[i].nome); 

        // Leitura da cor do exército
        printf("Digite a cor do exercito: ");
        scanf(" %s", territorios[i].cor);

        // Garantir que cada território tenha pelo menos 1 tropa
        do {
            printf("Digite a quantidade de tropas: ");
            scanf("%d", &territorios[i].tropas);
            if (territorios[i].tropas < 1) {
                printf("Quantidade invalida! Cada territorio deve ter pelo menos 1 tropa.\n");
            }
        } while (territorios[i].tropas < 1);
    }
}

// ==============================
// Função para exibir territórios
// ==============================
// Parâmetros: ponteiro para vetor de Territorio e quantidade
// Objetivo: listar os dados de todos os territórios cadastrados
void exibirTerritorios(Territorio* territorios, int n) {
    printf("\n===== Dados dos Territorios =====\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exercito: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
    }
}

// ==============================
// Função de ataque entre territórios
// ==============================
// Parâmetros: ponteiros para atacante e defensor
// Objetivo: simular batalha com dados aleatórios
// - se atacante vencer, defensor perde 1 tropa por rodada
// - se defensor perder todas, muda de cor e mensagem de derrota é exibida
// - se atacante perder, perde 1 tropa
// - se empate, nenhuma tropa é perdida
void atacar(Territorio* atacante, Territorio* defensor) {

    // Verificação se atacante tem tropas
    if (atacante->tropas <= 0) {
        printf("\nO territorio %s nao tem tropas para atacar!\n", atacante->nome);
        return;
    }

    // Verificação se defensor tem tropas
    if (defensor->tropas <= 0) {
        printf("\nO territorio %s nao possui tropas para defender!\n", defensor->nome);
        return;
    }

    // Geração dos números aleatórios simulando dados (1 a 6)
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    // Exibição do resultado da rodada
    printf("\nRolando os dados!\n");
    printf("%s (Atacante) tirou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (Defensor) tirou: %d\n", defensor->nome, dadoDefensor);

    // ==============================
    // Caso atacante vença a rodada
    // ==============================
    if (dadoAtacante > dadoDefensor) {
        defensor->tropas--;  // debita 1 tropa do defensor
        printf("\n%s Venceu a rodada! %s perdeu 1 tropa. Tropas restantes: %d\n",
               atacante->nome, defensor->nome, defensor->tropas);

        // Se defensor zerar tropas, muda de cor e exibe mensagem
        if (defensor->tropas <= 0) {
            defensor->tropas = 0;
            strcpy(defensor->cor, atacante->cor); // Transferência de domínio
            printf("\n%s Conquistou o territorio %s!\n", atacante->nome, defensor->nome);
            printf("%s VOCE PERDEU TODAS AS SUAS TROPAS PERDEDOR!\n", defensor->nome);
        }

    // ==============================
    // Caso defensor vença a rodada
    // ==============================
    } else if (dadoAtacante < dadoDefensor) {
        atacante->tropas--;  // debita 1 tropa do atacante
        if (atacante->tropas < 0) atacante->tropas = 0;
        printf("\n%s Fracassou na rodada e perdeu 1 tropa! Tropas restantes: %d\n",
               atacante->nome, atacante->tropas);

        if (atacante->tropas <= 0) {
            atacante->tropas = 0;
            printf("%s VOCÊ PERDEU TODAS AS SUAS TROPAS PERDEDOR!\n", atacante->nome);
        }

    // ==============================
    // Caso empate
    // ==============================
    } else {
        printf("\nEMPATE! Nenhuma tropa foi perdida nesta rodada.\n");
    }
}

// ==============================
// Função para liberar memória alocada dinamicamente
// ==============================
void liberarMemoria(Territorio* territorios) {
    free(territorios);
}

// ==============================
// Função principal 'main'
// ==============================
int main() {
    srand(time(NULL)); // inicializa gerador aleatório

    int n;
    printf("Digite o numero de territorios a cadastrar: ");
    scanf("%d", &n);

    // Validação mínima de territórios
    if (n <= 1) {
        printf("Eh necessario ter pelo menos 2 territorios para jogar!\n");
        return 1;
    }

    // ==============================
    // Alocação dinâmica do vetor de territórios
    // ==============================
    Territorio* territorios = (Territorio*) calloc(n, sizeof(Territorio));
    if (!territorios) {
        printf("Erro de memoria!\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(territorios, n);

    // Exibição inicial dos dados
    exibirTerritorios(territorios, n);

    // ==============================
    // Loop principal do menu de ataque
    // ==============================
    int opcao = 1;
    while (opcao != 0) {
        printf("\n===== MENU DE ATAQUE =====\n");
        printf("0 - Sair\n");
        printf("1 - Atacar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int a, d;

            // Escolha do atacante
            do {
                printf("Escolha o Territorio que vai Atacar (1-%d): ", n);
                scanf("%d", &a);
            } while (a < 1 || a > n);

            // Escolha do defensor
            do {
                printf("Escolha o Territorio que vai Defender (1-%d, diferente de %d): ", n, a);
                scanf("%d", &d);
            } while (d < 1 || d > n || d == a);

            // Executa 1 rodada de ataque
            atacar(&territorios[a - 1], &territorios[d - 1]);

            // Atualiza a exibição dos dados
            exibirTerritorios(territorios, n);
        }
    }

    // Liberação da memória alocada
    liberarMemoria(territorios);
    printf("\nPrograma encerrado. Memoria liberada.\n");
    return 0;
}
