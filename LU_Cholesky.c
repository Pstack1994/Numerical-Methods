#include <stdio.h>
#include "matrix.c"
#include "solve.c"
#include "operacion_matriz.c"
#include "EcuacionesL_Metodos.c"

void solv_Mod_Cholesky(double **cholesky, int m, double *resultado);

int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz(argc, argv);//se necesitan pasar la matriz y el vector de la aumentado
    double **cholesky;
    double resultado[matriz.m];
    cholesky=Mod_Cholesky(matriz.A, matriz.m, matriz.n);
    solv_Mod_Cholesky(cholesky, matriz.m, resultado);
    imprime_matrizc(cholesky,matriz.m, matriz.n);
    imprime_resultado(resultado, matriz.m);
    liberar_matriz(cholesky, matriz.m);
    return 0;
}

void solv_Mod_Cholesky(double **cholesky, int m, double *resultado){

 for(int i=1; i<m; i++){
        for(int j=0;j<i;j++){
            cholesky[i][j]*=cholesky[j][j];
        }
    }
    solv_diagonalinf(cholesky,m,resultado);

    for(int i=0;i<m;i++){
        cholesky[i][i]=1;
        cholesky[i][m]=resultado[i];
    }

   solv_diagonalsup(cholesky,m,resultado);

}
