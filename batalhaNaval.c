#include <stdio.h>



int main() {
    int i, j;
    int agua = 0;
    int navio = 3;
    int mapa[10][10];
    int tam_navio = 3;

    // tabuleiro 
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            mapa[i][j] = agua;
        }
    }

    //  Coordenadas
    int linha_h = 2, coluna_h = 4; // horizontal
    int linha_v = 5, coluna_v = 7; // vertical

    // limites 
    if (coluna_h + tam_navio > 10) {
        printf("Fora dos limites!\n");
        return 1;
    }

    if (linha_v + tam_navio > 10) {
        printf("Fora dos limites!\n");
        return 1;
    }
    //posicionamento
    for(j = coluna_h; j < coluna_h + tam_navio; j++ ){
        mapa[linha_h][j]=navio;
    }
    for(i = linha_v; i< linha_v + tam_navio ; i++){
        mapa[i][coluna_v]=navio;
    }
    //jogo
    printf("\nMapa\n");
    for(i = 0; i < 10 ; i++ ){
        for(j = 0; j < 10 ; j++){
            if(mapa[i][j] == agua)
                printf("1 ");
            else if (mapa[i][j]==navio)
                printf("3 ");        
        }
    printf("\n");    
    }

    return 0;
}
