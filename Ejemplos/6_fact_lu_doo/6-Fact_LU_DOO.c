#include <stdio.h>
#include "../../matrix.h"
#include "../../solve.h"
#include "../../operacion_matriz.h"
#include "../../EcuacionesL_Metodos.h"




int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz(argc, argv);
    double resultado[matriz.m];
    double det;
    int posicion[matriz.m];
    desc_LU(matriz.A, matriz.m, posicion);
    det=det_diagonal(matriz.A,matriz.m);
    solv_LU(matriz.A,matriz.m,resultado);
    imprime_resultado(resultado,matriz.m);
    printf("El determinante es: ");
    printf("%lf", det);
    liberar_matriz(matriz.A,matriz.m);
    return 0;
}
