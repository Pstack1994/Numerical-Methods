#include <stdio.h>
#include <stdlib.h>
#include "matrix.c"
#include "operacion_matriz.c"
#include "solve.c"


int main(int argc, char* argv[]){
    double** A;
    A = lee_matriz(argc, argv);
	imprime_matrizc(A,4);
	liberar_matriz(A,4);
    return 0;
}
