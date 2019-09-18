#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "operacion_matriz.h"

////////////////Operaciones sobre matrices////////////////////
void imprime_matrizc(double **matriz, int m, int n){
    for (int i=0; i<m;i++){
        for(int j=0; j<n;j++){
            printf("%lf ",matriz[i][j]);
        }
        printf("\n");
    }
}

void imprime_resultado(double *resultado, int m){
    //printf("EL resultado es: ");
    for(int i=0; i<m;i++){
        printf("%.10lf ", resultado[i]);
    }
    printf("\n");
}

double mabs(double a){
return (a<0)? -a:a;//calcular el valor absoluto
}

void cambia_renglon(double**matriz,int m, int r1,int r2){
    double cambia=0;
    for(int i=0;i<=m;i++){
        cambia=matriz[r1][i];
        matriz[r1][i]=matriz[r2][i];
        matriz[r2][i]=cambia;
    }
}

void cambia_columna(double**matriz,int m, int c1,int c2){
    double cambia=0;
    for(int i=0;i<m;i++){
        cambia=matriz[i][c1];
        matriz[i][c1]=matriz[i][c2];
        matriz[i][c2]=cambia;
    }
}

double find_maxr(double **matriz, int m,int r, int c, int *r2){//encontrar el maximo de una columna de una matriz
    double max=mabs(matriz[r][c]);//inicializar el máximo con el valor del pivote en donde estamos
    for(int i=r; i<m;i++){
        if(mabs(matriz[i][c])>mabs(max)){max=matriz[i][c];*r2=i;}//r2=posicion del valor máximo.
    }
    return max;
}

double find_max(double **matriz, int m, int n, int r, int c, int *r2, int *c2){//encuentra el máximo elemento de una matriz
    double max=mabs(matriz[r][c]);//inicializar en el pivote en el que estamos
    for(int i=r; i<m;i++){
        for(int j=c;j<n;j++){
            if(mabs(matriz[i][j])>mabs(max)){
                max=mabs(matriz[i][j]);
                *r2=i; *c2=j;// posición en renglones y columnas del maximo
            }
        }
    }
    return max;
}

double **multiplicacion(double **matriz, double **matriz2, int m, int n, int p, int q){
    double **resultado=crea_matriz2(m,q);
    if(n!=p){
        printf("No es posible hacer la multiplicacion de estas matrices");
        return 0;
    }

    for(int i=0; i<m; i++){
        for(int j=0; j<n;j++){
            resultado[i][j]=0;
            for(int k=0;k<p;k++){
                  resultado[i][j]+=matriz[i][k]*matriz2[k][j];
            }

        }
    }
    return resultado;
}


double ppunto(double *x, double *y, int m){
    double resultado=0;
    for(int i=0; i<m;i++){
        resultado+=x[i]*y[i];
    }

    return resultado;
}

matriz_elemento find_max_od(double **matriz, int m, int n){
    matriz_elemento maximo;
    maximo.max=0;


    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(i!=j){
                if(mabs(matriz[i][j])>mabs(maximo.max)){
                maximo.max=mabs(matriz[i][j]);
                maximo.pos_i=i; maximo.pos_j=j;// posición en renglones y columnas del maximo
                }
            }
        }
    }

    return maximo;
}
