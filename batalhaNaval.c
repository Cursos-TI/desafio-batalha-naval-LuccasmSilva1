#include <stdio.h>

#define TAM 10       
#define AGUA 0       
#define NAVIO 3      
#define HABILIDADE 5 
#define TAM_HAB 5    
#define CENTRO 2     


void exibirTabuleiro(int mapa[TAM][TAM]) {
    printf("\n=== MAPA DO JOGO ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (mapa[i][j] == AGUA)
                printf("0 "); // água
            else if (mapa[i][j] == NAVIO)
                printf("3 "); // navio
            else if (mapa[i][j] == HABILIDADE)
                printf("5 "); // área da habilidade
        }
        printf("\n");
    }
    printf("\nLegenda: 0 = Água | 3 = Navio | 5 = Área de Habilidade\n\n");
}

void aplicarHabilidade(int mapa[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int origem_l, int origem_c) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (habilidade[i][j] == 1) { // Se a célula faz parte da área da habilidade
                int lin = origem_l - CENTRO + i;
                int col = origem_c - CENTRO + j;
                // Verifica se está dentro do tabuleiro
                if (lin >= 0 && lin < TAM && col >= 0 && col < TAM) {
                    if (mapa[lin][col] == AGUA) // não sobrescreve navios
                        mapa[lin][col] = HABILIDADE;
                }
            }
        }
    }
}

void criarCone(int cone[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i >= j - CENTRO && i >= CENTRO - j) // lógica do cone expandindo para baixo
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

void criarCruz(int cruz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == CENTRO || j == CENTRO) // linha e coluna do centro
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}


void criarOctaedro(int octa[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            
            int dist = (i - CENTRO >= 0 ? i - CENTRO : CENTRO - i)
                     + (j - CENTRO >= 0 ? j - CENTRO : CENTRO - j);
            if (dist <= CENTRO)
                octa[i][j] = 1;
            else
                octa[i][j] = 0;
        }
    }
}

int main() {
    int mapa[TAM][TAM];

    //  tabuleiro 
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            mapa[i][j] = AGUA;

    //  navios 
    for (int j = 2; j < 5; j++) mapa[2][j] = NAVIO; // horizontal
    for (int i = 5; i < 8; i++) mapa[i][7] = NAVIO; // vertical

    //  habilidades 
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octa[TAM_HAB][TAM_HAB];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octa);

    //  origens no tabuleiro 
    int origem_cone_l = 1, origem_cone_c = 4;
    int origem_cruz_l = 6, origem_cruz_c = 3;
    int origem_octa_l = 7, origem_octa_c = 7;

    //   habilidades no tabuleiro 
    aplicarHabilidade(mapa, cone, origem_cone_l, origem_cone_c);
    aplicarHabilidade(mapa, cruz, origem_cruz_l, origem_cruz_c);
    aplicarHabilidade(mapa, octa, origem_octa_l, origem_octa_c);

    //  resultado 
    exibirTabuleiro(mapa);

    return 0;
}
