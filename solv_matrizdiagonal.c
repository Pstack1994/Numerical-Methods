#include <stdio.h>
#include"matrix.c"

double *solv_diagonal(double **x,int m,double *resultado);

int main (){
    int m=0;

    printf("Dame el tamano de la matriz: \n");
    scanf("%d",&m);
    double resultado[m];
    double **matriz=crea_matriz(m);
    printf("Dame los elementos de la matriz: \n");
    for(int i=0; i<m;i++){
        for(int j=0; j<m+1;j++){
            scanf("%lf",&matriz[i][j]);
        }
    }

    solv_diagonal(matriz,m,resultado);

    for(int j=0; j<m;j++){
        printf("%lf ",resultado[j]);
    }

    liberar_matriz(matriz,m);
    return 0;
}


double *solv_diagonal(double **x,int m,double *resultado){
    for(int i=0; i<m;i++){
        resultado[i]= x[i][m]/x[i][i];
    }
    return resultado;
}
