#include <stdio.h>
#include <stdlib.h>
#include "../../matrix.h"

int main(int argc, char *argv[]){
    Vector x, fx, polinomio;
    x=lee_vector(argv[1]);
    fx=lee_vector(argv[2]);

int z=5;
double valor=0;

    for(int i=0; i<x.m ;i++){
        double l=fx.v[i];
        for(int j=0; j<x.m; j++){
            if(i!=j){
                l=(l*(z-x.v[j]))/(x.v[i]-x.v[j]);
            }
        }
        valor=valor+l;
    }

    printf("EL valor es: %lf", valor);

    free(fx.v);
    free(x.v);
    return 0;
}
