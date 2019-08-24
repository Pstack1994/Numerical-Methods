#include <stdio.h>
#include "matrix.c"
#include "solve.c"
#include "operacion_matriz.c"
#include "EcuacionesL_Metodos.c"




int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz(argc, argv);
    double resultado[matriz.m];
    double respaldo[matriz.m];
    desc_LU(matriz.A,matriz.m);
    solv_LU(matriz.A,matriz.m,resultado);
    imprime_resultado(resultado,matriz.m);
    liberar_matriz(matriz.A,matriz.m);
    return 0;
}
