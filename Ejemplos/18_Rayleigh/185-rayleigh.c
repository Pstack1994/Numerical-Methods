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

eigen Metodo_Rayleigh(double ** matriz, double *xa, int m, int n, double tole);

int main(int argc, char* argv[]){
    Matriz matriz;
    Vector xa;
    eigen solucion;
    matriz=lee_matriz1(argc, argv);
    xa=lee_vector(argv[2]);


    solucion=Metodo_Rayleigh(matriz.A, xa.v,matriz.m,matriz.n,1e-9);

    liberar_matriz(matriz.A, matriz.m);
    free(xa.v);
    free(solucion.eigenvector);

    return 0;
}

eigen Metodo_Rayleigh(double ** matriz, double *xa, int m, int n, double tole){
    eigen solucion;
    double error=0,norma=0;
    double lambdan=0, lambdaa=0, *swap;
    double *xn, aux=0;
    xn=(double *)malloc(m*sizeof(double));

    int max_it=0;
    solucion.eigenvector=(double *)malloc(m*sizeof(double));



    //normalizar el vector inicial
    norma=ppunto(xa,xa,m);
    norma=sqrt(norma);
    for(int i=0; i<m; i++){
        xa[i]=xa[i]/norma;
    }

  do{
        //multiplicar matriz por vector para calcular v1
        lambdan=0;
        for(int i=0; i<m; i++){
            aux=0;
            for(int j=0; j<n;j++){
                aux+=matriz[i][j]*xa[j];
            }
            xn[i]=aux;
            lambdan+=xa[i]*xn[i];
        }


        solucion.eigenvalor=lambdan;

        error=mabs(lambdan-lambdaa);
        lambdaa=lambdan;

        norma=ppunto(xn,xn, m);
        norma=sqrt(norma);
        for(int i=0; i<m; i++){
            xn[i]=xn[i]/norma;
        }
        //solucion.eigenvector=xa.v;
        swap=xa;
        xa=xn;
        xn=swap;
        max_it++;
    }while(error>tole && max_it<100);
        swap=solucion.eigenvector;
        solucion.eigenvector=xa;
        xa=swap;
    printf("Converge en: %d iteraciones\n", max_it);
    printf("Eigenvalor: %lf\n", solucion.eigenvalor);
    printf("Eigenvector: \n");
    imprime_resultado(solucion.eigenvector, m);
    free(xn);
    return solucion;
}
