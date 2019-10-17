
#ifndef INTERPOLA
#define INTERPOLA
double derivada_lagrange(Vector x, Vector fx, double x0, int i);
Vector interpola_hermite(Vector x, Vector fx, Vector fpx, int a, int b);
Vector coef_lagrange(Vector x, Vector fx, double x0);
Vector interpola_lagrange(Vector x, Vector fx, int a, int b);
Matriz dif_div_newton(Vector fx, Vector x);
Vector evalua_dif_div_newton(Vector x, Matriz tabla, int a, int b);
#endif
