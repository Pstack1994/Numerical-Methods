#include <stdio.h>
#include "matrix.c"
#include "solve.c"
#include "operacion_matriz.c"
#include "EcuacionesL_Metodos.c"

int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz(argc, argv);//se necesitan pasar la matriz y el vector de la aumentado
    double **cholesky;
    double resultado[matriz.m];
    cholesky=Mod_Cholesky(matriz.A, matriz.m, matriz.n);
    imprime_matrizc(cholesky,matriz.m, matriz.n);

    for(int i=1; i< matriz.m;i++){
        for(int j=0;j<i;j++){
            cholesky[i][j]*=cholesky[j][j];
        }
    }
    solv_diagonalinf(cholesky,matriz.m,resultado);

    for(int i=0;i<matriz.m;i++){
        cholesky[i][i]=1;
        cholesky[i][matriz.m]=resultado[i];
    }

    solv_diagonalsup(cholesky,matriz.m,resultado);
    imprime_resultado(resultado, matriz.m);
    liberar_matriz(matriz.A,matriz.m);
    return 0;
}
