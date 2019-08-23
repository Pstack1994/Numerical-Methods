#include<stdio.h>
#include"matrix.c"
#include "operacion_matriz.c"
#include"solve.c"
#include "EcuacionesL_Metodos.c"

int main(int argc, char* argv[]){
    Matriz matriz;
    double det;
    matriz=lee_matriz(argc, argv);
    double resultado[matriz.m];
    solv_diagonalinf(matriz.A,matriz.m,resultado);
    imprime_resultado(resultado, matriz.m);
    printf("\n");
    printf("El determinante es: ");
    det=det_diagonal(matriz.A,matriz.m);
    printf("%lf",det);
    liberar_matriz(matriz.A,matriz.m);
    return 0;
}
