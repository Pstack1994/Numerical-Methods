
#include <stdio.h>
#include <math.h>
#include "../../matrix.h"
#include "../../operacion_matriz.h"
#include <stdlib.h>
#include<time.h>


eigen2 metodo_potencia1(double **matriz, int m, int n, double tole);

int main(int argc, char* argv[]){
    Matriz matriz;
    eigen2 solucion;
    matriz=lee_matriz1(argc, argv);
    solucion=metodo_potencia1(matriz.A, matriz.m,matriz.n,1e-8);
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


eigen2 metodo_potencia1(double **matriz, int m, int n, double tole){
    eigen2 solucion;
    solucion.eigenvalor=(double *)malloc(m*sizeof(double));
    solucion.eigenvector=crea_matriz2(m,m);


    double error=0, numerador=0, denominador=0, norma=0;
    double *xa= (double *)malloc(m*sizeof(double));
    double *xn= (double *)malloc(m*sizeof(double));
    double *resultado= (double *)malloc(m*sizeof(double));
    double lambdan=0, lambdaa=0;
    int max_it=0;
    double mag;
    srand(time(NULL));

    //ciclo para calcular los m vectores propios mas grandes
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
            //normalizar xa
            norma=0;
            for(int i=0; i<m; i++){
                norma+=xa[i]*xa[i];
            }
            norma=sqrt(norma);
            for(int i=0; i<m; i++){
                xa[i]=xa[i]/norma;
            }

            //multiplicar vector anterior por matriz
            for(int i=0; i<m; i++){
                for(int j=0; j<n;j++){
                    resultado[i]=0;
                    for(int k=0;k<m;k++){
                        resultado[i]+=matriz[i][k]*xa[k];
                    }
                }
            }
            numerador=0;
            denominador=0;
            //calcular proyecciones con producto punto porque norma es 1
            numerador=ppunto(resultado,resultado,m);
            denominador=ppunto(xa,resultado,m);
            //aproximacion del valor propio
            lambdan=numerador/denominador;
            solucion.eigenvalor[w]=lambdan;

            //calculo del error
            error=mabs(lambdan-lambdaa);
            lambdaa=lambdan;

            for(int i=0; i<m; i++){
                solucion.eigenvector[i][w]=xa[i];
                xa[i]=resultado[i];
            }
            max_it++;
        }while (max_it<1000 && error > tole);

    }
    free(xa);
    free(xn);
    free(resultado);

    return solucion;
}
