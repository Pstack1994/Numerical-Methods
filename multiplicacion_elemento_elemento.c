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
double matriz_vector(double **a, double *b, double *c, int m, int n);
void multiplica_matrices(double **a, double **b, double** c, int arenglones, int acolumnas, int bcolumnas);

int main (){
    for(int r=0; r<10; r++){
        int m=pow(10,r);
        double *a=malloc(m*sizeof(double));
        double *b=malloc(m*sizeof(double));
        double *c=malloc(m*sizeof(double));

        srand(time(NULL));
        omp_set_num_threads(4);

        for(int i=0; i<m; i++){
            a[i]=rand()%10;
            b[i]=rand()%10;
        }

        clock_t inicio=clock();
        //for(int i=0; i<100; i++){
        suma(a,b,c,m);
        //}
       float tiempo= (clock()-inicio)*1000/CLOCKS_PER_SEC;

        printf("tiempo: %f",tiempo );


        /*for(int i=0; i<m; i++){
            printf("%lf ", c[i]);
        }*/


        free(a);
        free(b);
        free(c);
    }
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

double matriz_vector(double **a, double *b, double *c, int m, int n){
    #pragma omp parallel for
    for(int i=0; i<m; i++){
        int aux=0;
        for(int j=0; j<n; j++){
            aux+=a[i][j]*b[j];
        }
        c[i]=aux;
    }
}

void multiplica_matrices(double ** a, double ** b, double ** c, int arenglones, int acolumnas, int bcolumnas) {
    double ** a_i = a;
    double ** b_i = b;
    double ** c_i = c;

    for (int i=0; i<arenglones; i++, a_i++, b_i++, c_i++) {
        double **b_k = b;
        double *a_ik = *a_i;
        memset(*c_i, 0, bcolumnas*sizeof(double));
        for (int k = 0; k < acolumnas; k++, a_ik++, b_k++) {
            double *b_kj = *b_k;
            double *c_ij = *c_i;
            for (int j=0; j<bcolumnas; j++, b_kj++, c_ij++) {
                *c_ij +=(*a_ik)*(*b_kj);
            }
        }
    }
}
