#include <stdio.h>

#define TAM 10        // Tamanho do tabuleiro (10x10)
#define NAVIO 3       // Valor que representa o navio no tabuleiro
#define AGUA 0        // Valor que representa água
#define TAM_NAVIO 3   // Comprimento fixo dos navios
#define HABILIDADE 5  // Valor que representa a área de efeito da habilidade
#define TAM_HAB 5     // Tamanho fixo das matrizes de habilidade (5x5)

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
    else if (orientacao == 'D1') { // Diagonal (linha++ / coluna++)
        if (linha + TAM_NAVIO > TAM || coluna + TAM_NAVIO > TAM) return 0;
        for (int i = 0; i < TAM_NAVIO; i++)
            if (tabuleiro[linha + i][coluna + i] == NAVIO) return 0;
    } 
    else if (orientacao == 'D2') { // Diagonal (linha++ / coluna--)
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

// Gera matriz de cone (5x5) com origem no topo
void gerarCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB/2 - i) && j <= (TAM_HAB/2 + i))
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera matriz de cruz (5x5) com origem no centro
void gerarCruz(int matriz[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == centro || j == centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera matriz de octaedro (losango) (5x5)
void gerarOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica habilidade ao tabuleiro no ponto de origem
void aplicarHabilidade(int tabuleiro[TAM][TAM], int hab[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int offset = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (hab[i][j] == 1) {
                int linhaTab = origemLinha - offset + i;
                int colunaTab = origemColuna - offset + j;
                if (linhaTab >= 0 && linhaTab < TAM && colunaTab >= 0 && colunaTab < TAM) {
                    if (tabuleiro[linhaTab][colunaTab] == AGUA) {
                        tabuleiro[linhaTab][colunaTab] = HABILIDADE;
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Navios definidos no código (2 normais e 2 diagonais)
    posicionarNavio(tabuleiro, 2, 2, 'H');
    posicionarNavio(tabuleiro, 5, 7, 'V');
    posicionarNavio(tabuleiro, 0, 0, 'D1');
    posicionarNavio(tabuleiro, 0, 9, 'D2');

    // Matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    // Gera formas das habilidades
    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // Aplica habilidades em pontos específicos do tabuleiro
    aplicarHabilidade(tabuleiro, cone, 4, 4);
    aplicarHabilidade(tabuleiro, cruz, 7, 2);
    aplicarHabilidade(tabuleiro, octaedro, 6, 6);

    // Exibe tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
