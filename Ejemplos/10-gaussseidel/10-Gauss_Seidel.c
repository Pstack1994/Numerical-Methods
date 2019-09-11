#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../matrix.h"
#include "../../tarea5.h"



int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz(argc, argv);
    double *resultado, tole=.00000000001;

    resultado=Gauss_Seidel(matriz.A, matriz.m, tole);
    liberar_matriz(matriz.A,matriz.m);
    free(resultado);

    return 0;
}
