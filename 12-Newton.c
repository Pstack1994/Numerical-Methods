#include <stdio.h>
#include <time.h>
#include "matrix.c"
#include<math.h>
#include "tarea5.c"





int main(){
    double tolerancia=1e-12;
    menu_newton(tolerancia);
    return 0;
}
