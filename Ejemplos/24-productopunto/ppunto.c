#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double ppunto(double *a, double *b, int m);

int main (int argc, char *argv[]){

int m=atoi(argv[1]);
    double norma=0;
    int n_cores=atoi(argv[2]);
    double p;

    double *a=(double*)malloc(m*sizeof(double));
    double *b=(double*)malloc(m*sizeof(double));

    //inicializar valores
    /*for(int i=0; i<m; i++){
        a[i]=i;
        b[i]=i;
    }*/

    omp_set_num_threads(n_cores);

   for(int i=0; i<100; i++){
        p=ppunto(a,b,m);
    }


    //printf("Valor: %lf", p);


    free(a);
    free(b);
    return 0;
}

double ppunto(double *a, double *b, int m){
    int c=0;
    #pragma omp parallel for reduction(+:c)
    for(int i=0; i<m; i++){
        c+=a[i]*b[i];
    }
    return c;

}
