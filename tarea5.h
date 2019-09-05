#include"matrix.h"

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
