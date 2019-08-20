#include<stdio.h>
#include"matrix.c"
#include"solve.c"

int main(){
    int m=0;
    double det;
    printf("Ingrese el tamano de la matriz: ");
    scanf("%d",&m);
    double **matriz=crea_matriz(m);
    double resultado[m];

    printf("Ingrese los elementos de la matriz: \n");
    for(int i=0; i<m; i++){
        for(int j=0; j<=m;j++){
            scanf("%lf",&matriz[i][j]);
        }
    }
    det=GJ_pivoteo(matriz, m,resultado);
    imprime_resultado(resultado,m);
    printf("\n");
    printf("%lf",det);
    liberar_matriz(matriz,m);
    return 0;
}
