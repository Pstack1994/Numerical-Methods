#include <stdio.h>
#include "matrix.c"
#include "solve.c"
#include "operacion_matriz.c"
#include "EcuacionesL_Metodos.c"


int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz1(argc, argv);
    double **inversa;
    desc_LU(matriz.A, matriz.m);
    inversa=inversa_LU(matriz.A, matriz.m);
    liberar_matriz(matriz.A,matriz.m);
    liberar_matriz(inversa, matriz.m);
    return 0;
}
