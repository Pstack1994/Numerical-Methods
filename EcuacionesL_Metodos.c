#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "solve.h"
#include <string.h>
#include "operacion_matriz.h"
#include "EcuacionesL_Metodos.h"

///////////////////////metodos para resolver sistemas de ecuaciones lineales//////////////////////////////


///////////////////////Gauss sin pivoteo//////////////////////////////////////////////////////
double G_sinpivoteo(double**matriz, double *b,int m, int n, double *resultado){
int r=0, c=0, r2=0, s=1;//r=renglomnes, c=columnas, r2=renglon por el cual se intercambiará, s=signo del determinante.
double max, det=1;//max=máximo de la columna c, det=determinante.

    while (r<m){//recorrer todos los renglones de la matriz
        if(matriz[r][c]==0){//verificar que pivote no sea 0
            max=find_maxr(matriz,m,r,c,&r2);//encontrar maximo de la columna m
            if(max==0){printf("El sistema no tiene solucion o tiene infinitas soluciones");return 0;}
            if(matriz[r][c]!= max){//si el valor del máximo es diferente al valor del pivote intercambiar los renglones
                cambia_renglon(matriz,b ,m, r,r2);
                s*=-1;//conservar el signo del determinante
            }
        }
        det*=matriz[r][c];//se calcula el determinante multiplicando el valor de los pivotes

        for(int i=n-1; i>=0;i--){//dividir el renglon r entre el valor del pivote
            matriz[r][i]= (matriz[r][i])*(1/matriz[r][c]);
        }
        b[r]/=matriz[r][c];

        for(int i=r+1;i<m;i++){
            if(matriz[i][c]!=0){
                for(int j=n-1;j>=0;j--){
                    matriz[i][j]=matriz[i][j]-matriz[i][c]*matriz[r][j];//eliminar los elementos por debajo del pivote
                    b[i]=b[i]-matriz[i][c]*b[j];
                }

            }

        }


            r++;
        c++;
}
    solv_tsup(matriz,b,m, resultado);
    det=s*det;
    return det;
}
