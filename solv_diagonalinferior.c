#include <stdio.h>
#include"matrix.c"

void *solv_diagonalinf(double **matriz,int m, double *resultado);
double det_diagonalinf(double **matriz, int m);

int main(){
    int m=0;
    double det=0;

    printf("Ingrese el tamano de la matriz: ");
    scanf("%d",&m);
    double resultado[m];
    double **matriz=crea_matriz(m);
    printf("Ingrese los elementos de la matriz: \n");
    for(int i=0; i<m; i++){
        for(int j=0; j<=m;j++){
            scanf("%lf",&matriz[i][j]);
        }
    }
    solv_diagonalinf(matriz,m,resultado);
    for(int i=0; i<m; i++){
        printf("%lf ",resultado[i]);
    }
    printf("\n");
    printf("El determinante es: ");
    det=det_diagonalinf(matriz,m);
    printf("%lf",det);
    liberar_matriz(matriz,m);
    return 0;
}

void *solv_diagonalinf(double **matriz,int m, double *resultado){
    double suma=0, c=0;
    resultado[0]=matriz[0][m]/matriz[0][0];
    for(int i=1; i<m;i++){
        suma=0;
        for(int j=0; j<i;j++){
            suma+=matriz[i][j]*resultado[j];
        }
        resultado[i]=(matriz[i][m]-suma)/matriz[i][i];
    }
}

double det_diagonalinf(double **matriz, int m){
    double resultado;
    resultado=matriz[0][0];
    for(int i=1;i<m;i++){
        resultado*=matriz[i][i];
    }
    return resultado;
}
