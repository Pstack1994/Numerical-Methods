#include<stdio.h>
#include"matrix.c"
#include "operacion_matriz.c"
#include"solve.c"
#include "EcuacionesL_Metodos.c"


int main(int argc, char* argv[]){
    double ** matriz=lee_matriz(argc, argv);
    int m=4;
    int n=4;
    double resultado[m];
    double det;

    det=GJ_sinpivoteo(matriz, m, n,resultado);
    imprime_resultado(resultado,m);
    printf("\n");
    printf("%lf",det);
    liberar_matriz(matriz,m);
    return 0;
}
