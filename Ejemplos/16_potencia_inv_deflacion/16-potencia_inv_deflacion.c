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
    Matriz matriz;
    eigen2 solucion;
    matriz=lee_matriz1(argc, argv);
    solucion=deflacion_potenciainv(matriz.A, matriz.m,matriz.n,1e-8,matriz.m);
    printf("Los eigenvalores son: \n");
    imprime_resultado(solucion.eigenvalor,matriz.m);
    printf("Los eigenvectores son: ");
        printf("\n");
        for(int i=0; i<matriz.m; i++){
            for(int j=0; j<matriz.m; j++){
                printf("%lf ", solucion.eigenvector[i][j]);
            }
            printf("\n");
        }

    liberar_matriz(matriz.A,matriz.m);
    liberar_matriz(solucion.eigenvector,matriz.m);
    free(solucion.eigenvalor);
    return 0;
}
