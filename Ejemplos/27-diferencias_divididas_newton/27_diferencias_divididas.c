#include <stdio.h>
#include "../../matrix.h"
#include <stdlib.h>

//Programa que interpola utilizando las diferencias divididas de Newton
//los puntos no necesariamente deben ser equiespaciados
//x: puntos que nos da el problema
//fx: polinomio evaluado en esos puntos


Matriz dif_div_newton(Vector fx, Vector x);
Vector evalua_dif_div_newton(Vector x, Matriz tabla, int a, int b);

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
    //evaluar polinomio de newton
    polinomio=evalua_dif_div_newton(x,tabla,-4,4);

    //liberar memoria
    fclose(guardar);
    free(x.v);
    free(fx.v);
    free(polinomio.v);
    liberar_matriz(tabla.A, tabla.m);
    return 0;
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
