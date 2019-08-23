#include <stdio.h>
#include "matrix.c"
#include "solve.c"
#include "operacion_matriz.c"
#include "EcuacionesL_Metodos.c"

int main(int argc, char* argv[]){

    double ** matriz=lee_matriz(argc, argv);
    int m=3;
    double resultado[m];

    desc_LU(matriz,m);

    double identidad[m][m];
    for(int i=0;i<m;i++){
        for(int j=0; j<m; j++){
            if(i==j){
                identidad[i][j]=1;
            }
            else{
                identidad[i][j]=0;
            }
        }
    }

    double respaldo_diag[m];

    for(int i=0;i<m;i++){
    respaldo_diag[i]=matriz[i][i];//crear respaldo para no perder los valores de la diagonal
    matriz[i][i]=1;
    }

    for(int i=0;i<m;i++){

        for(int j=0; j<m; j++){
            matriz[j][m]=identidad[j][i];
        }
        solv_diagonalinf(matriz,m,resultado);
        for(int k=0; k<m;k++){
            identidad[k][i]= resultado[k];
        }
    }


    for(int i=0; i<m;i++){
        matriz[i][i]=respaldo_diag[i];
    }

//////////////////////////////////// resolver superior /////////////////////

    for(int i=0;i<m;i++){
        for(int j=0; j<m; j++){
            matriz[j][m]=identidad[j][i];
        }
        solv_diagonalsup(matriz,m,resultado);

        for(int k=0; k<m;k++){
            identidad[k][i]= resultado[k];
        }
    }

    for(int i=0; i<m;i++){
        for(int j=0; j<m; j++){
            printf("%lf ", identidad[i][j]);
        }
        printf("\n");
    }

    liberar_matriz(matriz,m);
    return 0;
}
