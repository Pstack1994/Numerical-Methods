#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../../matrix.h"
#include"../../Eigen.h"
#include "../../operacion_matriz.h"
#include "../../solve.h"
#include "../../EcuacionesL_Metodos.h"

int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz1(argc, argv);
    eigen solucion;
    solucion=potencia_inversa(matriz.A, matriz.m, matriz.n, 1e-8);

    printf("Eigen valor: %.20lf", solucion.eigenvalor);
    printf("\n");
    printf("Eigen vector: ");
    for(int i=0; i<matriz.m;i++){
        printf("%lf, ", solucion.eigenvector[i]);
    }

    liberar_matriz(matriz.A,matriz.m);
    free(solucion.eigenvector);
    return 0;
}
