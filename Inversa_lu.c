#include <stdio.h>
#include "matrix.c"
#include "solve.c"
#include "operacion_matriz.c"
#include "EcuacionesL_Metodos.c"

int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz(argc, argv);
    double resultado[matriz.m];

   desc_LU(matriz.A, matriz.m);

    double identidad[matriz.m][matriz.m];
    for(int i=0;i<matriz.m;i++){
        for(int j=0; j<matriz.m; j++){
            if(i==j){
                identidad[i][j]=1;
            }
            else{
                identidad[i][j]=0;
            }
        }
    }

    double respaldo_diag[matriz.m];

    for(int i=0;i<matriz.m;i++){
    respaldo_diag[i]=matriz.A[i][i];//crear respaldo para no perder los valores de la diagonal
    matriz.A[i][i]=1;
    }

    for(int i=0;i<matriz.m;i++){

        for(int j=0; j<matriz.m; j++){
            matriz.A[j][matriz.m]=identidad[j][i];
        }
        solv_diagonalinf(matriz.A,matriz.m,resultado);
        for(int k=0; k<matriz.m;k++){
            identidad[k][i]= resultado[k];
        }
    }


    for(int i=0; i<matriz.m;i++){
        matriz.A[i][i]=respaldo_diag[i];
    }

//////////////////////////////////// resolver superior /////////////////////

    for(int i=0;i<matriz.m;i++){
        for(int j=0; j<matriz.m; j++){
            matriz.A[j][matriz.m]=identidad[j][i];
        }
        solv_diagonalsup(matriz.A,matriz.m,resultado);

        for(int k=0; k<matriz.m;k++){
            identidad[k][i]= resultado[k];
        }
    }

    for(int i=0; i<matriz.m;i++){
        for(int j=0; j<matriz.m; j++){
            printf("%lf ", identidad[i][j]);
        }
        printf("\n");
    }

    liberar_matriz(matriz.A,matriz.m);
    return 0;
}
