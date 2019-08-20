#include <stdio.h>
#include "matrix.c"
#include "solve.c"

int main(){
int m;

printf("Ingrese el tamano de la matriz: ");
    scanf("%d",&m);
    double **matrizA=crea_matriz(m);
    double resultado[m];
    double matrizL[m][m];
    double matrizU [m][m];
    printf("Ingrese los elementos de la matriz: \n");
    for(int i=0; i<m; i++){
        for(int j=0; j<=m;j++){
            scanf("%lf",&matrizA[i][j]);
        }
    }
int k1;
    for(int i=0; i<m;i++){
        for(int j=0; j<m;j++){
            if(j==0 && i!=0){
               matrizA[i][0]=matrizA[i][0]/matrizA[0][0];
               continue;//se salta todo lo que está abajo.
            }
            if(i==0){
                continue;//se salta todo lo que está abajo.
            }

            if(j<i){
                k1=j;//cambia los limites de la suma del for de abajo.
            }
            if(j>=i){
                k1=i;//cambia los limites de la suma del for de abajo.
            }

            for(int k=0; k<k1;k++){
                matrizA[i][j]-=matrizA[i][k]*matrizA[k][j];
            }
            if(j<i){
                matrizA[i][j]/=matrizA[j][j];
            }
        }
    }

        printf("\n");
    imprime_matrizc(matrizA,m);

    liberar_matriz(matrizA,m);
    return 0;
}
