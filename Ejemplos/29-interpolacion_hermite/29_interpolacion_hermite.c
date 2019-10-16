#include <stdio.h>
#include <stdlib.h>
#include "../../matrix.h"


double derivada_lagrange(Vector x, Vector fx, double x0, int i);
Vector interpola_hermite(Vector x, Vector fx, Vector fpx, int a, int b);
Vector coef_lagrange(Vector x, Vector fx, double x0);

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

    polinomio=interpola_hermite(x,fx,fpx,-1,3);

    fclose(guardar);
    free(fx.v);
    free(polinomio.v);
    free(x.v);
    free(fpx.v);
    return 0;
}

double derivada_lagrange(Vector x, Vector fx, double x0, int i){
        double derivada;
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
        derivada=suma;
        return derivada;
        //printf("\n %lf\n", *derivada);
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

Vector interpola_hermite(Vector x, Vector fx, Vector fpx, int a, int b){
    double primero=0;
    double segundo=0;
    double derivada;
    Vector coef;
    Vector polinomio;
    polinomio.m=4*(b-a);
    polinomio.n=x.n;
    polinomio.v=(double*)malloc(polinomio.m*sizeof(double));
    int contador=0;

    FILE *guardar;
    guardar=fopen("polinomioevaluado.txt", "w");

    for(double x0=a; x0<b; x0+=0.25){
        primero=0;
        segundo=0;
        coef=coef_lagrange(x,fx,x0);

        for(int i=0; i<x.m; i++){
            derivada=derivada_lagrange(x,fx,x.v[i], i);
            primero+=((-2*derivada*x0)+1 +(2*x.v[i]*derivada))*coef.v[i]*coef.v[i]*fx.v[i];
            segundo+=(x0-x.v[i])*coef.v[i]*coef.v[i]*fpx.v[i];
        }
        polinomio.v[contador]=primero+segundo;
        fprintf(guardar,"%lf %lf \n",x0, polinomio.v[contador]);
        contador++;
        free(coef.v);
    }
    fclose(guardar);
    return polinomio;
}
