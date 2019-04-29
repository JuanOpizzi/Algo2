#include "tp0.h"

/* ******************************************************************
 *                     FUNCIONES A COMPLETAR
 * *****************************************************************/

/* swap() intercambia dos valores enteros.
 */
void swap (int* x, int* y) {
	int aux=*x;
	*x = *y;
	*y = aux;
}

/* maximo() busca el mayor elemento del arreglo y devuelve su posicion.
 * Si el vector es de largo 0, devuelve -1.
 */
int maximo(int vector[], int n) {
	int pos = 0;				
	if (n == 0) {
		return -1;
	}	
	for(int x=0; x<n; x++) {
		if (vector[pos] < vector[x]){
			pos = x;
		}
	}		
	return pos;
}

/* La función comparar recibe dos vectores y sus respectivas longitudes
 * y devuelve -1 si el primer vector es menor que el segundo; 0 si son
 * iguales; y 1 si el segundo es menor.
 *
 * Un vector es menor a otro cuando al compararlos elemento a elemento,
 * el primer elemento en el que difieren no existe o es menor.
 */
int comparar(int vector1[], int n1, int vector2[], int n2) {	
	int resultado = 0;	
	for(int x=0; x<n1 && x<n2; x++){
		if (vector1[x] < vector2[x]) {
			return -1;
		}
		if (vector1[x] > vector2[x]) {
			return  1;
		}	
	}
	if (n1 < n2) {
		return -1;
	}
	if (n1 > n2) {
		return 1;
	}
	return resultado;
}
	
/* selection_sort() ordena el arreglo recibido mediante el algoritmo de
 * selección.
 */
void seleccion(int vector[], int n) {
	int y = 0;	
	int aux;
	for(int x=n-1; x >= 0; x=x-1){
		aux = maximo(vector, n-y);
		swap(&vector[x], &vector[aux]);
		y++;
	}
}






