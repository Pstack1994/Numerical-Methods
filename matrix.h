
#ifndef MATRIX
#define MATRIX

typedef struct Matriz{
	double **A;
	int m;
	int n;
} Matriz;

typedef struct Vector{
	double *v;
	int m;
	int n;
}Vector;

typedef struct eigen{
	double *eigenvector;
	double eigenvalor;
} eigen;

typedef struct eigen2{
    double **eigenvector;
    double *eigenvalor;
}eigen2;

typedef struct matriz_elemento{
    double max;
    int pos_i;
	int pos_j;
}matriz_elemento;


double **crea_matriz(int m);
double **crea_matriz2(int m, int n);
void liberar_matriz(double **matriz,int m);
Matriz lee_matriz(int argc, char* argv[]);
Matriz lee_matriz1(int argc, char* argv[]);
Vector lee_vector(char *filename);
#endif
