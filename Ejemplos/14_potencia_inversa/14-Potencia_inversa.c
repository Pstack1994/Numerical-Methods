#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../../matrix.h"
#include "../../operacion_matriz.h"
#include "../../solve.h"
#include "../../EcuacionesL_Metodos.h"

eigen potencia_inversa(double **matriz, int m, int n, double tole);

int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz1(argc, argv);
    eigen solucion;
    solucion=potencia_inversa(matriz.A, matriz.m, matriz.n, 1e-15);

    printf("Eigen valor: %.20lf", solucion.eigenvalor);
    printf("\n");
    printf("Eigen vector: ");
    for(int i=0; i<matriz.m;i++){
        printf("%lf, ", solucion.eigenvector[i]);
    }

    liberar_matriz(matriz.A,matriz.m);
    free(solucion.eigenvector);
    return 0;
}

eigen potencia_inversa(double **matriz, int m, int n, double tole){
    double  xn[m], error=0, numerador=0, denominador=0, norma=0;
    double xa[m], lambdan=0, lambdaa=0;
    int max_it=0, posicion[m];
    eigen solucion;
    solucion.eigenvector=(double *)malloc(m*sizeof(double));

    ///inicilizar vector anterior
    srand(time(NULL));
    for(int i=0; i<m;i++){
        xa[i]=rand()%100+1;
    }

    //factorizacion LU;
    desc_LU(matriz, m, posicion);

    do{
        //normalizar vector xa
        norma=0;
        for(int i=0; i<m; i++){
            norma+=xa[i]*xa[i];
        }
        norma=sqrt(norma);

        for(int i=0; i<m; i++){
            xa[i]=xa[i]/norma;
        }
        //poner xa en la ultima columna de matriz
        for(int i=0; i<m; i++){
            matriz[i][n]=xa[i];
        }
        //resolver sistema de ecuaciones;
        solv_LU(matriz, m, xn);
        /*printf("\n");
        for(int i=0; i<m; i++){
            printf("%lf ", xn[i]);
        }
        printf("\n");*/

        //realizar producto punto para calcular lambda mas pequeño
        numerador=0;
        denominador=0;

        for(int i=0; i<m; i++){
            numerador+=xn[i]*xa[i];
            denominador+=xn[i]*xn[i];
        }

        lambdan=numerador/denominador;
        solucion.eigenvalor=lambdan;

        error=mabs(lambdan-lambdaa);
        lambdaa=lambdan;

        for(int i=0; i<m; i++){
            solucion.eigenvector[i]=xa[i];
            xa[i]=xn[i];
        }

        max_it++;

    }while(max_it<10000 && error>tole);

    printf("max it: %d\n", max_it);

    return solucion;
}
