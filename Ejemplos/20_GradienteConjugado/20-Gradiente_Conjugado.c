#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../../matrix.h"
#include "../../operacion_matriz.h"
#include "../../solve.h"
#include "../../EcuacionesL_Metodos.h"


//solo sirve para matrices simetricas y definidas positivas
int main(int argc, char * argv[]){
    Matriz matriz;
    Vector b;
    double *x;
    matriz=lee_matriz1(argc,argv);
    b=lee_vector(argv[2]);
    x=Gradiente_Conjugado(matriz.A, b.v, matriz.m,matriz.n);

    printf("El resultado es: ");
    imprime_resultado(x,matriz.m);

    free(b.v);
    free(x);
    liberar_matriz(matriz.A, matriz.m);

    return 0;
}
