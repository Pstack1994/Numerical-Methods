#include <stdio.h>
#include <math.h>
#include "matrix.c"
#include "solve.c"
#include "operacion_matriz.c"
#include "EcuacionesL_Metodos.c"



int main(int argc, char* argv[]){
    Matriz matriz;
    matriz=lee_matriz(argc, argv);

    /*double v1[matriz.m], v0[matriz.m], numerador=0, denominador=0, lambdan, lambdav=0,norma=0, tole=1e-9;
    double error=0;
    int posicion[matriz.m], maxit=0;

    desc_LU(matriz.A, matriz.m, posicion);
    for(int i=0; i<matriz.m;i++){
        v0[i]=0;
    }
    v0[0]=1;
    //hacer matriz aumentada con vector inicial v0

    do{
        for(int i=0; i<matriz.m;i++){
         matriz.A[i][matriz.m]=v0[i];
        }

        solv_LU(matriz.A, matriz.m, v1);
        numerador=0;
        denominador=0;
        for(int i=0; i<matriz.m;i++){
            numerador+=v1[i]*v0[i];
            denominador+=v0[i]*v0[i];
        }

        lambdan=numerador/denominador;
        error=mabs(lambdan-lambdav);
        lambdav=lambdan;
        for(int i=0; i<matriz.m; i++){
            v0[i]==v1[i];
            norma+=v0[i]*v0[i];
        }
        norma=sqrt(norma);
        for(int i=0; i<matriz.m; i++){
            v0[i]=v0[i]/norma;
         }
         norma=0;
        maxit++;
    }while(error> tole && maxit<150);
*/
    liberar_matriz(matriz.A,matriz.m);
    return 0;
}
