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
    matriz=lee_matriz1(argc, argv);
    imprime_matrizc(matriz.A, matriz.m, matriz.n);
    liberar_matriz(matriz.A, matriz.m);
    return 0;
}
