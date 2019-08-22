#include <stdio.h>
#include "matrix.c"
#include "solve.c"
#include "operacion_matriz.c"
#include "EcuacionesL_Metodos.c"




int main(){
    int m;
    printf("Ingrese el tamano de la matriz: ");
    scanf("%d",&m);
    double **matriz=crea_matriz(m);
    double resultado[m];
    double respaldo[m];
    printf("Ingrese los elementos de la matriz: \n");
    for(int i=0; i<m; i++){
        for(int j=0; j<=m;j++){
            scanf("%lf",&matriz[i][j]);
        }
    }

    desc_LU(matriz,m);
    solv_LU(matriz,m,resultado);
    imprime_resultado(resultado,m);

    liberar_matriz(matriz,m);
    return 0;
}
