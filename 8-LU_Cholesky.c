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
    solv_Mod_Cholesky(cholesky, matriz.m, resultado);
    imprime_matrizc(cholesky,matriz.m, matriz.n);
    imprime_resultado(resultado, matriz.m);
    liberar_matriz(cholesky, matriz.m);
    return 0;
}
