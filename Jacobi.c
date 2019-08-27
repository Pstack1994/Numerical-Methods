#include <stdio.h>
#include <math.h>

int main(){
    int m=3;
    double a[m][m+1], xa[m], xn[m], tole=.000001, suma=0, aux=0;
    int max;

    printf("ingresalos valores de la matriz: \n");
    for(int i=0; i<m;i++){
        for(int j=0; j<=m;j++){
            scanf("%lf", &a[i][j]);
        }
    }
    ///inicializacion de xanterior
    for(int i=0; i<m;i++){
        xa[i]=a[i][m];
    }

    do{
        aux=0;
        for(int i=0;i<m;i++){
            suma=0;
            for(int j=0; j<m;j++){
                if(i!=j){
                    suma+=a[i][j]*xa[j];
                }
         }
            xn[i]=(a[i][m]-suma)/a[i][i];
            aux+=((xn[i]-xa[i])*(xn[i]-xa[i]))/(xn[i]*xn[i]); //calculo del error
        }

        aux=sqrt(aux);
        //actualizar xanterior
        for(int i=0; i<m;i++){
            xa[i]=xn[i];
        }
        max++;//incrementar contador;

    } while(aux>tole && max<100);

    printf("Numero de iteraciones: %d \n", max);
    for(int i=0; i<m;i++){
        printf("%lf ", xn[i]);
    }
    return 0;
}
