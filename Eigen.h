#ifndef EIGEN
#define EIGEN
eigen metodo_potencia(double **matriz, int m, int n, double tole);
eigen potencia_inversa(double **matriz, int m, int n, double tole);
eigen2 potencia_deflacion(double **matriz, int m, int n, double tole);
eigen2 deflacion_potenciainv(double **matriz, int m, int n, double tole);
eigen2 Jacobi_Eigen(double **matriz, double tole, int m);
eigen Metodo_Rayleigh(double ** matriz, double *xa, int m, int n, double tole);
eigen2 metodo_QR(double **matriz, double **r, int m, int n, double tole);
eigen2 iteracion_subespacio(double** matriz, int m, int n, int tp, double tole );
#endif
