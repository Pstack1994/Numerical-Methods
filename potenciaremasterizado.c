#include <stdio.h>
#include "matrix.c"
#include <math.h>
#include <time.h>
#include "operacion_matriz.c"

eigen metodo_potencia(double **matriz, int m, int n, double tole);

int main(int argc, char* argv[]){
    Matriz matriz;
    eigen solucion;
    matriz=lee_matriz1(argc, argv);
    solucion=metodo_potencia(matriz.A, matriz.m,matriz.n,2.22045e-14);
    printf("Eigen valor: %lf", solucion.eigenvalor);
    printf("\n");
    printf("Eigen vector: ");
    for(int i=0; i<matriz.m;i++){
        printf("%lf, ", solucion.eigenvector[i]);
    }
    liberar_matriz(matriz.A,matriz.m);
    free(solucion.eigenvector);
    return 0;
}
eigen metodo_potencia(double **matriz, int m, int n, double tole){
    eigen solucion;
    solucion.eigenvector=(double *)malloc(m*sizeof(double));
    double  xn[m], error=0, numerador=0, denominador=0, norma=0;
    double xa[m], resultado[m], lambdan=0, lambdaa=0;
    int max_it=0;
    srand(time(NULL));
    ///inicilizar vector anterior
    for(int i=0; i<m;i++){
        xa[i]=rand()%100+1;
    }

    do{

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

        for(int i=0; i<m; i++){
            numerador+=resultado[i]*resultado[i];
            denominador+=xa[i]*resultado[i];
        }
        lambdan=numerador/denominador;
        solucion.eigenvalor=lambdan;

        error=mabs(lambdan-lambdaa);
        lambdaa=lambdan;

        for(int i=0; i<m; i++){
            solucion.eigenvector[i]=xa[i];
            xa[i]=resultado[i];
        }
        max_it++;
    } while (max_it<1000 && error > tole);
    printf("%d \n", max_it);
    return solucion;
}
