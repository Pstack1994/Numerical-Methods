#include <stdio.h>
#include <stdlib.h>
#include "../../matrix.h"
#include "../../interpolacion.h"


int main(int argc, char *argv[]){
    Vector x, fx, fpx, polinomio;
    x=lee_vector(argv[1]);
    fx=lee_vector(argv[2]);
    fpx=lee_vector(argv[3]);


    FILE *guardar;
    guardar=fopen("xfx.txt", "w");
    for(int i=0; i<x.m; i++){
        fprintf(guardar,"%lf %lf \n",x.v[i], fx.v[i]);
    }

    polinomio=interpola_hermite(x,fx,fpx,-2,5);

    fclose(guardar);
    free(fx.v);
    free(polinomio.v);
    free(x.v);
    free(fpx.v);
    return 0;
}
