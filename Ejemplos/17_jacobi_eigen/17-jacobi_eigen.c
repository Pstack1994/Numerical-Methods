#include <stdio.h>
#include <math.h>
#include "../../matrix.h"
#include "../../operacion_matriz.h"



matriz_elemento find_max_od(double **matriz, int m, int n);

int main(int argc, char* argv[]){
    matriz_elemento maximo;
    Matriz matriz;
    double theta, numerador, denominador;
    matriz=lee_matriz1(argc, argv);

    //encontrar maximo fuera de la diagonal
    maximo=find_max_od(matriz.A, matriz.m, matriz.n);

    numerador=2*(matriz.A[maximo.pos_i][maximo.pos_j]);
    denominador=matriz.A[maximo.pos_i][maximo.pos_i]*matriz.A[maximo.pos_j][maximo.pos_j];

    //calcular angulo de la rotacion con las posiciones del maximo
    theta=(1/2)*atan2(numerador,denominador);

    for(int l=0; l<matriz.m; l++){
        matriz.A[l][maximo.pos_i]=matriz.A[l][maximo.pos_i]*cos(theta)+matriz.A[l][maximo.pos_j]*sin(theta);
        matriz.A[l][maximo.pos_j]=-matriz.A[l][maximo.pos_j]*sin(theta)+matriz.A[l][maximo.pos_j]*cos(theta);//no se si es i o j la segunda
    }

    //algo con la identidad que aun no se

    for(int k=0; k< matriz.m; k++){
        matriz.A[maximo.pos_i][k]=matriz.A[maximo.pos_i][k]*cos(theta)+matriz.A[maximo.pos_j][k]*sin(theta);
        matriz.A[maximo.pos_j][k]=-matriz.A[maximo.pos_i][k]*sin(theta)+matriz.A[maximo.pos_j][k]*cos(theta);//comprobar a mano
    }

    printf("%lf ", theta);
    liberar_matriz(matriz.A, matriz.m);
    return 0;
}

matriz_elemento find_max_od(double **matriz, int m, int n){
    matriz_elemento maximo;
    maximo.max=mabs(matriz[0][0]);


    for(int i=1; i<m; i++){
        for(int j=0; j<n; j++){
            if(mabs(matriz[i][j])>mabs(maximo.max)){
                maximo.max=mabs(matriz[i][j]);
                maximo.pos_i=i; maximo.pos_j=j;// posición en renglones y columnas del maximo
            }
        }
    }

    return maximo;
}
