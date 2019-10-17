#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include<time.h>
#include"matrix.h"
#include"interpolacion.h"

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
                    l*=(x0-x.v[j])/(x.v[i]-x.v[j]);
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

Matriz dif_div_newton(Vector fx, Vector x){
    //crear tabla de diferencias
    Matriz tabla;
    tabla.m=x.m;
    tabla.n=x.m;
    tabla.A=crea_matriz2(tabla.m, tabla.n);
    //inicializar tabla de diferencias
    for(int i=0; i<x.m; i++){
        tabla.A[i][0]=fx.v[i];
    }

    int p=0;
    for(int i=0; i<tabla.m; i++){
        p=0;
        for(int j=i+1; j<tabla.m; j++){
            tabla.A[j][i+1]=(tabla.A[j][i]-tabla.A[j-1][i])/(x.v[j]-x.v[p]);
            p++;
        }
    }

    return tabla;
}

Vector evalua_dif_div_newton(Vector x, Matriz tabla, int a, int b){
    //se decidio evaluar el polinomio de 0.25 en 0.25
    Vector polinomio;
    polinomio.v=(double*)malloc((4*(b-a))*sizeof(double));
    double p1=0, aux=0;

    int contador=0;
    FILE *guardar;
    guardar=fopen("polinomioevaluado.txt", "w");
    for(float x0=a; x0<b; x0=x0+0.25){
        p1=0;
        for(int i=0; i<tabla.m; i++){
            aux=1;
            for(int j=0; j<i; j++){
                aux=aux*(x0-x.v[j]);
            }
            p1=p1+tabla.A[i][i]*aux;
        }
        polinomio.v[contador]=p1;
        fprintf(guardar,"%lf %lf \n",x0, polinomio.v[contador]);
        contador++;
    }
    fclose(guardar);

    return polinomio;
}
