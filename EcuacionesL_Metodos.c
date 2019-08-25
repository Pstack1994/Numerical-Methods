#include <stdio.h>
#include <stdlib.h>

///////////////////////metodos para resolver sistemas de ecuaciones lineales//////////////////////////////

double G_sinpivoteo(double**matriz, int m, int n, double *resultado);
double G_pivoteo(double**matriz, int m, int n, double *resultado);
void desc_LU(double **matriz, int m, int *posicion);
void solv_LU(double **matrizLU,int m, double *resultado);
double ** inversa_LU(double **matriz, int m, int *posicion);
double ** Mod_Cholesky(double **matriz,int m, int n);
void solv_Mod_Cholesky(double **cholesky, int m, double *resultado);

///////////////////////Gauss sin pivoteo//////////////////////////////////////////////////////
double G_sinpivoteo(double**matriz, int m, int n, double *resultado){
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

        for(int i=n; i>=0;i--){//dividir el renglon r entre el valor del pivote
            matriz[r][i]= (matriz[r][i])*(1/matriz[r][c]);
        }

        for(int i=r+1;i<m;i++){
            if(matriz[i][c]!=0){
                for(int j=n;j>=0;j--){
                    matriz[i][j]=matriz[i][j]-matriz[i][c]*matriz[r][j];//eliminar los elementos por debajo del pivote
                }
            }

        }

            r++;
        c++;
}
    solv_tsup(matriz, m, resultado);
    det=s*det;
    return det;
}

/////////////gauss con pivoteo/////////////////////////////////////////////////////////////////
double G_pivoteo(double**matriz, int m, int n, double *resultado){
    int posicion[n];//vector en donde se conservaran las posiciones de las soluciones en los cambios de columna
    int r=0, c=0, r2=0, c2=0, aux=0, s=1;//r=renglones, c=columnas, (r2 y c2)=renglon y columna para intercambiar. s=signo det.
    double max=0, det=1; //max=maximo valor de la matriz, det= determinante.

//ciclo para inicializar las posiciones
    for(int i=0; i<n;i++){
        posicion[i]=i;
    }
//while para recorrer todas los renglones de la matriz
    while (r<m){
        //Encuentra el valor máximo de la matriz
        max=find_max(matriz, m, n, r,c,&r2,&c2);
        if(mabs(matriz[r][c])!= max){//si el valor absoluto del pivote es diferente del máximo de la matriz intercambia.
            if(r!=r2){
                cambia_renglon(matriz, n, r,r2);
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

        for(int i=n; i>=0;i--){
            matriz[r][i]= (matriz[r][i])*(1/matriz[r][c]);// se divide el renglon r entre el pivote
        }

        for(int i=r+1;i<m;i++){
            if(matriz[i][c]!=0){
                for(int j=n;j>=0;j--){
                    matriz[i][j]=matriz[i][j]-matriz[i][c]*matriz[r][j];//se eliminan los elementos debajo del pivote
                }
            }
        }
            r++; //se aumentan el valor del renglon
        c++;// se aumeta el valor de la columna

    }

    solv_tsup(matriz, m, resultado);

    double maux;
    int pos;

    for(int i=0; i<m; i++){//regresar los valores de los resultados a las posiciones correspondientes.
        for(int j=0; j<m; j++){
            if(i==posicion[j]){
                maux=resultado[j];
                resultado[j]=resultado[i];
                resultado[i]=maux;
                pos=posicion[i];
                posicion[i]=posicion[j];
                posicion[j]=pos;
            }
        }
    }
    det=s*det;
    return det;
}
//descomposicion LU////////////////////////////////////////////////
void desc_LU(double **matriz, int m, int *posicion){
int k1, r2=1, aux=0;
double respaldo[m+1];

for(int i=0; i<m;i++){
    posicion[i]=i;
}
for(int i=0; i<m;i++){
        respaldo[m]=matriz[i][m];
        for(int j=0; j<m;j++){
            respaldo[j]=matriz[i][j];
            if(j==0 && i!=0){
               matriz[i][0]=matriz[i][0]/matriz[0][0];
               continue;//se salta todo lo que está abajo.
            }
            if(i==0){
                continue;//se salta todo lo que está abajo.
            }

            if(j<i){
                k1=j;//cambia los limites de la suma del for de abajo.
            }
            if(j>=i){
                k1=i;//cambia los limites de la suma del for de abajo.
            }

            for(int k=0; k<k1;k++){
                matriz[i][j]-=matriz[i][k]*matriz[k][j];
            }
            if(j<i){
                matriz[i][j]/=matriz[j][j];
            }
        }
        if(matriz[i][i]==0 && i<m-1){//pivote es igual a cero
            if(i+r2>=m){printf("El sistema no tiene solucion");return;}
            for(int k=0; k<=m;k++){
                matriz[i][k]=matriz[i+r2][k];
                matriz[i+r2][k]=respaldo[k];
            }
            aux=posicion[i];
            posicion[i]=posicion[i+r2];
            posicion[i+r2]=aux;
            r2++;
            i--;
            continue;
        }

         r2=1;

    }

   /* printf("\n");
    imprime_matrizc(matriz,m);
    printf("\n");*/
}
////////////solucionar LU/////////////////////////////////////////////////
void solv_LU(double **matrizLU,int m, double *resultado){
    double respaldo_diag[m];
    for(int i=0;i<m;i++){
        respaldo_diag[i]=matrizLU[i][i];//crear respaldo para no perder los valores de la diagonal
        matrizLU[i][i]=1;
    }

    solv_tinf(matrizLU,m,resultado);//resolver ly=b
    for(int i=0; i<m;i++){
        matrizLU[i][i]=respaldo_diag[i];
        matrizLU[i][m]=resultado[i];//intercambiar valores de la ultima columna por los resultados de resolver ly=b
    }
    solv_tsup(matrizLU,m,resultado);//resolver ux=y
}

double ** inversa_LU(double **matriz, int m,int *posicion){
    double resultado[m];
    double auxiliar[m];
    double **identidad=crea_matriz(m);
    for(int i=0;i<m;i++){
        for(int j=0; j<m; j++){
            if(i==j){
                identidad[i][j]=1;
            }
            else{
                identidad[i][j]=0;
            }
        }
    }

   for(int i=0;i<m;i++){
        for(int j=0; j<m; j++){
            auxiliar[j]=identidad[j][i];
            if(posicion[i]!=i){
                identidad[j][i]=identidad[i][posicion[j]];
                identidad[i][posicion[j]]=auxiliar[j];
                //posicion[i]=i;
            }
        }
    }

    double respaldo_diag[m];

    for(int i=0;i<m;i++){
    respaldo_diag[i]=matriz[i][i];//crear respaldo para no perder los valores de la diagonal
    matriz[i][i]=1;
    }

    for(int i=0;i<m;i++){// resolver LY=I

        for(int j=0; j<m; j++){
            matriz[j][m]=identidad[j][i];
        }
        solv_tinf(matriz,m,resultado);
        for(int k=0; k<m;k++){
            identidad[k][i]= resultado[k];
        }
    }


    for(int i=0; i<m;i++){
        matriz[i][i]=respaldo_diag[i];//respaldar la diagonal
    }

    for(int i=0;i<m;i++){ //Resolver UX=Y
        for(int j=0; j<m; j++){
            matriz[j][m]=identidad[j][i];
        }
        solv_tsup(matriz,m,resultado);

        for(int k=0; k<m;k++){
            identidad[k][i]= resultado[k];
        }
    }

    return identidad;
}
//////////////////////CHOLESKY MODIFICADO////////////////////////////////////////////////////////
double ** Mod_Cholesky(double **matriz,int m, int n){
if(n!=m){
    printf("No es una matriz cuadrada, no se puede aplicar este metodo");
    liberar_matriz(matriz, m);
    exit(EXIT_FAILURE);
}
for(int i=0; i<m;i++){
    for(int j=0;j<m;j++){
        if(matriz[i][j]!=matriz[j][i]){
            printf("No es una matriz simetrica, no se puede aplicar este metodo");
            liberar_matriz(matriz, m);
            exit(EXIT_FAILURE);
        }

    }
}

for(int i=0;i<m;i++){
        for(int j=0; j<n;j++){
            if(i==j){
                for(int k=0;k<i;k++){
                    matriz[i][j]-=matriz[i][k]*matriz[i][k]*matriz[k][k];
                }
            }

            if (i>j){
                for(int k=0; k<j; k++){
                    matriz[i][j]-=matriz[j][k]*matriz[i][k]*matriz[k][k];
                }
                matriz[i][j]/=matriz[j][j];
            }

        }
    }

    for(int i=0; i<m;i++){
        for(int j=0; j<n; j++){
              if(i<j){
               matriz[i][j]=matriz[j][i];
            }

        }
    }
    return matriz;
}

void solv_Mod_Cholesky(double **cholesky, int m, double *resultado){

 for(int i=1; i<m; i++){
        for(int j=0;j<i;j++){
            cholesky[i][j]*=cholesky[j][j];
        }
    }
    solv_tinf(cholesky,m,resultado);

    for(int i=0;i<m;i++){
        cholesky[i][i]=1;
        cholesky[i][m]=resultado[i];
    }
   solv_tsup(cholesky,m,resultado);
}
