#include <stdio.h>
#include <stdlib.h>
#include "../../matrix.h"

Vector interpola_lagrange(Vector x, Vector fx, int a, int b);
Vector derivada_lagrange(Vector x, Vector fx, double x0);
Vector coef_lagrange(Vector x, Vector fx, double x0);


int main(int argc, char *argv[]){
    Vector x, fx,polinomio;
    x=lee_vector(argv[1]);
    fx=lee_vector(argv[2]);

    FILE *guardar;
    guardar=fopen("xfx.txt", "w");
    for(int i=0; i<x.m; i++){
        fprintf(guardar,"%lf %lf \n",x.v[i], fx.v[i]);
    }

    polinomio=interpola_lagrange(x,fx,-10,10);

    fclose(guardar);
    free(fx.v);
    free(x.v);
    free(polinomio.v);
    return 0;
}

Vector interpola_lagrange(Vector x, Vector fx, int a, int b){
    Vector coef, polinomio;
    polinomio.m=4*(b-a);
    polinomio.n=x.n;
    polinomio.v=(double*)malloc(polinomio.m*sizeof(double));
    double suma;
    int contador=0;

    FILE *guardar;
    guardar=fopen("polinomioevaluado.txt", "w");

    for(double x0=a; x0<b; x0+=0.25){
        coef=coef_lagrange(x,fx,x0);
            suma=0;
        for(int i=0; i<x.m; i++){
            suma+=fx.v[i]*coef.v[i];
        }
        polinomio.v[contador]=suma;
        fprintf(guardar,"%lf %lf \n",x0, polinomio.v[contador]);
        contador++;
        free(coef.v);
    }
    fclose(guardar);
    return polinomio;
}

Vector coef_lagrange(Vector x, Vector fx, double x0){
    Vector coeficientes;
    coeficientes.m=x.m;
    coeficientes.n=x.n;
    coeficientes.v=(double*)malloc(coeficientes.m*sizeof(double));

        for(int i=0; i<x.m ;i++){
            double l=1;
            for(int j=0; j<x.m; j++){
                if(i!=j){
                    l*=(x0-x.v[j])/(x.v[j]-x.v[i]);
                }
            }
            coeficientes.v[i]=l;
        }
    return coeficientes;

}

Vector derivada_lagrange(Vector x,Vector fx, double x0){
    Vector derivada;
    derivada.m=x.m;
    derivada.n=x.n;
    derivada.v=(double*)malloc(derivada.m*sizeof(double));

    for(int i=0; i<x.m ;i++){
        double suma=0;
        for(int j=0; j<x.m; j++){
            if(i!=j){
                double l=1;
                for(int m=0; m<x.m; m++){
                    if(m!=i && m!=j){
                        l*=(x0-x.v[m])/(x.v[j]-x.v[m]);
                    }
                }

                suma+=(1/(x.v[i]-x.v[j]));


            }
        }
        printf("%lf ", suma);
        derivada.v[i]=suma;

    }

    return derivada;

}
