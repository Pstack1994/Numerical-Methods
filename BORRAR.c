#include <stdio.h>

void multiplicacion(double **matriz, double **matriz2, double **matriz3, int m, int n, int p, int q);

int main(){

    double a[3][3]={{1,2,3},{4,5,6},{1,1,1}};
    double b[3][3]={{3,4,5},{6,7,8},{1,1,1}};
    double c[3][3];

    double **m1=a;
    double **m2=b;
    double **m3=c;

    multiplicacion(m1,m2,m3, 3,3,3,3);

    for(int i=0; i<3; i++){
        for(int j=0; j<3;j++){
            printf("%lf ", m3[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void multiplicacion(double **matriz, double **matriz2, double **matriz3, int m, int n, int p, int q){
    if(n!=p){
        printf("No es posible hacer la multiplicacion de estas matrices");
        return;
    }

    for(int i=0; i<m; i++){
        for(int j=0; j<n;j++){
           int aux=0;
            for(int k=0;k<p;k++){
                  aux+=matriz[i][k]*matriz2[k][j];
            }
            matriz3[i][j]=aux;
        }
    }
}
