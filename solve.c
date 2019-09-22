#include <stdio.h>
#include<stdlib.h>
#include"solve.h"

double det_diagonal(double **matriz, int m){
    double resultado;
    resultado=matriz[0][0];
    for(int i=1;i<m;i++){
        resultado*=matriz[i][i];
    }
    return resultado;
}

void solv_diagonal(double **matriz, double *b, int m,double *resultado){
    for(int i=0; i<m;i++){
        if(matriz[i][i]==0){
            printf("el sistema no tiene solucion");
            return;
        }
        resultado[i]= b[i]/matriz[i][i];
    }
}

void solv_tinf(double **matriz, double *b, int m, double *resultado){//resuelve una matriz triangular inferior
    double suma=0;
    resultado[0]=b[0]/matriz[0][0];
    for(int i=1; i<m;i++){
        suma=0;
        for(int j=0; j<i;j++){
            suma+=matriz[i][j]*resultado[j];
        }
        if(matriz [i][i]==0){
            printf("El sistema no tiene solucion");
            return;
        }
        resultado[i]=(b[i]-suma)/matriz[i][i];
    }
}

void solv_tsup(double **matriz, double *b, int m, double *resultado){
    double suma=0;
    resultado[m-1]=b[m-1]/matriz[m-1][m-1];
    for(int i=2; i<=m;i++){
            suma=0;
        for(int j=1; j<i;j++){
            suma+= matriz[m-i][m-j]*resultado[m-j];
        }
        if(matriz [m-i][m-i]==0){
            printf("El sistema no tiene solucion");
            return;
        }
        resultado[m-i]=(b[m-i]-suma)/matriz[m-i][m-i];
    }
}
