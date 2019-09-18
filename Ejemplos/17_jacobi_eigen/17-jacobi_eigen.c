#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include "../../matrix.h"
#include "../../Eigen.h"
#include "../../solve.h"
#include "../../operacion_matriz.h"
#include"../../EcuacionesL_Metodos.h"


int main(int argc, char* argv[]){
    eigen2 solucion;
    Matriz matriz;
    double tole=1e-9;
    matriz=lee_matriz1(argc, argv);

    solucion=Jacobi_Eigen(matriz.A, tole, matriz.m);
    printf("Los eigenvalores son: ");
    imprime_resultado(solucion.eigenvalor, matriz.m);

    printf("\nLos eigenvectores son: ");
    imprime_matrizc(solucion.eigenvector, matriz.m, matriz.m);

    liberar_matriz(matriz.A, matriz.m);
    liberar_matriz(solucion.eigenvector, matriz.m);
    free(solucion.eigenvalor);

    return 0;
}
