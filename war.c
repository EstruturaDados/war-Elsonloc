#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==============================
// Definição da struct Territorio
// ==============================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ==============================
// Função para cadastrar territórios
// ==============================
void cadastrarTerritorios(Territorio* territorios, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do Territorio %d:\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf(" %[^\n]", territorios[i].nome); 

        printf("Digite a cor do exercito: ");
        scanf(" %s", territorios[i].cor);

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
// Função de ataque/defesa entre territórios
// ==============================
void atacar(Territorio* atacante, Territorio* defensor) {

    if (atacante->tropas <= 0) {
        printf("\nO territorio %s nao tem tropas para atacar!\n", atacante->nome);
        return;
    }

    if (defensor->tropas <= 0) {
        printf("\nO territorio %s nao possui tropas para defender!\n", defensor->nome);
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nRolando os dados!\n");
    printf("%s (Atacante) tirou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (Defensor) tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        defensor->tropas--;
        printf("\n%s Venceu a rodada! %s perdeu 1 tropa. Tropas restantes: %d\n",
               atacante->nome, defensor->nome, defensor->tropas);

        if (defensor->tropas <= 0) {
            defensor->tropas = 0;
            strcpy(defensor->cor, atacante->cor);
            printf("\n%s Conquistou o territorio %s!\n", atacante->nome, defensor->nome);
            printf("%s VOCE PERDEU TODAS AS SUAS TROPAS PERDEDOR!\n", defensor->nome);
        }

    } else if (dadoAtacante < dadoDefensor) {
        atacante->tropas--;
        if (atacante->tropas < 0) atacante->tropas = 0;
        printf("\n%s Defendeu com sucesso! %s perdeu 1 tropa. Tropas restantes: %d\n",
               defensor->nome, atacante->nome, atacante->tropas);

        if (atacante->tropas <= 0) {
            atacante->tropas = 0;
            printf("%s VOCE PERDEU TODAS AS SUAS TROPAS PERDEDOR!\n", atacante->nome);
        }

    } else {
        printf("\nEMPATE! Nenhuma tropa foi perdida nesta rodada.\n");
    }

    // Mensagem motivacional após cada rodada
    printf("\nVOCE DEVE CONTINUAR ATE VENCER\n");
}

// ==============================
// Função para liberar memória
// ==============================
void liberarMemoria(Territorio* territorios) {
    free(territorios);
}

// ==============================
// Função principal 'main'
// ==============================
int main() {
    srand(time(NULL));

    int n;
    printf("Digite o numero de territorios a cadastrar: ");
    scanf("%d", &n);

    if (n <= 1) {
        printf("Eh necessario ter pelo menos 2 territorios para jogar!\n");
        return 1;
    }

    Territorio* territorios = (Territorio*) calloc(n, sizeof(Territorio));
    if (!territorios) {
        printf("Erro de memoria!\n");
        return 1;
    }

    cadastrarTerritorios(territorios, n);
    exibirTerritorios(territorios, n);

    // ==============================
    // Loop principal do menu
    // ==============================
    int opcao = 1;
    while (1) {
        printf("\n===== MENU =====\n");
        printf("0 - Sair\n");
        printf("1 - Atacar\n");
        printf("2 - Defender\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 0) {
            // Confirmação ao sair
            int confirma;
            do {
                printf("\nTem certeza que deseja sair? 1 - Sim / 0 - Nao: ");
                scanf("%d", &confirma);
            } while (confirma != 0 && confirma != 1);

            if (confirma == 1) {
                printf("\nVoce decidiu sair do jogo.\n");
                break;
            } else {
                continue; // Volta ao menu sem sair
            }
        }

        int a, d;
        // Escolha do atacante/defensor
        do {
            printf("Escolha o Territorio (1-%d) que vai atuar: ", n);
            scanf("%d", &a);
        } while (a < 1 || a > n);

        do {
            printf("Escolha o Territorio (1-%d) alvo/diferente de %d: ", n, a);
            scanf("%d", &d);
        } while (d < 1 || d > n || d == a);

        // Executa ataque/defesa (mesma função)
        atacar(&territorios[a - 1], &territorios[d - 1]);

        // Exibe dados atualizados
        exibirTerritorios(territorios, n);
    }

    liberarMemoria(territorios);
    printf("\nPrograma encerrado. Memoria liberada.\n");
    return 0;
}