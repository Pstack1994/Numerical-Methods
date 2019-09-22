#include<stdio.h>
#include<stdlib.h>
#include"../../matrix.h"
#include "../../operacion_matriz.h"
#include"../../solve.h"
#include "../../EcuacionesL_Metodos.h"


int main(int argc, char* argv[]){
    Matriz matriz;
    Vector b;
    matriz=lee_matriz1(argc, argv);
    b=lee_vector(argv[2]);

    double resultado[matriz.m];
    double det;

    det=G_sinpivoteo(matriz.A,b.v, matriz.m, matriz.n,resultado);
    imprime_resultado(resultado,matriz.m);
    printf("\n");
    printf("El determinante es:");
    printf("%lf",det);
    liberar_matriz(matriz.A,matriz.m);
    free(b.v);
    return 0;
}
