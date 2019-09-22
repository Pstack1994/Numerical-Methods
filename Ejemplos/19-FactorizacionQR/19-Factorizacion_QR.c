#include<stdio.h>
#include <stdlib.h>
#include "../../matrix.h"
#include "../../Eigen.h"
#include "../../operacion_matriz.h"
#include"../../EcuacionesL_Metodos.h"
#include "../../solve.h"


int main(int argc, char *argv[]){
    Matriz matriz;
    eigen2 solucion;

    matriz=lee_matriz1(argc,argv);
    double **r=crea_matriz2(matriz.m,matriz.n);

    solucion=metodo_QR(matriz.A,r,matriz.m,matriz.n, 2.2245e-9);
    imprime_matrizc(solucion.eigenvector,matriz.m,matriz.n);
    printf("\nLos eigenvalores son: ");
    imprime_resultado(solucion.eigenvalor, matriz.m);

    liberar_matriz(solucion.eigenvector, matriz.m);
    liberar_matriz(matriz.A, matriz.m);
    liberar_matriz(r, matriz.m);
    free(solucion.eigenvalor);
    return 0;
}
