#include <stdio.h>
#include "../../matrix.h"
#include <stdlib.h>
#include"../../interpolacion.h"

//Programa que interpola utilizando las diferencias divididas de Newton
//los puntos no necesariamente deben ser equiespaciados
//x: puntos que nos da el problema
//fx: polinomio evaluado en esos puntos

int main(int argc, char *argv[]){
    Vector x, fx, polinomio;
    Matriz tabla;
    x=lee_vector(argv[1]);
    fx=lee_vector(argv[2]);

    //guardar datos x, fx para graficar
    FILE *guardar;
    guardar=fopen("xfx.txt", "w");
    for(int i=0; i<x.m; i++){
        fprintf(guardar,"%lf %lf \n",x.v[i], fx.v[i]);
    }
    //calcular tabla de diferencias divididas
    tabla=dif_div_newton(fx,x);

    for(int i=0; i<tabla.m; i++){
        for(int j=0; j<tabla.m; j++){
            printf("%lf ", tabla.A[i][j]);
        }
        printf("\n");
    }
    //evaluar polinomio de newton
    polinomio=evalua_dif_div_newton(x,tabla,-4,5);

    //liberar memoria
    fclose(guardar);
    free(x.v);
    free(fx.v);
    free(polinomio.v);
    liberar_matriz(tabla.A, tabla.m);
    return 0;
}
