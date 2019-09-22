#ifndef SOLVE
#define SOLVE
    void solv_diagonal(double **matriz, double *b, int m,double *resultado);
    void solv_tinf(double **matriz,double *b, int m, double *resultado);
    double det_diagonal(double **matriz, int m);
    void solv_tsup(double **matriz, double *b, int m, double *resultado);
#endif
