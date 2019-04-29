#include "pila.h"
#include "testing.h"
#include <stddef.h>

#include <stdio.h>
#include <stdlib.h>



/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

//  	
void prueba_pila_vacia() {
	printf("Prueba 00\n");
	pila_t* pseudo_pila = pila_crear();
	print_test("Veo que la pila esta vacia", pila_esta_vacia(pseudo_pila));
	print_test("Veo que no hay un elemento al final de la pila", pila_ver_tope(pseudo_pila) == NULL);
	print_test("Intento desapilar y recibo null", pila_desapilar(pseudo_pila) == NULL);
	pila_destruir(pseudo_pila);
	print_test("La pila fue destruida", true);
}
void pila_prueba_apilar() {	
    	printf("Prueba 01\n");    			
	pila_t* pila = pila_crear();
	print_test("Veo que la pila esta vacia", pila_esta_vacia(pila));	
	printf("Apilo elementos del mismo tipo\n");	
	int* valor;
	valor = malloc(sizeof(int));
	*valor = 2;
	pila_apilar(pila, &valor);
	print_test("La pila no esta vacia", pila_esta_vacia(pila) == false);
	print_test("Veo el tope de la pila", pila_ver_tope(pila) == &valor);
	print_test("Desapilo mi unico elemento de la pila", pila_desapilar(pila) == &valor);
	print_test("La pila esta vacia", pila_esta_vacia(pila) == true);
	free(valor);
	int* vector;
	vector = malloc(20*sizeof(int));
	int  b = 0;	
	for (int a =0; a<19; a++) {
		b += 5;		
		vector[a]= b;
		pila_apilar(pila, &vector[a]);
		print_test("Apile en la pila lo que yo creo haber apilado", pila_ver_tope(pila) == &vector[a]);
	}
	int a = 18;
	while(!pila_esta_vacia(pila)) {
		print_test("Desapilo lo que yo creo haber apilado", pila_ver_tope(pila) == &vector[a]);
		vector[a] -= 5;
		a--;
		pila_desapilar(pila);
	}
	free(vector);	
	pila_destruir(pila);
	print_test("La pila fue destruida", true);
}	

void pila_prueba_apilar_NULL() {
	printf("Prueba 02\n");	
	pila_t* pila01 = pila_crear();
	printf("Apilo y desapilo NULL\n");
	pila_apilar(pila01, NULL);
	print_test("La pila no esta vacia", pila_esta_vacia(pila01) == false);	
	print_test("Desapilo el nulo  de la pila", pila_desapilar(pila01) == NULL);
	print_test("Veo que la pila esta vacia", pila_esta_vacia(pila01) == true);
	pila_destruir(pila01);
	print_test("La pila fue destruida", true);
}

void pila_prueba_mezclar() {	
	printf("Prueba 03\n");
	pila_t* pila02 = pila_crear();
	printf("Apilo 2 elementos de distinto tipo\n");
	int* entero;
	entero = malloc (sizeof(int));
	double* no_entero;
	no_entero = malloc (sizeof(double));	
	*entero = 5;
	*no_entero = 4.5;
	pila_apilar(pila02, &entero);
	print_test("Veo que el tope de la pila sea correcto", pila_ver_tope(pila02) == &entero);
	pila_apilar(pila02, &no_entero);
	print_test("Veo que el tope de la pila sea correcto", pila_ver_tope(pila02) == &no_entero);
	print_test("Desapilo mi elemento no entero de la pila", pila_desapilar(pila02) == &no_entero);
	print_test("Veo que el tope de la pila sea correcto", pila_ver_tope(pila02) == &entero); 
	print_test("Desapilo mi elemento entero de la pila", pila_desapilar(pila02) == &entero);
	print_test("La pila esta vacia", pila_esta_vacia(pila02) == true);
	free(entero);
	free(no_entero);
	pila_destruir(pila02);
	print_test("La pila fue destruida", true);
}



void pruebas_pila_alumno() {
	prueba_pila_vacia();
	pila_prueba_apilar();
	pila_prueba_apilar_NULL();
	pila_prueba_mezclar();
}



