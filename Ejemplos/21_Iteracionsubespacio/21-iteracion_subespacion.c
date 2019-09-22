#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../../matrix.h"
#include "../../operacion_matriz.h"
#include "../../solve.h"
#include "../../EcuacionesL_Metodos.h"
#include"../../Eigen.h"

eigen2 iteracion_subespacio(double** matriz, int m, int n, int tp, double tole );

int main(int argc, char *argv[]){
    Matriz matriz;
    matriz=lee_matriz1(argc, argv);
    eigen2 solucion;

    solucion=iteracion_subespacio(matriz.A,matriz.m,matriz.n,5,1e-9);
    printf("Los eigenvalores son: \n");
    imprime_resultado(solucion.eigenvalor,5);
    printf("\nLos eigenvectores son: \n");
    imprime_matrizc(solucion.eigenvector, matriz.m,5);

    liberar_matriz(matriz.A,matriz.m);
    liberar_matriz(solucion.eigenvector,matriz.m);
    free(solucion.eigenvalor);
    return 0;
}

eigen2 iteracion_subespacio(double** matriz, int m, int n, int tp, double tole ){
    matriz_elemento maximo;
    eigen2 solucion;

    double **r, **resultado, **temp, **pt, **diagonal;
    int max_it=0;
    r=crea_matriz2(tp,tp);
    solucion.eigenvector=crea_matriz2(m,tp);
    pt=crea_matriz2(tp,m);
    diagonal=crea_matriz2(tp,tp);
    resultado=crea_matriz2(m,tp);
    solucion.eigenvalor=(double*)malloc(tp*sizeof(double));

    //inicializar solucion.eigenvector con un valor aleatrio
    srand(time(NULL));
    for(int i=0; i<m;i++){
        for(int j=0; j<tp;j++){
            solucion.eigenvector[i][j]=rand()%100+1;
        }
    }


   do{
        //factorizar solucion.eigenvector
        factoriza_QR(solucion.eigenvector,r,m,tp);

        multiplica_matrices(matriz,solucion.eigenvector,resultado,m,m,tp);

        for(int i=0; i<tp;i++){
            for(int j=0; j<m;j++){
                pt[i][j]=solucion.eigenvector[j][i];
            }
        }

        temp=resultado;
        resultado=solucion.eigenvector;
        solucion.eigenvector=temp;

        multiplica_matrices(pt,solucion.eigenvector,diagonal,tp,m,tp);

        maximo=find_max_od(diagonal, tp, tp);
        max_it++;
   }while(mabs(maximo.max)>tole && max_it<10000);

    for(int i=0; i<tp;i++){
        solucion.eigenvalor[i]=diagonal[i][i];
    }

    printf("convergio en: %d iteraciones",max_it);
    printf("\n");

    liberar_matriz(diagonal, tp);
    liberar_matriz(r,tp);
    liberar_matriz(resultado,m);
    liberar_matriz(pt,tp);
    return solucion;
}
