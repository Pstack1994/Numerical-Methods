#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void suma(double *a, double *b, double *c, int m);

int main (int argc, char *argv[]){

    int m=atoi(argv[1]);
    double norma=0;
    int n_cores=atoi(argv[2]);

    double *a=(double*)malloc(m*sizeof(double));
    double *b=(double*)malloc(m*sizeof(double));
    double *c=(double*)malloc(m*sizeof(double));

    //inicializar valores
    /*for(int i=0; i<m; i++){
        a[i]=i;
        b[i]=i;
    }*/

    omp_set_num_threads(n_cores);

   for(int i=0; i<100; i++){
        suma(a,b,c,m);
    }

   /* for(int i=0; i<m; i++){
        norma+=c[i]*c[i];
    }
    norma=sqrt(norma);

    printf("Norma: %lf", norma);
    */

    free(a);
    free(b);
    free(c);
    return 0;
}

void suma(double *a, double *b, double *c, int m){
    #pragma omp parallel for
    for(int i=0; i<m; i++){
        c[i]=a[i]+b[i];
    }
}
