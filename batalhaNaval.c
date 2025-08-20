#include <stdio.h>

#define TAM 10        // Tamanho do tabuleiro (10x10)
#define NAVIO 3       // Valor que representa o navio no tabuleiro
#define AGUA 0        // Valor que representa a água
#define TAM_NAVIO 3   // Comprimento fixo dos navios

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se é possível posicionar um navio
int podePosicionar(int tabuleiro[TAM][TAM], int linha, int coluna, char orientacao) {
    if (orientacao == 'H') { // Horizontal
        if (coluna + TAM_NAVIO > TAM) return 0; // Ultrapassa limite
        for (int j = 0; j < TAM_NAVIO; j++) {
            if (tabuleiro[linha][coluna + j] == NAVIO) return 0; // Já tem navio
        }
    } else if (orientacao == 'V') { // Vertical
        if (linha + TAM_NAVIO > TAM) return 0; // Ultrapassa limite
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] == NAVIO) return 0; // Já tem navio
        }
    }
    return 1;
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, char orientacao) {
    if (podePosicionar(tabuleiro, linha, coluna, orientacao)) {
        if (orientacao == 'H') {
            for (int j = 0; j < TAM_NAVIO; j++) {
                tabuleiro[linha][coluna + j] = NAVIO;
            }
        } else if (orientacao == 'V') {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linha + i][coluna] = NAVIO;
            }
        }
    } else {
        printf("ERRO: Não foi possível posicionar o navio nas coordenadas (%d,%d)\n", linha, coluna);
    }
}

int main() {
    int tabuleiro[TAM][TAM];

    // Inicializa tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Coordenadas dos navios (definidas no código)
    int linhaNavio1 = 2, colunaNavio1 = 3; // Navio horizontal
    int linhaNavio2 = 5, colunaNavio2 = 7; // Navio vertical

    // Posiciona navios
    posicionarNavio(tabuleiro, linhaNavio1, colunaNavio1, 'H');
    posicionarNavio(tabuleiro, linhaNavio2, colunaNavio2, 'V');

    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}
