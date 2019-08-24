#include <stdio.h>
#include "matrix.c"
#include "solve.c"
#include "operacion_matriz.c"
#include "EcuacionesL_Metodos.c"


int main(){
    int m=2,n=2,p=2,q=2;

    double **matriza[2][2]={{1,2},{2,3}};
    double **matrizb[2][2]={{1,2},{2,3}};

    double **resultado;
    resultado=multiplicacion(matriza,matrizb,m,n,p,q);
    imprime_matrizc(resultado,2,2);
    //liberar_matriz(matriz.A,matriz.m);
    return 0;
}
