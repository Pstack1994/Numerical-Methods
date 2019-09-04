#include <stdio.h>
#include <stdlib.h>


double mabs(double a);
double evalua(double x, int numero);
double biseccion(double a, double b, double toler, int numero);
void menu_biseccion();
double deriva(double x, double h, int numero);
void menu_newton(double tolerancia);
double *Jacobi(double **matriz, int m, double tole);
void imprime_resultado(double *resultado, int m);
double *Gauss_Seidel(double **matriz, int m, double tole);
eigen metodo_potencia(double **matriz, int m, int n, double tole);



double mabs(double a){
return (a<0)? -a:a;//calcular el valor absoluto
}

double evalua(double x, int numero){

    switch(numero){
        case 1: return x*x;break;
        case 2: return (x*x)-2;break;
        case 3: return sin(x);break;
        case 4: return 1/(x*x);break;
        case 5: return (x*x*x)-3*(x*x)+2*x;break;
        case 6: return 1/(x*x);break;
    }

}

double biseccion(double a, double b, double toler, int numero){
double eval_a, eval_b, p_medio, eval_pmedio, a1=a, b1=b;
    int max=0, it=100;
 do{
        p_medio= (a + b)/2;
        eval_a= evalua(a,numero);
        //eval_b= evalua(b,numero);
        eval_pmedio= evalua(p_medio,numero);

        if( eval_pmedio*eval_a > 0){
            a=p_medio;
        }else{b=p_medio;}

        max++;
    } while (mabs(eval_pmedio) > toler && max<it);
    if(max==it){
    printf("No se encontraron raices en el intervalo de %lf a %lf", a1,b1);
    return 0;
    }else{
    printf("Se encontró raiz en el intervalo de %lf a %lf \n", a1,b1);
    printf("La raiz esta en: %lf, numero de iteraciones: %d ", p_medio, max);
    }
    return p_medio;
}

void menu_biseccion(){
    int numero;
    int bandera=0;
    double a;
    double b;
    double resultado;
    printf("1) x^2 \n2) x^2 -2 \n3) sin(x) \n4) 1/(x^2) \n5) x^3 + 3x^2 + 2x \n6) 1/(x^2)\n");
    while(bandera==0){
        printf("\nA qué función deseas aproximar la raíz: ");
        scanf("%d", &numero);
        switch(numero){
            case 1: a=-10;b=-1;bandera=1;break;
            case 2: a=-10;b=10;bandera=1;break;
            case 3: a=-M_PI; b=M_PI;bandera=1;break;
            case 4: a=-1;b=1;bandera=1;break;
            case 5: a=-3;b=3;bandera=1;break;
            case 6: a=-10000;b=10000;bandera=1;break;
            default: printf("No es una opción valida, ingrese otra."); bandera=0;
        }
    }
    resultado=biseccion(a,b,1e-15,numero);
}


double deriva(double x, double h, int numero){
    x=(evalua(x+h, numero)-evalua(x, numero))/h;
    return x;
}
double Newton (double xa, double tolerancia, int numero){
    double xn, error=tolerancia+1;
    int max=0, it=100;
    do{
        if(deriva(xa,tolerancia, numero)>tolerancia){
        xn=xa-(evalua(xa, numero)/deriva(xa,tolerancia, numero));
        }else{
        printf("No se encontraron raices");
        return 0;
        }
        error=mabs(xn-xa);
        xa=xn;

        max++;
    }while(error>tolerancia && max<it);

    if(max==it){
    printf("No se encontraron raices");
    return 0;
    }else{
    printf("Se encontró raiz\n");
    printf("La raiz esta en: %lf, numero de iteraciones: %d ", xn, max);
    return xn;
    }
}
void menu_newton(double tolerancia){
    int numero;
    int bandera=0;
    double xa;
    double resultado;
    printf("1) x^2 \n2) x^2 -2 \n3) sin(x) \n4) 1/(x^2) \n5) x^3 + 3x^2 + 2x \n6) 1/(x^2)\n");
    while(bandera==0){
        printf("\nA qué función deseas aproximar la raíz: ");
        scanf("%d", &numero);
        switch(numero){
            case 1: xa=1;bandera=1;break;
            case 2: xa=2;bandera=1;break;
            case 3: xa=1;bandera=1;break;
            case 4: xa=10;bandera=1;break;
            case 5: xa=-2;bandera=1;break;
            case 6: xa=5;bandera=1;break;
            default: printf("No es una opción valida, ingrese otra."); bandera=0;
        }
    }
    resultado=Newton(xa,tolerancia,numero);
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
        //xa[i]=matriz[i][m];
        xa[i]=1;
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
        //printf("\n %lf", error);

        //actualizar xanterior
        for(int i=0; i<m;i++){
            xa[i]=xn[i];
        }
        max_it++;//incrementar contador;
    } while(error>tole && max_it<3000);

    if(max_it==2000){
        printf("El sistema diverge /n");
        //return xn;
        free(xn);
        return 0;
    }else {
        printf("Numero de iteraciones: %d \n", max_it);
        return xn;
    }

}

void imprime_resultado(double *resultado, int m){
    printf("EL resultado es: ");
    for(int i=0; i<m;i++){
        printf("%lf ", resultado[i]);
    }
    printf("\n");
}

double *Gauss_Seidel(double **matriz, int m, double tole){
    double suma=0, aux=0, auxa=0;
    double *xn=(double *)malloc(m*sizeof(double*));
    int max=0;

    ///inicializacion de xn
    for(int i=0; i<m;i++){
        xn[i]=1;
    }

    do{
        aux=0;
        for(int i=0;i<m;i++){
            suma=0;
            for(int j=0; j<m;j++){
                if(i!=j){
                    suma+=matriz[i][j]*xn[j];
                }
         }
            auxa=xn[i];
            xn[i]=(matriz[i][m]-suma)/matriz[i][i];
            aux+=((xn[i]-auxa)*(xn[i]-auxa))/(xn[i]*xn[i]); //calculo del error
        }

        aux=sqrt(aux);
        max++;//incrementar contador;

    } while(aux>tole && max<3000);

    printf("Numero de iteraciones: %d \n", max);
    for(int i=0; i<m;i++){
        printf("%lf ", xn[i]);
    }
    return xn;
}

eigen metodo_potencia(double **matriz, int m, int n, double tole){
    eigen solucion;
    solucion.eigenvector=(double *)malloc(m*sizeof(double));
    double  xn[m], error=0, maxa=0, maxn=0, norma=0;
    double xa[m], resultado[m], lambda;
    int max_it=0;

    ///inicilizar vector anterior
    for(int i=0; i<m;i++){
        xa[i]=0;
    }
    xa[0]=1;

    do{
    norma=0;
    //multiplicar vector anterior por matriz
    for(int i=0; i<m; i++){
        for(int j=0; j<n;j++){
            resultado[i]=0;
            for(int k=0;k<m;k++){
                  resultado[i]+=matriz[i][k]*xa[k];
            }
        }
       norma+=resultado[i]*resultado[i];
    }
    //norma de la multiplicacion
    norma=sqrt(norma);

    maxa=maxn;
    //encontrar maximo del vector anterior
    double max=mabs(xa[0]);
    int pos_max=0;
    for(int i=0; i<m;i++){
        if(mabs(xa[i])>mabs(max)){
            max=xa[i];
            pos_max=i;
        }
    }

    lambda=resultado[pos_max]/xa[pos_max];
    maxn=lambda;

    //normalizar vector de la multiplicación
    for(int i=0; i<m; i++){
        xa[i]=resultado[i]/norma;
        solucion.eigenvector[i]=xa[i];
    }

    error=mabs(maxn-maxa);
    solucion.eigenvalor=maxn;
    max_it++;
    } while (max_it<100 && error > tole);

    return solucion;
}