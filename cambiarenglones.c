#include<stdio.h>
#include"matrix.c"

void *cambia_renglon(double**matriz,int m, int r1, int r2);
double find_max(double **matriz, int m,int r, int c, int *r2);

int main(){
    int m=0, r=0, c=0, r2=0;
    double max=0;

    printf("Ingrese el tamano de la matriz: ");
    scanf("%d",&m);
    double **matriz=crea_matriz(m);
    printf("Ingrese los elementos de la matriz: \n");

    for(int i=0; i<m; i++){
        for(int j=0; j<=m;j++){
            scanf("%lf",&matriz[i][j]);
        }
    }

    while (r<m){

        if(matriz[r][c]==0){
            max=find_max(matriz,m,r,c,&r2);
            if(max==0){printf("El sistema no tiene solucion o tiene infinitas soluciones");return;}
            if(matriz[r][c]!= max){
                cambia_renglon(matriz, m, r,r2);
            }
        }

        for(int i=m; i>=0;i--){
            matriz[r][i]= (matriz[r][i])*(1/matriz[r][c]);
        }

        if(matriz[r][c]!=0){
            for(int i=r+1;i<m;i++){
                if(matriz[i][c]!=0){
                    for(int j=m;j>=0;j--){
                        matriz[i][j]=matriz[i][j]-matriz[i][c]*matriz[r][j];
                    }
                }
            }
            r++;
        }
        c++;

    for(int i=0; i<m; i++){
        for(int j=0; j<=m;j++){
            printf("%lf ",matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}



    /*cambia_renglon(matriz,m,0,1);

    for(int i=0; i<m; i++){
        for(int j=0; j<=m;j++){
            printf("%lf ",matriz[i][j]);
        }
        printf("\n");
    }
    max=find_max(matriz, m, 0,0);
    printf("El maximo es: ");
    printf("%lf",max);*/

    liberar_matriz(matriz,m);
    return 0;
}

void *cambia_renglon(double**matriz,int m, int r1,int r2){
    double cambia=0;
    for(int i=0;i<=m;i++){
        cambia=matriz[r1][i];
        matriz[r1][i]=matriz[r2][i];
        matriz[r2][i]=cambia;
    }
}

double find_max(double **matriz, int m,int r, int c, int *r2){
    double max=matriz[r][c];
    for(int i=r; i<m;i++){
        if(matriz[i][c]>max){max=matriz[i][c];*r2=i;}
    }
    return max;
}
