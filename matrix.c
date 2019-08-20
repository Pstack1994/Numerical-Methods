#include <stdio.h>
#include<stdlib.h>

double **crea_matriz(int m);
void liberar_matriz(double **matriz,int m);


double **crea_matriz(int m){
    double **matriz;
    matriz=(double **)malloc(m*sizeof(double*));
    for(int i=0; i<m;i++){
        matriz[i]=(double *)malloc((m+1)*sizeof(double));
    }
    return matriz;
}

void liberar_matriz(double **matriz,int m){
    for(int i=0;i<m;i++){
        free(matriz[i]);
    }
    free(matriz);
}

