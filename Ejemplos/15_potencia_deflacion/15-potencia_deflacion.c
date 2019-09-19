
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <math.h>
#include "../../matrix.h"
#include "../../Eigen.h"
#include "../../operacion_matriz.h"
#include "../../solve.h"
#include "../../EcuacionesL_Metodos.h"


int main(int argc, char* argv[]){
    Matriz matriz;
    eigen2 solucion;
    matriz=lee_matriz1(argc, argv);
    solucion=potencia_deflacion(matriz.A, matriz.m,matriz.n,1e-8);
    printf("Los eigenvalores son: \n");
    imprime_resultado(solucion.eigenvalor,matriz.m);
    printf("Los eigenvectores son:\n");
    imprime_matrizc(solucion.eigenvector, matriz.m, matriz.m);

    liberar_matriz(matriz.A,matriz.m);
    liberar_matriz(solucion.eigenvector,matriz.m);
    free(solucion.eigenvalor);
    return 0;
}
