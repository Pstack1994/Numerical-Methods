#include <stdio.h>
#include <math.h>
#include "matrix.c"
#include "tarea5.c"



int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz(argc, argv);
    double *resultado, tole=.00000000001;

    resultado=Gauss_Seidel(matriz.A, matriz.m, tole);
    liberar_matriz(matriz.A,matriz.m);
    free(resultado);

    return 0;
}
