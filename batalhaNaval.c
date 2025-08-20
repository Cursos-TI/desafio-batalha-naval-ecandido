#include <stdio.h>

#define TAM 10        // Tamanho do tabuleiro (10x10)
#define NAVIO 3       // Valor que representa o navio no tabuleiro
#define AGUA 0        // Valor que representa água
#define TAM_NAVIO 3   // Comprimento fixo dos navios

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se pode posicionar navio
int podePosicionar(int tabuleiro[TAM][TAM], int linha, int coluna, char orientacao) {
    if (orientacao == 'H') { // Horizontal
        if (coluna + TAM_NAVIO > TAM) return 0;
        for (int j = 0; j < TAM_NAVIO; j++)
            if (tabuleiro[linha][coluna + j] == NAVIO) return 0;
    } 
    else if (orientacao == 'V') { // Vertical
        if (linha + TAM_NAVIO > TAM) return 0;
        for (int i = 0; i < TAM_NAVIO; i++)
            if (tabuleiro[linha + i][coluna] == NAVIO) return 0;
    } 
    else if (orientacao == 'D1') { // Diagonal ↘ (linha++ / coluna++)
        if (linha + TAM_NAVIO > TAM || coluna + TAM_NAVIO > TAM) return 0;
        for (int i = 0; i < TAM_NAVIO; i++)
            if (tabuleiro[linha + i][coluna + i] == NAVIO) return 0;
    } 
    else if (orientacao == 'D2') { // Diagonal ↙ (linha++ / coluna--)
        if (linha + TAM_NAVIO > TAM || coluna - (TAM_NAVIO - 1) < 0) return 0;
        for (int i = 0; i < TAM_NAVIO; i++)
            if (tabuleiro[linha + i][coluna - i] == NAVIO) return 0;
    }
    return 1;
}

// Função para posicionar navio
void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, char orientacao) {
    if (podePosicionar(tabuleiro, linha, coluna, orientacao)) {
        if (orientacao == 'H') {
            for (int j = 0; j < TAM_NAVIO; j++)
                tabuleiro[linha][coluna + j] = NAVIO;
        } 
        else if (orientacao == 'V') {
            for (int i = 0; i < TAM_NAVIO; i++)
                tabuleiro[linha + i][coluna] = NAVIO;
        } 
        else if (orientacao == 'D1') {
            for (int i = 0; i < TAM_NAVIO; i++)
                tabuleiro[linha + i][coluna + i] = NAVIO;
        } 
        else if (orientacao == 'D2') {
            for (int i = 0; i < TAM_NAVIO; i++)
                tabuleiro[linha + i][coluna - i] = NAVIO;
        }
    } else {
        printf("ERRO: Não foi possível posicionar o navio (%c) em (%d,%d)\n", orientacao, linha, coluna);
    }
}

int main() {
    int tabuleiro[TAM][TAM];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Navios definidos no código (2 normais e 2 diagonais)
    // Navio 1 - horizontal
    posicionarNavio(tabuleiro, 2, 2, 'H');
    // Navio 2 - vertical
    posicionarNavio(tabuleiro, 5, 7, 'V');
    // Navio 3 - diagonal
    posicionarNavio(tabuleiro, 0, 0, 'D1');
    // Navio 4 - diagonal
    posicionarNavio(tabuleiro, 0, 9, 'D2');

    // Exibe tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}
