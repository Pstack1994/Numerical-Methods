#include <stdio.h>
#include "matrix.c"
#include <math.h>
#include "tarea5.c"

int main(int argc, char* argv[]){
    Matriz matriz;
    eigen solucion;
    matriz=lee_matriz1(argc, argv);
    solucion=metodo_potencia(matriz.A, matriz.m,matriz.n,1e-8);
    printf("Eigen valor: %lf", solucion.eigenvalor);
    printf("\n");
    printf("Eigen vector: ");
    for(int i=0; i<matriz.m;i++){
        printf("%lf, ", solucion.eigenvector[i]);
    }

    liberar_matriz(matriz.A,matriz.m);
    free(solucion.eigenvector);
    return 0;
}
