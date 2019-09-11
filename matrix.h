
#ifndef MATRIX
#define MATRIX

typedef struct Matriz{
	double **A;
	int m;
	int n;
} Matriz;

typedef struct eigen{
	double *eigenvector;
	double eigenvalor;
} eigen;

double **crea_matriz(int m);
double **crea_matriz2(int m, int n);
void liberar_matriz(double **matriz,int m);
Matriz lee_matriz(int argc, char* argv[]);
Matriz lee_matriz1(int argc, char* argv[]);
#endif
