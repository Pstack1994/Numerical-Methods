#include <stdio.h>
#include "matrix.c"
#include "solve.c"
#include "operacion_matriz.c"
#include "EcuacionesL_Metodos.c"

int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz1(argc, argv);
    int f=0, c=0;
    double max=0;
    max=find_max(matriz.A,matriz.m,matriz.n,0,0,&f,&c);

    printf("El maximo es: ");
    printf("%lf",max);printf("\n");
    printf("fila: "); printf("%d",f);printf("\n");
    printf("columna: "); printf("%d",c);

    liberar_matriz(matriz.A, matriz.m);

    return 0;
}
