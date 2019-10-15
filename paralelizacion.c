#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <omp.h>

//no pasrme de matrices de 8 mil * 8mil
void suma(double *a, double *b, double *c, int m);
void multiplica (double *a, double *b, double *c, int m);
double ppunto(double *a, double *b, int m);
void matriz_vector(double **a, double *b, double *c, int m, int n);
void multiplicacion(double **matriz, double **matriz2, double **matriz3, int m, int n, int p, int q);


int main (int argc, char *argv[]){

    int m=atoi(argv[1]);
    int n_cores=atoi(argv[2]);

   /* double *a=(double*)malloc(m*sizeof(double));
    double *b=(double*)malloc(m*sizeof(double));
    double *c=(double*)malloc(m*sizeof(double));*/

    double **matriz=(double**)malloc(m*sizeof(double*));
    double **matriz2=(double**)malloc(m*sizeof(double*));
    double **matriz3=(double**)malloc(m*sizeof(double*));
    for(int i=0; i<m;i++){
        matriz[i]=(double *)malloc((m)*sizeof(double));
        matriz2[i]=(double *)malloc((m)*sizeof(double));
        matriz3[i]=(double *)malloc((m)*sizeof(double));
    }

    //srand(time(NULL));
    omp_set_num_threads(n_cores);

    /*for(int i=0; i<m; i++){
        a[i]=rand()%10;
        b[i]=rand()%10;
    }*/

   // for(int i=0; i<100; i++){
        multiplicacion(matriz,matriz2,matriz3,m,m,m,m);
    //}


    for(int i=0;i<m;i++){
        free(matriz[i]);
        free(matriz2[i]);
        free(matriz3[i]);
    }
    free(matriz);
    free(matriz2);
    free(matriz3);
    //free(a);
    //free(b);
    //free(c);
    return 0;
}

void suma(double *a, double *b, double *c, int m){
    #pragma omp parallel for
    for(int i=0; i<m; i++){
        c[i]=a[i]+b[i];
    }
}
void multiplica(double *a, double *b, double *c, int m){

    #pragma omp parallel for
    for(int i=0; i<m; i++){
        int aux;
        aux=a[i]*b[i];
        c[i]=aux;
    }
}

double ppunto(double *a, double *b, int m){
    int c=0;
    #pragma omp parallel for reduction(+:c)
    for(int i=0; i<m; i++){
        c+=a[i]*b[i];
    }
    return c;

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
