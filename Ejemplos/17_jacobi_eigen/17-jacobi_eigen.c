#include <stdio.h>
#include <math.h>
#include "../../matrix.h"
#include "../../operacion_matriz.h"



matriz_elemento find_max_od(double **matriz, int m, int n);

int main(int argc, char* argv[]){
    matriz_elemento maximo;
    Matriz matriz;
    double theta, numerador, denominador;
    double **identidad, tole=1e-8;
    int max_it=0;

    matriz=lee_matriz1(argc, argv);
    identidad=crea_matriz(matriz.m);

    //inicializar matriz identidad
    for(int i=0; i<matriz.m; i++){
        for(int j=0; j<matriz.m; j++){
            if(i==j){
                identidad[i][j]=1;
            }else {
                identidad[i][j]=0;
            }
        }
    }

    do{
        //encontrar maximo fuera de la diagonal
        maximo=find_max_od(matriz.A, matriz.m, matriz.n);
        int i=maximo.pos_i;
        int j=maximo.pos_j;

        printf("maximo: %lf\n", maximo.max);
        printf("pos_i: %d\n", maximo.pos_i);
        printf("pos_j: %d\n", maximo.pos_j);
        numerador=2*(matriz.A[maximo.pos_i][maximo.pos_j]);
        denominador=matriz.A[maximo.pos_i][maximo.pos_i]-matriz.A[maximo.pos_j][maximo.pos_j];

        printf("Numerador: %lf\n", numerador);
        printf("denominador: %lf\n", denominador);
        //calcular angulo de la rotacion con las posiciones del maximo
        double s,c;
        theta=atan2(numerador,denominador);

        if(theta>0){
            theta=0.5*(-theta+M_PI);
        }
        if(theta<0){
            theta=-0.5*(-theta-M_PI);
        }
        printf("theta= %lf\n", theta);

        s=sin(theta);
        c=cos(theta);
        printf("seno= %lf\n", s);
        printf("cos= %lf\n", c);

        double aii_k= matriz.A[i][i];
        double ajj_k= matriz.A[j][j];
        double aij_k=matriz.A[i][j];

        matriz.A[i][i]=(aii_k*c*c)+(2*aij_k*c*s)+(ajj_k*s*s);
        matriz.A[j][j]=(aii_k*s*s)-(2*aij_k*c*s)+(ajj_k*c*c);
        matriz.A[i][j]=((ajj_k-aii_k)*c*s)+(aij_k*(c*c-s*s));
        matriz.A[j][i]=matriz.A[i][j];


        double air_k, ajr_k;

        for(int r=0; r<matriz.m; r++){
            air_k=matriz.A[i][r];
            ajr_k= matriz.A[j][r];

            if(i!=r){
                if(r==j){
                    ajr_k=ajj_k;
                }
            matriz.A[i][r]=(air_k*c)+(ajr_k*s);
            matriz.A[r][i]=matriz.A[i][r];
            }

            if(j!=r){
                if(r==i){
                    air_k=aii_k;
                }
            matriz.A[j][r]=-air_k*s+ajr_k*c;
            matriz.A[r][j]=matriz.A[j][r];
            }


        }






/*
        //formulas dadas por Botello
        for(int l=0; l<matriz.m; l++){
            matriz.A[l][maximo.pos_i]=matriz.A[l][maximo.pos_i]*c+matriz.A[l][maximo.pos_j]*s;
            matriz.A[l][maximo.pos_j]=-matriz.A[l][maximo.pos_j]*s+matriz.A[l][maximo.pos_i]*c;//no se si es i o j la segunda
        }

        //algo con la identidad que aun no se
        for(int l=0; l<matriz.m; l++){
            identidad[l][maximo.pos_i]=identidad[l][maximo.pos_i]*c+identidad[l][maximo.pos_j]*s;
            identidad[l][maximo.pos_j]=-identidad[l][maximo.pos_j]*s+identidad[l][maximo.pos_i]*c;//no se si es i o j la segunda
        }

        for(int k=0; k< matriz.m; k++){
            matriz.A[maximo.pos_i][k]=matriz.A[maximo.pos_i][k]*c+matriz.A[maximo.pos_j][k]*s;
            matriz.A[maximo.pos_j][k]=-matriz.A[maximo.pos_j][k]*s+matriz.A[maximo.pos_i][k]*c;//comprobar a mano
        }

*/
        max_it++;
    }while(maximo.max>tole && max_it <1);


    imprime_matrizc(matriz.A,matriz.m,matriz.m);

    liberar_matriz(matriz.A, matriz.m);
    liberar_matriz(identidad, matriz.m);
    return 0;
}

matriz_elemento find_max_od(double **matriz, int m, int n){
    matriz_elemento maximo;
    maximo.max=0;


    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(i!=j){
                if(mabs(matriz[i][j])>mabs(maximo.max)){
                    maximo.max=mabs(matriz[i][j]);
                    maximo.pos_i=i; maximo.pos_j=j;// posición en renglones y columnas del maximo
                }
            }
        }
    }

    return maximo;
}
