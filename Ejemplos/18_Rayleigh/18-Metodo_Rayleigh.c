#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<time.h>
#include "../../matrix.h"
#include "../../Eigen.h"
#include "../../solve.h"
#include "../../operacion_matriz.h"
#include"../../EcuacionesL_Metodos.h"



int main(int argc, char* argv[]){
    Matriz matriz;
    Vector xa;
    eigen solucion;
    matriz=lee_matriz1(argc, argv);
    xa=lee_vector(argv[2]);

   solucion=Metodo_Rayleigh(matriz.A, xa.v,matriz.m,matriz.n,1e-9);
   printf("Eigenvalor: %lf\n", solucion.eigenvalor);
    printf("Eigenvector: \n");
    imprime_resultado(solucion.eigenvector, matriz.m);


    liberar_matriz(matriz.A, matriz.m);
    free(solucion.eigenvector);

    return 0;
}
