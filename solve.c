#include <stdio.h>
#include<stdlib.h>

void imprime_matrizc(double **matriz, int m);
void imprime_resultado(double *resultado, int m);
double mabs(double a);
void *cambia_renglon(double**matriz,int m, int r1, int r2);
void *cambia_columna(double**matriz,int m, int c1, int c2);
double find_maxr(double **matriz, int m,int r, int c, int *r2);
double find_max(double **matriz, int m,int r, int c , int *r2, int *c2);
void *solv_diagonalinf(double **matriz,int m, double *resultado);
double det_diagonalinf(double **matriz, int m);
void *solv_diagonalsup(double **matriz, int m, double *resultado);
double det_diagonalsup(double **matriz, int m);
double GJ_sinpivoteo(double**matriz, int m, double *resultado);
double GJ_pivoteo(double**matriz, int m, double *resultado);


void imprime_matrizc(double **matriz, int m){
    for (int i=0; i<m;i++){
        for(int j=0; j<=m;j++){
            printf("%lf ",matriz[i][j]);
        }
        printf("\n");
    }
}

void imprime_resultado(double *resultado, int m){
    printf("El resultado es: ");
    for(int i=0; i<m;i++){
        printf("%lf ", resultado[i]);
    }
}

double mabs(double a){
return (a<0)? -a:a;//calcular el valor absoluto
}
void *cambia_renglon(double**matriz,int m, int r1,int r2){
    double cambia=0;
    for(int i=0;i<=m;i++){
        cambia=matriz[r1][i];
        matriz[r1][i]=matriz[r2][i];
        matriz[r2][i]=cambia;
    }
}

void *cambia_columna(double**matriz,int m, int c1,int c2){
    double cambia=0;
    for(int i=0;i<m;i++){
        cambia=matriz[i][c1];
        matriz[i][c1]=matriz[i][c2];
        matriz[i][c2]=cambia;
    }
}

double find_maxr(double **matriz, int m,int r, int c, int *r2){//encontrar el maximo de una columna de una matriz
    double max=abs(matriz[r][c]);//inicializar el máximo con el valor del pivote en donde estamos
    for(int i=r; i<m;i++){
        if(abs(matriz[i][c])>abs(max)){max=matriz[i][c];*r2=i;}//r2=posicion del valor máximo.
    }
    return max;
}

double find_max(double **matriz, int m,int r, int c, int *r2, int *c2){//encuentra el máximo elemento de una matriz
    double max=mabs(matriz[r][c]);//inicializar en el pivote en el que estamos
    for(int i=r; i<m;i++){
        for(int j=c;j<m;j++){
            if(mabs(matriz[i][j])>mabs(max)){
                max=mabs(matriz[i][j]);
                *r2=i; *c2=j;// posición en renglones y columnas del maximo
            }
        }
    }
    return max;
}

void *solv_diagonalinf(double **matriz,int m, double *resultado){//resuelve una matriz triangular inferior
    double suma=0, c=0;
    resultado[0]=matriz[0][m]/matriz[0][0];
    for(int i=1; i<m;i++){
        suma=0;
        for(int j=0; j<i;j++){
            suma+=matriz[i][j]*resultado[j];
        }
        resultado[i]=(matriz[i][m]-suma)/matriz[i][i];
    }
}

double det_diagonalinf(double **matriz, int m){
    double resultado;
    resultado=matriz[0][0];
    for(int i=1;i<m;i++){
        resultado*=matriz[i][i];
    }
    return resultado;
}

void *solv_diagonalsup(double **matriz, int m, double *resultado){
    double suma=0;
    resultado[m-1]=matriz[m-1][m]/matriz[m-1][m-1];
    for(int i=2; i<=m;i++){
            suma=0;
        for(int j=1; j<i;j++){
            suma+= matriz[m-i][m-j]*resultado[m-j];
        }
        resultado[m-i]=(matriz[m-i][m]-suma)/matriz[m-i][m-i];
    }
}

double det_diagonalsup(double **matriz, int m){
    double resultado;
    resultado=matriz[0][0];
    for(int i=1;i<m;i++){
        resultado*=matriz[i][i];
    }

    return resultado;
}

// Gauss sin pivoteo
double GJ_sinpivoteo(double**matriz, int m, double *resultado){
int r=0, c=0, r2=0, s=1;//r=renglomnes, c=columnas, r2=renglon por el cual se intercambiará, s=signo del determinante.
double max, det=1;//max=máximo de la columna c, det=determinante.

    while (r<m){//recorrer todos los renglones de la matriz
        if(matriz[r][c]==0){//verificar que pivote no sea 0
            max=find_maxr(matriz,m,r,c,&r2);//encontrar maximo de la columna m
            if(max==0){printf("El sistema no tiene solucion o tiene infinitas soluciones");return 0;}
            if(matriz[r][c]!= max){//si el valor del máximo es diferente al valor del pivote intercambiar los renglones
                cambia_renglon(matriz, m, r,r2);
                s*=-1;//conservar el signo del determinante
            }
        }
        det*=matriz[r][c];//se calcula el determinante multiplicando el valor de los pivotes

        for(int i=m; i>=0;i--){//dividir el renglon r entre el valor del pivote
            matriz[r][i]= (matriz[r][i])*(1/matriz[r][c]);
        }

        for(int i=r+1;i<m;i++){
            if(matriz[i][c]!=0){
                for(int j=m;j>=0;j--){
                    matriz[i][j]=matriz[i][j]-matriz[i][c]*matriz[r][j];//eliminar los elementos por debajo del pivote
                }
            }

        }

            r++;
        c++;
}
    solv_diagonalsup(matriz, m, resultado);
    det=s*det;
    return det;
}

//gauss con pivoteo
double GJ_pivoteo(double**matriz, int m,double *resultado){
    int posicion[m];//vector en donde se conservaran las posiciones de las soluciones en los cambios de columna
    int r=0, c=0, r2=0, c2=0, aux=0, s=1;//r=renglones, c=columnas, (r2 y c2)=renglon y columna para intercambiar. s=signo det.
    double max=0, det=1; //max=maximo valor de la matriz, det= determinante.

//ciclo para inicializar las posiciones
    for(int i=0; i<m;i++){
        posicion[i]=i;
    }
//while para recorrer todas los renglones de la matriz
    while (r<m){
        //Encuentra el valor máximo de la matriz
        max=find_max(matriz, m, r,c,&r2,&c2);
        if(mabs(matriz[r][c])!= max){//si el valor absoluto del pivote es diferente del máximo de la matriz intercambia.
            if(r!=r2){
                cambia_renglon(matriz, m, r,r2);
                s*=-1;
            }
            if(c!=c2){
                cambia_columna(matriz,m,c,c2);
                s*=-1;//cada cambio de renglon o columna cambia el signo del determinante.
                aux=posicion[c];//cambiar los valores para mantener el orden de la solucion.
                posicion[c]=posicion[c2];
                posicion[c2]=aux;
            }
        }
        det*=matriz[r][c]; //se calcula el determinante al multiplicar los pivotes de la matriz.
        for(int i=m; i>=0;i--){
            matriz[r][i]= (matriz[r][i])*(1/matriz[r][c]);// se divide el renglon r entre el pivote
        }

        for(int i=r+1;i<m;i++){
            if(matriz[i][c]!=0){
                for(int j=m;j>=0;j--){
                    matriz[i][j]=matriz[i][j]-matriz[i][c]*matriz[r][j];//se eliminan los elementos debajo del pivote
                }
            }
        }
            r++; //se aumentan el valor del renglon
        c++;// se aumeta el valor de la columna

    }

    solv_diagonalsup(matriz, m, resultado);

    double maux;
    for(int i=0; i<m; i++){//regresar los valores de los resultados a las posiciones correspondientes.
        if(posicion[i]!=i){

            maux=resultado[i];
            resultado[i]=resultado[posicion[i]];
            resultado[posicion[i]]=maux;
            posicion[posicion[i]]=posicion[i];
            posicion[i]=i;
        }
    }
    det=s*det;
    return det;
}
