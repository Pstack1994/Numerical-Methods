#include <stdio.h>
#include <stdlib.h>
#include "../../matrix.h"
#include "../../operacion_matriz.h"
#include "../../solve.h"
#include "../../EcuacionesL_Metodos.h"
#include"../../Eigen.h"


int main(int argc, char *argv[]){
    Matriz matriz;
    //double **cholesky;
   // eigen2 solucion;

    matriz=lee_matriz1(argc, argv);
    //int posicion[matriz.m];
    //solucion=deflacion_potenciainv(matriz.A, matriz.m, matriz.n, 1e-9,2);
    //desc_LU(matriz.A, matriz.m, posicion);
    //imprime_resultado(solucion.eigenvector, matriz.m);
   // imprime_matrizc(solucion.eigenvector, matriz.m, 2);

    //liberar_matriz(solucion.eigenvector,matriz.m);
    liberar_matriz(matriz.A,matriz.m);
    //free(solucion.eigenvalor);

    return 0;
}
