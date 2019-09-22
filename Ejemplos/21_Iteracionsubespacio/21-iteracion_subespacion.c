#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "../../matrix.h"
#include "../../operacion_matriz.h"
#include "../../solve.h"
#include "../../EcuacionesL_Metodos.h"
#include"../../Eigen.h"


int main(int argc, char *argv[]){
    Matriz matriz;
    matriz=lee_matriz1(argc, argv);
    eigen2 solucion;

    solucion=iteracion_subespacio(matriz.A,matriz.m,matriz.n,15,1e-9);
    printf("Los eigenvalores son: \n");
    imprime_resultado(solucion.eigenvalor,15);
    printf("\nLos eigenvectores son: \n");
    imprime_matrizc(solucion.eigenvector, matriz.m,15);

    liberar_matriz(matriz.A,matriz.m);
    liberar_matriz(solucion.eigenvector,matriz.m);
    free(solucion.eigenvalor);
    return 0;
}
