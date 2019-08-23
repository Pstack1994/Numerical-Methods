#include <stdio.h>
#include<stdlib.h>

double **crea_matriz(int m);
void liberar_matriz(double **matriz,int m);
double **lee_matriz(int argc, char* argv[]);
double **lee_matriz1(int argc, char* argv[]);

double **crea_matriz(int m){
    double **matriz;
    matriz=(double **)malloc(m*sizeof(double*));
    for(int i=0; i<m;i++){
        matriz[i]=(double *)malloc((m+1)*sizeof(double));
    }
    return matriz;
}

void liberar_matriz(double **matriz,int m){
    for(int i=0;i<m;i++){
        free(matriz[i]);
    }
    free(matriz);
}

double **lee_matriz(int argc, char* argv[]){
    int n,m;
    int k,l;
	double **matriz;

    FILE* fin = NULL;
	fin = fopen( argv[ 1 ] , "r" );

	if(  !fin  ){
		printf("Error: No se abrio %s\n" , argv[ 1 ] );
	}

    fscanf(fin, "%d %d", &n, &m );
	matriz=crea_matriz(m);

    for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			fscanf(fin, "%lf", &matriz[i][j]);
		}
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


double **lee_matriz1(int argc, char* argv[]){
    int n,m;
    int k,l;
	double **matriz;

    FILE* fin = NULL;
	fin = fopen( argv[ 1 ] , "r" );

	if(  !fin  ){
		printf("Error: No se abrio %s\n" , argv[ 1 ] );
	}

    fscanf(fin, "%d %d", &n, &m );
	matriz=crea_matriz(m);

    for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			fscanf(fin, "%lf", &matriz[i][j]);
		}
	}
	fclose( fin );

	return matriz;
}
