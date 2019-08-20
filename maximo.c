#include <stdio.h>
#include"matrix.c"

double find_max(double **matriz, int m, int p, int *f, int *c);

int main(){
    int m=0, f=0, c=0;
    double max=0;

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

    max=find_max(matriz,m,0,&f,&c);
    printf("El maximo es: ");
    printf("%lf",max);printf("\n");
    printf("fila: "); printf("%d",f);printf("\n");
    printf("columna: "); printf("%d",c);

    liberar_matriz(matriz, m);

    return 0;
}


double find_max(double **matriz, int m,int p, int *f, int *c){
    double max=matriz[p][p];
    for(int i=p; i<m;i++){
        for(int j=p;j<m;j++){
            if(matriz[i][j]>max){max=matriz[i][j]; *f=i; *c=j;}
        }
    }
    return max;
}
