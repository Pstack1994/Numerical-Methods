#ifndef METODOS
#define METODOS
double G_sinpivoteo(double**matriz, int m, int n, double *resultado);
double G_pivoteo(double**matriz, int m, int n, double *resultado);
void desc_LU(double **matriz, int m, int *posicion);
void solv_LU(double **matrizLU,int m, double *resultado);
double ** inversa_LU(double **matriz, int m, int *posicion);
double ** Mod_Cholesky(double **matriz,int m, int n);
void solv_Mod_Cholesky(double **cholesky, int m, double *resultado);
void factoriza_QR(double **matriz, double **r, int m, int n);
double *Gradiente_Conjugado(double **matriz, double *b, int m, int n);
#endif
