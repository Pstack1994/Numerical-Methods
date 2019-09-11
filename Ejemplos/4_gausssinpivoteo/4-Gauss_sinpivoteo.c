#include<stdio.h>
#include"../../matrix.h"
#include "../../operacion_matriz.h"
#include"../../solve.h"
#include "../../EcuacionesL_Metodos.h"


int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz(argc, argv);
    double resultado[matriz.m];
    double det;

    det=G_sinpivoteo(matriz.A, matriz.m, matriz.n,resultado);
    imprime_resultado(resultado,matriz.m);
    printf("\n");
    printf("El determinante es:");
    printf("%lf",det);
    liberar_matriz(matriz.A,matriz.m);
    return 0;
}
