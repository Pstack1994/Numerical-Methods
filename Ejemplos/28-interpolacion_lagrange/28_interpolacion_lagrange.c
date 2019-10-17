#include <stdio.h>
#include <stdlib.h>
#include "../../matrix.h"
#include"../../interpolacion.h"


int main(int argc, char *argv[]){
    Vector x, fx,polinomio;
    x=lee_vector(argv[1]);
    fx=lee_vector(argv[2]);

    FILE *guardar;
    guardar=fopen("xfx.txt", "w");
    for(int i=0; i<x.m; i++){
        fprintf(guardar,"%lf %lf \n",x.v[i], fx.v[i]);
    }

    polinomio=interpola_lagrange(x,fx,-2,4);

    fclose(guardar);
    free(fx.v);
    free(x.v);
    free(polinomio.v);
    return 0;
}
