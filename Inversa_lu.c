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
    int posicion[matriz.m];
    desc_LU(matriz.A, matriz.m, posicion);
    inversa=inversa_LU(matriz.A, matriz.m, posicion);
    resultado=multiplicacion(inversa,matriz2.A,matriz.m,matriz.m,matriz.m,matriz.m);

    printf("La inversa es: \n");
    imprime_matrizc(inversa,matriz.m, matriz.n);
    printf("\n");
    printf("Inversa por matriz original: \n");
    imprime_matrizc(resultado,matriz.m,matriz.n);

    liberar_matriz(resultado,matriz.m);
    liberar_matriz(matriz2.A, matriz2.m);
    liberar_matriz(matriz.A,matriz.m);
    liberar_matriz(inversa, matriz.m);
    return 0;
}
