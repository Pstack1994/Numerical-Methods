#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include<time.h>
#include"matrix.h"
#include "Eigen.h"
#include"operacion_matriz.h"
#include"EcuacionesL_Metodos.h"
#include"solve.h"


eigen metodo_potencia(double **matriz, int m, int n, double tole){
    eigen solucion;
    solucion.eigenvector=(double *)malloc(m*sizeof(double));
    double error=0, numerador=0, denominador=0, norma=0;
    double xa[m], resultado[m], lambdan=0, lambdaa=0;
    int max_it=0;
    srand(time(NULL));
    ///inicilizar vector anterior
    for(int i=0; i<m;i++){
        xa[i]=rand()%100+1;
    }
    /*for(int i=0; i<m; i++){
        xa[i]=matriz[i][m];
    }*/

    do{

        //normalizar xa
        norma=0;
        for(int i=0; i<m; i++){
            norma+=xa[i]*xa[i];
        }
        norma=sqrt(norma);
        for(int i=0; i<m; i++){
            xa[i]=xa[i]/norma;
        }

        //multiplicar vector anterior por matriz
        for(int i=0; i<m; i++){
            for(int j=0; j<n;j++){
                resultado[i]=0;
                for(int k=0;k<m;k++){
                    resultado[i]+=matriz[i][k]*xa[k];
                }
            }
        }
        numerador=0;
        denominador=0;
        //calcular proyecciones con producto punto porque norma es 1
        for(int i=0; i<m; i++){
            numerador+=resultado[i]*resultado[i];
            denominador+=xa[i]*resultado[i];
        }
        //aproximacion del valor propio
        lambdan=numerador/denominador;
        solucion.eigenvalor=lambdan;

        //calculo del error
        error=mabs(lambdan-lambdaa);
        lambdaa=lambdan;

        for(int i=0; i<m; i++){
            solucion.eigenvector[i]=xa[i];
            xa[i]=resultado[i];
        }
        max_it++;
    } while (max_it<100 && error > tole);
    printf("Iteraciones: %d \n", max_it);
    return solucion;
}


eigen potencia_inversa(double **matriz, int m, int n, double tole){
    double  xn[m], error=0, numerador=0, denominador=0, norma=0;
    double xa[m], lambdan=0, lambdaa=0;
    int max_it=0, posicion[m];
    eigen solucion;
    solucion.eigenvector=(double *)malloc(m*sizeof(double));

    ///inicilizar vector anterior
    srand(time(NULL));
    for(int i=0; i<m;i++){
        xa[i]=rand()%100+1;
    }

    //factorizacion LU;
    desc_LU(matriz, m, posicion);

    do{
        //normalizar vector xa
        norma=0;
        for(int i=0; i<m; i++){
            norma+=xa[i]*xa[i];
        }
        norma=sqrt(norma);

        for(int i=0; i<m; i++){
            xa[i]=xa[i]/norma;
        }
        //poner xa en la ultima columna de matriz
        for(int i=0; i<m; i++){
            matriz[i][n]=xa[i];
        }
        //resolver sistema de ecuaciones;
        solv_LU(matriz, m, xn);


        //realizar producto punto para calcular lambda mas pequeño
        numerador=0;
        denominador=0;

        for(int i=0; i<m; i++){
            numerador+=xn[i]*xa[i];
            denominador+=xn[i]*xn[i];
        }

        lambdan=numerador/denominador;
        solucion.eigenvalor=lambdan;

        error=mabs(lambdan-lambdaa);
        lambdaa=lambdan;

        for(int i=0; i<m; i++){
            solucion.eigenvector[i]=xa[i];
            xa[i]=xn[i];
        }

        max_it++;

    }while(max_it<1000 && error>tole);

    printf("max it: %d\n", max_it);

    return solucion;
}

eigen2 potencia_deflacion(double **matriz, int m, int n, double tole){
    eigen2 solucion;
    solucion.eigenvalor=(double *)malloc(m*sizeof(double));
    solucion.eigenvector=crea_matriz2(m,m);


    double error=0, numerador=0, denominador=0, norma=0;
    double *xa= (double *)malloc(m*sizeof(double));
    double *xn= (double *)malloc(m*sizeof(double));
    double *resultado= (double *)malloc(m*sizeof(double));
    double lambdan=0, lambdaa=0;
    int max_it=0;
    double mag;
    srand(time(NULL));

    //ciclo para calcular los m vectores propios mas grandes
    for(int w=0; w<m; w++){
        //inicializar vector vo
        for(int i=0; i<m;i++){
            xa[i]=rand()%100 +1;
        }

        //empieza metodo de la potencia
        do{
            //quitar la proyeccion de los eigenvectores encontrados
            for(int j=0; j<w; j++){
                for(int k=0; k<m;k++){
                    xn[k]=solucion.eigenvector[k][j];
                }
                mag=ppunto(xn,xa,m);
                for(int i=0; i<m;i++){
                    xa[i]=xa[i]-xn[i]*mag;
                }
            }
            //normalizar xa
            norma=0;
            for(int i=0; i<m; i++){
                norma+=xa[i]*xa[i];
            }
            norma=sqrt(norma);
            for(int i=0; i<m; i++){
                xa[i]=xa[i]/norma;
            }

            //multiplicar vector anterior por matriz
            for(int i=0; i<m; i++){
                for(int j=0; j<n;j++){
                    resultado[i]=0;
                    for(int k=0;k<m;k++){
                        resultado[i]+=matriz[i][k]*xa[k];
                    }
                }
            }
            numerador=0;
            denominador=0;
            //calcular proyecciones con producto punto porque norma es 1
            numerador=ppunto(resultado,resultado,m);
            denominador=ppunto(xa,resultado,m);
            //aproximacion del valor propio
            lambdan=numerador/denominador;
            solucion.eigenvalor[w]=lambdan;

            //calculo del error
            error=mabs(lambdan-lambdaa);
            lambdaa=lambdan;

            for(int i=0; i<m; i++){
                solucion.eigenvector[i][w]=xa[i];
                xa[i]=resultado[i];
            }
            max_it++;
        }while (max_it<1000 && error > tole);

    }
    free(xa);
    free(xn);
    free(resultado);

    return solucion;
}

eigen2 deflacion_potenciainv(double **matriz, int m, int n, double tole, int neigen){
    eigen2 solucion;
    solucion.eigenvalor=(double *)malloc(neigen*sizeof(double));
    solucion.eigenvector=crea_matriz2(m, neigen);


    double error=0, numerador=0, denominador=0, norma=0;
    double *xa= (double *)malloc(m*sizeof(double));
    double *xn= (double *)malloc(m*sizeof(double));
    double *resultado= (double *)malloc(m*sizeof(double));
    double  lambdan=0, lambdaa=0, mag;
    int max_it=0, posicion[m];


    desc_LU(matriz, m, posicion);

    for(int w=0; w<neigen; w++){
        //inicializar vector vo
        for(int i=0; i<m;i++){
            xa[i]=rand()%100 +1;
        }

        //empieza metodo de la potencia
        do{
            for(int j=0; j<w; j++){
                for(int k=0; k<m;k++){
                    xn[k]=solucion.eigenvector[k][j];
                }
                mag=ppunto(xn,xa,m);
                for(int i=0; i<m;i++){
                    xa[i]=xa[i]-xn[i]*mag;
                }
            }

            //normalizar vector xa
            norma=0;
            for(int i=0; i<m; i++){
                norma+=xa[i]*xa[i];
            }
            norma=sqrt(norma);

            for(int i=0; i<m; i++){
                xa[i]=xa[i]/norma;
            }
            //poner xa en la ultima columna de matriz
            for(int i=0; i<m; i++){
                matriz[i][n]=xa[i];
            }
            //resolver sistema de ecuaciones;
            solv_LU(matriz, m, xn);

            //realizar producto punto para calcular lambda mas pequeño
            numerador=0;
            denominador=0;
            numerador=ppunto(xn,xa,m);
            denominador=ppunto(xn,xn,m);

            lambdan=numerador/denominador;
            solucion.eigenvalor[w]=lambdan;

            error=mabs(lambdan-lambdaa);
            lambdaa=lambdan;

            for(int i=0; i<m; i++){
                solucion.eigenvector[i][w]=xa[i];
                xa[i]=xn[i];
            }
            max_it++;
        }while (max_it<1000 && error > tole);

    }
    free(xa);
    free(xn);
    free(resultado);

    return solucion;
}

eigen2 Jacobi_Eigen(double **matriz, double tole, int m){
matriz_elemento maximo;
    eigen2 solucion;
    double theta, numerador, denominador;
    int max_it=0;

    solucion.eigenvector=crea_matriz(m);
    solucion.eigenvalor= (double*)malloc(m*sizeof(double));

    //inicializar identidad
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){

            if(i==j){
                solucion.eigenvector[i][j]=1;
            }else{
                solucion.eigenvector[i][j]=0;
            }

        }
    }

do{
        //encontrar maximo fuera de la diagonal
        maximo=find_max_od(matriz, m, m);
        int i=maximo.pos_i;
        int j=maximo.pos_j;

        numerador=2*(matriz[i][j]);
        denominador=matriz[i][i]- matriz[j][j];

        //calcular angulo de la rotacion con las posiciones del maximo
        theta=0.5*atan(numerador/denominador);

        double aux1, aux2;
        for(int l=0; l<m; l++){
            aux1=matriz[l][i]*cos(theta)+matriz[l][j]*sin(theta);
            aux2=-matriz[l][i]*sin(theta)+matriz[l][j]*cos(theta);
            matriz[l][j]=aux2;
            matriz[l][i]=aux1;
            aux1=solucion.eigenvector[l][i]*cos(theta)+solucion.eigenvector[l][j]*sin(theta);
            aux2=-solucion.eigenvector[l][i]*sin(theta)+solucion.eigenvector[l][j]*cos(theta);
            solucion.eigenvector[l][j]=aux2;
            solucion.eigenvector[l][i]=aux1;
        }


        for(int k=0; k< m; k++){
            aux1=matriz[i][k]*cos(theta)+matriz[j][k]*sin(theta);
            aux2=-matriz[i][k]*sin(theta)+matriz[j][k]*cos(theta);
            matriz[j][k]=aux2;
            matriz[i][k]=aux1;
        }

        max_it++;

    }while(maximo.max>tole && max_it <20000);

    for(int i=0; i<m; i++){
        solucion.eigenvalor[i]=matriz[i][i];
    }
    printf("iteraciones: %d\n", max_it);

    return solucion;
}

eigen2 metodo_QR(double **matriz, double **r, int m, int n, double tole){
    matriz_elemento maximo;
    eigen2 solucion;
    double ** resultado, **eigenvector;
    int max_it=0;
    resultado=crea_matriz2(m,n);
    eigenvector=crea_matriz2(m,n);
    solucion.eigenvector=crea_matriz2(m,n);
    solucion.eigenvalor=(double*)malloc(m*sizeof(double));

    double **temp;
    for(int i=0; i<m;i++){
        solucion.eigenvector[i][i]=1;
        for(int j=0; j<n; j++){
            if(i!=j){
                solucion.eigenvector[i][j]=0;
            }
        }
    }

    do{
        factoriza_QR(matriz, r, m, n);

        matrix_multiply_mmd(solucion.eigenvector,matriz,eigenvector,m,n,n);
        matrix_multiply_mmd(r,matriz,resultado,m,n,n);

        temp=resultado;
        resultado=matriz;
        matriz=temp;

        temp=eigenvector;
        eigenvector=solucion.eigenvector;
        solucion.eigenvector=temp;

        maximo=find_max_od(matriz, m, n);
        max_it++;
    }while(mabs(maximo.max)>tole && max_it<10000);

    for(int i=0; i<m; i++){
        solucion.eigenvalor[i]=matriz[i][i];
    }

    printf("converge en: %d\n", max_it);
    liberar_matriz(resultado, m);
    liberar_matriz(eigenvector,m);

    return solucion;
}
