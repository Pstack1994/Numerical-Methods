#include<stdio.h>
#include"matrix.c"

void *solv_diagonalsup(double **matriz, int m, double *resultado);
double det_diagonalsup(double **matriz, int m);

int main(){
    int m=0, det=0;
    printf("Ingrese el tamaño de la matriz cuadrada: ");
    scanf("%d",&m);
    double resultado[m];
    double **matriz=crea_matriz(m);
    printf("Ingrese los elementos de la matriz: \n");
    for(int i=0; i<m; i++){
        for(int j=0; j<=m;j++){
            scanf("%lf",&matriz[i][j]);
        }
    }

    solv_diagonalsup(matriz,m,resultado);

    printf("EL resultado de las incognitas es: ");
    for(int i=0; i<m; i++){
        printf("%lf ",resultado[i]);
    }
    det=det_diagonalsup(matriz,m);
    printf("\n");
    printf("El resultado del determinante es: ");
    printf("%lf ", det);

    liberar_matriz(matriz,m);
    return 0;
}

void *solv_diagonalsup(double **matriz, int m, double *resultado){
    double suma=0;
    resultado[m-1]=matriz[m-1][m]/matriz[m-1][m-1];
    for(int i=2; i<=m;i++){
            suma=0;
        for(int j=1; j<i;j++){
            suma+= matriz[m-i][m-j]*resultado[m-j];
        }
        resultado[m-i]=(matriz[m-i][m]-suma)/matriz[m-i][m-i];
    }
}

double det_diagonalsup(double **matriz, int m){
    double resultado;
    resultado=matriz[0][0];
    for(int i=1;i<m;i++){
        resultado*=matriz[i][i];
    }

    return resultado;
}
