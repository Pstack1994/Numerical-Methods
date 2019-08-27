#include <stdio.h>
#include "matrix.c"
#include "solve.c"
#include "operacion_matriz.c"
#include "EcuacionesL_Metodos.c"
#include<math.h>



double evalua(double x);

int main(){
    double eval_a, eval_b, a=0, b=1, p_medio, eval_pmedio, toler=0.000001;
    int max=0;
    do{
        eval_a= evalua(a);
        eval_b= evalua(b);
        p_medio= (a + b)/2;
        eval_pmedio= evalua(p_medio);

        if( eval_pmedio*eval_a > 0){
            a=p_medio;
        }

        if( eval_pmedio*eval_b > 0){
            b=p_medio;
        }
        max++;
    } while (mabs(eval_pmedio) > toler && max<200);

    printf("La raiz esta en: %lf, numero de iteraciones: %d ", p_medio, max);
}


double evalua(double x){
    x=x-pow(2,-x);
    return x;
}
