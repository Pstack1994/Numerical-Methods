#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<time.h>
#include "../../matrix.h"
#include "../../Eigen.h"
#include "../../solve.h"
#include "../../operacion_matriz.h"
#include"../../EcuacionesL_Metodos.h"


int main(int argc, char* argv[]){
    Matriz matriz;
    Vector xa;
    matriz=lee_matriz1(argc, argv);
    xa=lee_vector(argv[2]);

    int m=matriz.m;

    double error=0,norma=0, tole=2.22045e-9;
    double lambdan=0, lambdaa=0, *swap;
    double *xn, aux=0;
    xn=(double *)malloc(m*sizeof(double));

    int max_it=0;
    eigen solucion;
    solucion.eigenvector=(double *)malloc(m*sizeof(double));



    //normalizar el vector inicial
    norma=ppunto(xa.v,xa.v,xa.m);
    norma=sqrt(norma);
    for(int i=0; i<m; i++){
        xa.v[i]=xa.v[i]/norma;
    }

  do{
        //multiplicar matriz por vector para calcular v1
        lambdan=0;
        for(int i=0; i<m; i++){
            aux=0;
            for(int j=0; j<matriz.n;j++){
                aux+=matriz.A[i][j]*xa.v[j];
            }
            xn[i]=aux;
            lambdan+=xa.v[i]*xn[i];
        }


        //lambdan=ppunto(xa.v, xn, m);
        //printf("Sigma: %lf\n", lambdan);
        solucion.eigenvalor=lambdan;

        error=mabs(lambdan-lambdaa);
        lambdaa=lambdan;
        norma=ppunto(xn,xn, m);
        norma=sqrt(norma);
        for(int i=0; i<m; i++){
            xn[i]=xn[i]/norma;
        }
        //solucion.eigenvector=xa.v;
        swap=xa.v;
        xa.v=xn;
        xn=swap;


        max_it++;
    }while(error>tole && max_it<100);
        swap=solucion.eigenvector;
        solucion.eigenvector=xa.v;
        xa.v=swap;
    printf("Converge en: %d iteraciones\n", max_it);
    printf("Eigenvalor: %lf\n", solucion.eigenvalor);
    printf("Eigenvector: \n");
    imprime_resultado(solucion.eigenvector, m);
    liberar_matriz(matriz.A, m);
    free(xa.v);
    free(xn);
    free(solucion.eigenvector);

    return 0;
}
