#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../matrix.h"
#include "../../Eigen.h"
#include "../../operacion_matriz.h"
#include"../../EcuacionesL_Metodos.h"
#include "../../solve.h"


int main(int argc, char *argv[]){
    Matriz matriz;


    matriz=lee_matriz1(argc,argv);
    double **r=crea_matriz2(matriz.m,matriz.n);

    factoriza_QR(matriz.A, r, matriz.m, matriz.n);
    imprime_matrizc(matriz.A,matriz.m,matriz.n);
    printf("\n");
    imprime_matrizc(r,matriz.m,matriz.n);

    liberar_matriz(matriz.A, matriz.m);
    liberar_matriz(r, matriz.m);
    return 0;
}
