#include <stdio.h>
#include <math.h>
#include "matrix.c"
#include "operacion_matriz.c"
double *Jacobi(double **matriz, int m, double tole);

int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz(argc, argv);
    double *resultado, tole=.00000000000001;

    resultado=Jacobi(matriz.A, matriz.m, tole);

    imprime_resultado(resultado, matriz.m);

    liberar_matriz(matriz.A,matriz.m);
    free(resultado);
    return 0;
}

double *Jacobi(double **matriz, int m, double tole){

double norma=0, xa[m], suma=0, error=0;
int d=0, max_it=0;
double *xn=(double *)malloc(m*sizeof(double*));

//comprobar que la matriz es diagonalmente dominante
    for(int i=0; i<m;i++){
        norma=0;
        for(int j=0; j<m;j++){
            if(i!=j){
                norma+=matriz[i][j]*matriz[i][j];
            }
        }
        norma=sqrt(norma);
        if(matriz[i][i]>norma){
            d++;
        }
    }
    if(d==m){
        printf("La matriz es diagonalmente dominante, se garantiza convergencia \n");
    }else {
        printf("La matriz no es diagonalmente dominante, no se garantiza convergencia \n");
    }

///inicializacion de xanterior
    for(int i=0; i<m;i++){
        xa[i]=matriz[i][m];
    }

    do{
        error=0;
        for(int i=0;i<m;i++){
            suma=0;
            for(int j=0; j<m;j++){
                if(i!=j){
                    suma+=matriz[i][j]*xa[j];
                }
         }
            xn[i]=(matriz[i][m]-suma)/matriz[i][i];
            error+=((xn[i]-xa[i])*(xn[i]-xa[i]))/(xn[i]*xn[i]); //calculo del error
        }

        error=sqrt(error);

        //actualizar xanterior
        for(int i=0; i<m;i++){
            xa[i]=xn[i];
        }
        max_it++;//incrementar contador;
    } while(error>tole && max_it<100);

    if(max_it==100){
        printf("El sistema diverge /n");
        free(xn);
        return 0;
    }else {
        printf("Numero de iteraciones: %d \n", max_it);
        return xn;
    }

}
