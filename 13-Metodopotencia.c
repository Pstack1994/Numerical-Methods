#include <stdio.h>
#include <math.h>
#include "matrix.c"
#include "operacion_matriz.c"


eigen metodo_potencia(double **matriz, int m, int n, double tole);
int main(int argc, char* argv[]){
    Matriz matriz;
    eigen solucion;
    matriz=lee_matriz1(argc, argv);
    solucion=metodo_potencia(matriz.A, matriz.m,matriz.n,1e-8);
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
    double  xn[m], error=0, maxa=0, maxn=0, norma=0;
    double xa[m], resultado[m];
    int max_it=0;

    for(int i=0; i<m;i++){
        xa[i]=0;
    }
    xa[0]=1;

    do{

    //norma=0;
    for(int i=0; i<m; i++){
        for(int j=0; j<n;j++){
            resultado[i]=0;
            for(int k=0;k<m;k++){
                  resultado[i]+=matriz[i][k]*xa[k];
            }

        }
       //norma+=resultado[i]*resultado[i];
    }
   // norma=sqrt(norma);
    maxa=maxn;
    double max=mabs(resultado[0]);
    int pos_max=0;
    for(int i=0; i<m;i++){
        if(mabs(resultado[i])>mabs(max)){
            max=resultado[i];
            pos_max=i;
        }
    }
    maxn=max;

    for(int i=0; i<m; i++){
        xa[i]=resultado[i]/max;
        solucion.eigenvector[i]=xa[i];
    }
    error=mabs(maxn-maxa);
    solucion.eigenvalor=maxn;
    max_it++;
    } while (max_it<100 && error > tole);


return solucion;
}
