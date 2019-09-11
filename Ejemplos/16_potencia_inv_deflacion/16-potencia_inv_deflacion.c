#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include "../../matrix.h"
#include "../../solve.h"
#include "../../operacion_matriz.h"
#include"../../EcuacionesL_Metodos.h"


eigen2 deflacion_potenciainv(double **matriz, int m, int n, double tole);

int main(int argc, char* argv[]){
    Matriz matriz;
    eigen2 solucion;
    matriz=lee_matriz1(argc, argv);
    solucion=deflacion_potenciainv(matriz.A, matriz.m,matriz.n,1e-8);
    printf("Los eigenvalores son: \n");
    imprime_resultado(solucion.eigenvalor,matriz.m);
    printf("Los eigenvectores son: ");
        printf("\n");
        for(int i=0; i<matriz.m; i++){
            for(int j=0; j<matriz.m; j++){
                printf("%lf ", solucion.eigenvector[i][j]);
            }
            printf("\n");
        }


    liberar_matriz(matriz.A,matriz.m);
    liberar_matriz(solucion.eigenvector,matriz.m);
    free(solucion.eigenvalor);
    return 0;
}


eigen2 deflacion_potenciainv(double **matriz, int m, int n, double tole){
    eigen2 solucion;
    solucion.eigenvalor=(double *)malloc(m*sizeof(double));
    solucion.eigenvector=crea_matriz(m);


    double error=0, numerador=0, denominador=0, norma=0;
    double *xa= (double *)malloc(m*sizeof(double));
    double *xn= (double *)malloc(m*sizeof(double));
    double *resultado= (double *)malloc(m*sizeof(double));
    double  lambdan=0, lambdaa=0, mag;
    int max_it=0, posicion[m];


    desc_LU(matriz, m, posicion);

    for(int w=0; w<m; w++){
        //inicializar vector vo
        for(int i=0; i<m;i++){
            xa[i]=rand()%100 +1;
        }

        //empieza metodo de la potencia
        do{
            for(int j=0; j<w; j++){
                for(int k=0; k<m;k++){
                    xn[k]=solucion.eigenvector[k][j];
                }
                mag=ppunto(xn,xa,m);
                for(int i=0; i<m;i++){
                    xa[i]=xa[i]-xn[i]*mag;
                }
            }

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

            //realizar producto punto para calcular lambda mas pequeño
            numerador=0;
            denominador=0;
            numerador=ppunto(xn,xa,m);
            denominador=ppunto(xn,xn,m);

            lambdan=numerador/denominador;
            solucion.eigenvalor[w]=lambdan;

            error=mabs(lambdan-lambdaa);
            lambdaa=lambdan;

            for(int i=0; i<m; i++){
                solucion.eigenvector[i][w]=xa[i];
                xa[i]=xn[i];
            }

            max_it++;
        }while (max_it<1000 && error > tole);

    }
    free(xa);
    free(xn);
    free(resultado);

    return solucion;
}
