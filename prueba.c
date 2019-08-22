#include <stdio.h>
#include <stdlib.h>
#include "matrix.c"
double **lee_matriz(int argc, char* argv[]);

int main(int argc, char* argv[]){
    double** A;
    A = lee_matriz(argc, argv);
	A[0][0]=1;
	liberar_matriz(A,4);
    return 0;
}

double **lee_matriz(int argc, char* argv[]){
    int n,m;        // Size of matrix A
    int k,l;        // Size of matrix b (solutions to linear equations)
	double **matriz;
    FILE* fin = NULL;

	fin = fopen( argv[ 1 ] , "r" );
	if(  !fin  ){
		printf("Error: No se abrio %s\n" , argv[ 1 ] );
	}

    fscanf(fin, "%d %d", &n, &m );
	printf("%d, %d",n, m);
	matriz=crea_matriz(m);

    for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			fscanf(fin, "%lf", &matriz[i][j]);
		}
		printf("\n");
	}
	fclose( fin );

	fin = fopen( argv[ 2 ] , "r" );
	if(  !fin  ){
		printf( "Error: No se abrio %s\n" , argv[ 1 ] );
	}

    fscanf( fin , "%d %d", &k , &l );

		for(int j=0; j<k; j++){
			fscanf(fin, "%lf", &matriz[j][m]);
		}
	fclose( fin );

	return matriz;
}
