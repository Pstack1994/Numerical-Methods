#include <stdio.h>
#include <stdlib.h>


int main( int argc , char* argv[] ){
	double eps = 1.0;
	int n = 0;
	while( 1.0 + ( eps * 0.5 ) > 1.0 ){
		++n;
		eps *= 0.5;
	}
	printf("\n\nEpsilon de la maquina en forma binaria = 2^(-%d)\n", n);
	printf("Epsilon de la maquina en forma decimal = %G\n\n", eps);
	return 0;
}
