#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#define TRACE(x,y) fprintf(stderr,x,y)
/*
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
	double* resultado = malloc(sizeof(double) *n);
	int* arreglo_aux  = malloc(sizeof(int) *n);
	int a          = 0;
	int aux        = 0;
	double cont    = 1;
	while(a<=k){
		aux += arreglo[a];
		a++;
	}
	resultado[0] = aux/a;	
	//aux = 0;
	for(int i = 1; i<n; i++){
		size_t menor = i - k;
		size_t mayor = i + k;
		if((menor <= 0) && (mayor < n)){
			aux += arreglo[mayor]; 
			cont++;
			arreglo_aux[i] = aux;
		}
		if((menor > 0) && (mayor < n)){
			aux -= arreglo[menor-1];
			aux += arreglo[mayor];
			arreglo_aux[i] = aux;
		}
		if((menor > 0) && (mayor >= n)){
			aux -= arreglo[menor-1];
			cont--;
			arreglo_aux[i] = aux;
		}	
		if((menor <= 0) && (mayor >= n)){
			aux = arreglo_aux[i-1];
		}
		resultado[i] = aux / cont;	
	}
	free(arreglo_aux);
	return resultado;
}

int main(){
	int arreglo1[] = {1,-1,0,1,-1,0,1,-1};
	int arreglo2[] = {1,1,1,1,1,1,1,1};
	int arreglo3[] = {0,0,0,0,0,0,0,0};
	int arreglo4[] = {1,2,3,1,2,3,1,2,3};
	int arreglo5[] = {1,2,3,0,0,0,0,1,2,3,0,0,0,0,1,2,3,0,0,0,0};
	int arreglo6[] = {10,5,3,6,2,6};	

	int* arreglos[] = {arreglo1, arreglo2, arreglo3, arreglo4, arreglo5, arreglo6, NULL};

	int largos[] = {8,8,8,9,21, 6};

	for (int j=0; arreglos[j]; j++){
		double* obtuve = obtener_promedio_movil_corto(arreglos[j], largos[j], 1);
		for(int a=0; a<largos[j]; a++){
			printf("%d: %.3f\n",a,obtuve[a]);
		}
		free(obtuve);
	}
	double* vector = obtener_promedio_movil_optimizado(arreglos[5], largos[5], 1);
	for(int z=0; z<largos[1]; z++){
		printf("%f\n", vector[z]);
	}
	free(vector);
	return 0;
}*/
//
