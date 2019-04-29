#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#define TRACE(x,y) fprintf(stdout,x,y)

void imprimir (int* arreglo, size_t n){
	printf("[%d", arreglo[0]);
		for(int a=1; a<(n-1); a++){
			printf(",%d", arreglo[a]);
		}
	printf(",%d]\n", arreglo[n-1]);
}

double* obtener_promedio_movil_corto(int* arreglo, size_t n, size_t k){
	imprimir(arreglo,n);
	double* resultado = malloc(sizeof(double) *n);
	double valor      = 0;
	for(int i=0; i<n; i++){
		TRACE("i: %d\n",i);
		int div=1;
		valor = arreglo[i];
		for(int delta=1; delta<=k; delta++){
			TRACE("%d\n",delta);
			if( (i-delta)>-1 ){
				TRACE("i-delta ok: %d\n",i-delta);
				valor += arreglo[i-delta];
				div++;
			}

			if( (i+delta)<n ){
				TRACE("i+delta ok: %d\n",i+delta);
				valor += arreglo[i+delta];
				div++;
			}
		}
		resultado[i] = valor/div;
	}
	return resultado;
}

double* obtener_promedio_movil_optimizado(int* arreglo, size_t n, size_t k){
	imprimir(arreglo,n);
	//double* resultado    = malloc(sizeof(double) *n);
	int* arreglo_aux  = malloc(sizeof(int) *n);
	//double valor       = 0;
	//int suma_acumulada = 0;
	int a   = 0;
	//int div = 1;
	while(a<n){
		arreglo_aux[a] = arreglo[a];
		if(arreglo_aux[a-1]){
			arreglo_aux[a] += arreglo_aux[a-1];
		}
		a++;
	}
	// Imprimo el arreglo para ver que acumule bien.
	imprimir(arreglo_aux, n);
	//for(int i=0; i<n; i++){
	
	//}
	
	//return resultado;
	return NULL;
}

int main(){
	int arreglo1[]  = {1,-1,0,1,-1,0,1,-1};
	int arreglo2[]  = {1,1,1,1,1,1,1,1};
	int arreglo3[]  = {0,0,0,0,0,0,0,0};
	int arreglo4[]  = {1,2,3,1,2,3,1,2,3};
	int arreglo5[]  = {1,2,3,0,0,0,0,1,2,3,0,0,0,0,1,2,3,0,0,0,0};
	int arreglo6[]  = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int arreglo7[]  = {9,8,7,5,4,6,5,4,5,6,7,8,9,9,6,4,6,8};
	int arreglo8[]  = {1,4,8,6,8,6,7,8,9};
	int arreglo9[]  = {5,6,5,2,13};
	int arreglo10[] = {9,8,7,6,5,4,3,2,1};
	int* arreglos[] = {arreglo1, arreglo2, arreglo3, arreglo4, arreglo5, arreglo6,arreglo7, arreglo8, arreglo9, arreglo10, NULL};

	int largos[] = {8,8,8,9,21,15,18,9,5,9};

	/*for (int j=0; arreglos[j]; j++){
		double* obtuve = obtener_promedio_movil_corto(arreglos[j], largos[j], 1);
		for(int a=0; a<largos[j]; a++){
			printf("%d: %.3f\n",a,obtuve[a]);
		}
		free(obtuve);
	}*/
	for (int j=0; arreglos[j]; j++){
		obtener_promedio_movil_optimizado(arreglos[j], largos[j], 1);
	}
	obtener_promedio_movil_optimizado(arreglos[3], largos[3], 1);
	return 0;
}
//

