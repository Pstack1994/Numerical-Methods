#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void matriz_vector(double **a, double *b, double *c, int m, int n);



int main (int argc, char *argv[]){
    int m=atoi(argv[1]);
    int n_cores=atoi(argv[2]);
    double norma=0;

    double *a=(double*)malloc(m*sizeof(double));
    double *c=(double*)malloc(m*sizeof(double));

    double **matriz=(double**)malloc(m*sizeof(double*));

    for(int i=0; i<m;i++){
        matriz[i]=(double *)malloc((m)*sizeof(double));
    }

    omp_set_num_threads(n_cores);

    for(int i=0; i<100; i++){
        matriz_vector(matriz, a, c, m ,m);
    }


   /*for(int i=0; i<m; i++){
        norma+=c[i]*c[i];
    }
    norma=sqrt(norma);

    printf("Norma: %lf", norma);
    */


    for(int i=0;i<m;i++){
        free(matriz[i]);
    }
    free(matriz);
    free(a);
    free(c);
    return 0;

}

void matriz_vector(double **a, double *b, double *c, int m, int n){
    #pragma omp parallel for
    for(int i=0; i<m; i++){
        int aux=0;
        for(int j=0; j<n; j++){
            aux+=a[i][j]*b[j];
        }
        c[i]=aux;
    }
}
