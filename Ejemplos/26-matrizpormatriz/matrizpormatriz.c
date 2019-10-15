#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void multiplicacion(double **matriz, double **matriz2, double **matriz3, int m, int n, int p, int q);


int main (int argc, char *argv[]){

    int m=atoi(argv[1]);
    int n_cores=atoi(argv[2]);

    double **matriz=(double**)malloc(m*sizeof(double*));
    double **matriz2=(double**)malloc(m*sizeof(double*));
    double **matriz3=(double**)malloc(m*sizeof(double*));

    for(int i=0; i<m;i++){
        matriz[i]=(double *)malloc((m)*sizeof(double));
        matriz2[i]=(double *)malloc((m)*sizeof(double));
        matriz3[i]=(double *)malloc((m)*sizeof(double));
    }

    omp_set_num_threads(n_cores);

    multiplicacion(matriz,matriz2,matriz3,m,m,m,m);


    for(int i=0;i<m;i++){
        free(matriz[i]);
        free(matriz2[i]);
        free(matriz3[i]);
    }
    free(matriz);
    free(matriz2);
    free(matriz3);
    return 0;
}


void multiplicacion(double **matriz, double **matriz2, double **matriz3, int m, int n, int p, int q){

  #pragma omp parallel for
    for(int i=0; i<m; i++){
        for(int j=0; j<n;j++){
           int aux=0;
            for(int k=0;k<p;k++){
                  aux+=matriz[i][k]*matriz2[k][j];
            }
            matriz3[i][j]=aux;
        }
    }

}
