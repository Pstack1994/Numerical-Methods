#include <stdio.h>
#include "matrix.c"
#include "solve.c"
#include "operacion_matriz.c"
#include "EcuacionesL_Metodos.c"


int main(int argc, char* argv[]){
    Matriz matriz, matriz2;
    matriz=lee_matriz1(argc, argv);
    matriz2=lee_matriz1(argc, argv);
    double **resultado;
    double **inversa;
    desc_LU(matriz.A, matriz.m);
    inversa=inversa_LU(matriz.A, matriz.m);
    resultado=multiplicacion(inversa,matriz2.A,matriz.m,matriz.m,matriz.m,matriz.m);
    printf("\n");
    imprime_matrizc(resultado,matriz.m,matriz.m);
    liberar_matriz(matriz.A,matriz.m);
    liberar_matriz(inversa, matriz.m);
    return 0;
}
