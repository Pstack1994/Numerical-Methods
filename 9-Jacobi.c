#include <stdio.h>
#include <math.h>
#include "matrix.c"
#include "tarea5.c"


int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz(argc, argv);
    double *resultado, tole=1e-9;

    resultado=Jacobi(matriz.A, matriz.m, tole);

    imprime_resultado(resultado, matriz.m);
    printf("%d", matriz.m);
    printf("\n %d", matriz.n);
    liberar_matriz(matriz.A,matriz.m);
    free(resultado);
    return 0;
}
