#ifndef OPERACION
#define OPERACION
void imprime_matrizc(double **matriz, int m, int n);
void imprime_resultado(double *resultado, int m);
double mabs(double a);
void cambia_renglon(double**matriz,int m, int r1, int r2); //m=numero de columnas
void cambia_columna(double**matriz,int m, int c1, int c2);
double find_maxr(double **matriz, int m,int r, int c, int *r2);
double find_max(double **matriz, int m, int n, int r, int c , int *r2, int *c2);
double **multiplicacion(double **matriz, double **matriz2, int m, int n, int p, int q);
double ppunto(double *x, double *y, int m);
matriz_elemento find_max_od(double **matriz, int m, int n);
#endif
