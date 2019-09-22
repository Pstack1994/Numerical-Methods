#include <stdio.h>
#include<stdlib.h>
#include"matrix.h"


double **crea_matriz(int m){
    double **matriz;
    matriz=(double **)malloc(m*sizeof(double*));
    for(int i=0; i<m;i++){
        matriz[i]=(double *)malloc((m+1)*sizeof(double));
    }
    return matriz;
}
double **crea_matriz2(int m, int n){
    double **matriz;
    matriz=(double **)malloc(m*sizeof(double*));
    for(int i=0; i<m;i++){
        matriz[i]=(double *)malloc((n)*sizeof(double));
    }
    return matriz;
}

void liberar_matriz(double **matriz,int m){
    for(int i=0;i<m;i++){
        free(matriz[i]);
    }
    free(matriz);
}

Matriz lee_matriz(int argc, char* argv[]){
    int n,m;
    int k,l;
	Matriz matriz;


    FILE* fin = NULL;
	fin = fopen( argv[ 1 ] , "r" );

	if(  !fin  ){
		printf("Error: No se abrio %s\n" , argv[ 1 ] );
	}

    fscanf(fin, "%d %d", &m, &n );
	matriz.A=crea_matriz2(m,n+1);

    for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			fscanf(fin, "%lf", &matriz.A[i][j]);
		}
	}
	fclose( fin );

	fin = fopen( argv[ 2 ] , "r" );

	if(  !fin  ){
		printf( "Error: No se abrio %s\n" , argv[ 1 ] );
	}

    fscanf( fin , "%d %d", &k , &l );

	for(int j=0; j<k; j++){
		fscanf(fin, "%lf", &matriz.A[j][n]);
	}
	fclose( fin );
	matriz.m=m;
	matriz.n=n;

	return matriz;
}


Matriz lee_matriz1(int argc, char* argv[]){
    int m, n;
	Matriz matriz;

    FILE* fin = NULL;
	fin = fopen( argv[ 1 ] , "r" );

	if(  !fin  ){
		printf("Error: No se abrio %s\n" , argv[ 1 ] );
	}

    fscanf(fin, "%d %d", &m, &n );
	matriz.A=crea_matriz2(m,n);

    for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			fscanf(fin, "%lf", &matriz.A[i][j]);
		}
	}
	fclose( fin );
	matriz.m=m;
	matriz.n=n;
	return matriz;
}

Vector lee_vector(char *filename){
	int m, n;
	Vector vector;
	FILE* fin=NULL;
	fin=fopen(filename, "r");

	if(  !fin  ){
		printf("Error: No se abrio %s\n" , filename);
	}

	fscanf(fin, "%d %d", &m, &n );
	vector.v=(double*)malloc(m*sizeof(double));

    for(int i=0; i<m; i++){
		fscanf(fin, "%lf", &vector.v[i]);
	}
	fclose( fin );
	vector.m=m;
	vector.n=n;
	return vector;
}
