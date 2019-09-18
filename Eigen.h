#ifndef EIGEN
#define EIGEN
eigen potencia_inversa(double **matriz, int m, int n, double tole);
eigen2 potencia_deflacion(double **matriz, int m, int n, double tole);
eigen2 deflacion_potenciainv(double **matriz, int m, int n, double tole);
eigen2 Jacobi_Eigen(double **matriz, double tole, int m);
#endif
