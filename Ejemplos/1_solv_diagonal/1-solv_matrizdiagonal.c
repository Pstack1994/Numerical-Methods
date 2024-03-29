#include<stdio.h>
#include"../../matrix.h"
#include "../../operacion_matriz.h"
#include"../../solve.h"


int main(int argc, char* argv[]){
    Matriz matriz;
    double det;
    matriz=lee_matriz(argc, argv);
    double resultado[matriz.m];
    solv_diagonal(matriz.A,matriz.m,resultado);
    imprime_resultado(resultado, matriz.m);
    printf("\n");
    printf("El determinante es: ");
    det=det_diagonal(matriz.A,matriz.m);
    printf("%lf",det);
    liberar_matriz(matriz.A,matriz.m);
    return 0;
}
