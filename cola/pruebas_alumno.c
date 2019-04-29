#include "cola.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>

#include <stdio.h>
#include <stdlib.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

//  	

void prueba_cola_vacia(){
	cola_t* cola_vacia = cola_crear();
	print_test("La cola esta vacia", cola_esta_vacia(cola_vacia));
	print_test("el primer elemento de mi cola es NULL", cola_ver_primero(cola_vacia) == NULL);
	print_test("Intento desencolar y recibo NULL", cola_desencolar(cola_vacia) == NULL);
	cola_destruir(cola_vacia, NULL);
	print_test("La cola fue destruida", true);
}

void prueba_cola_encolar(){
	printf("Prueba 01\n");
	cola_t* cola01 = cola_crear();	
	printf("encolo elementos del mismo tipo\n");
	print_test("La cola esta vacia", cola_esta_vacia(cola01));
	int arreglo[] = {5, 20, 3, 4, 10};
	for (int x=0; x<5; x++){
		cola_encolar(cola01, &arreglo[x]);
	}	
	print_test("La cola no esta vacia", !cola_esta_vacia(cola01));
	print_test("el primer elemento de mi cola es 5", cola_ver_primero(cola01) == &arreglo[0]);
	cola_destruir(cola01, NULL);
	print_test("La cola fue destruida", true);
}

void prueba_cola_volumen(){
	printf("Prueba 03\n");
	printf("Encolo y veo que encole lo que creo haber encolado\n");
	cola_t* cola_vol = cola_crear();
	int a = 0;
	print_test("La cola esta vacia", cola_esta_vacia(cola_vol));
	char* arreglo[] = {"1","26","13","40","55","600","07","80","49","10","111","220", "gato", "vaca", "perro"};
	for (int i=0; i<15; i++){
		print_test("Encole en la cola", cola_encolar(cola_vol, &arreglo[i]));
	}
	print_test("La no cola esta vacia", !cola_esta_vacia(cola_vol));
	while(!cola_esta_vacia(cola_vol)){
		print_test("Desencole lo que habia encolado", cola_desencolar(cola_vol) == &arreglo[a]);
		a++;
	}
	cola_destruir(cola_vol, NULL);
	print_test("La cola fue destruida", true);
}		

void prueba_cola_destruir(){
	printf("Prueba 04\n");
	printf("Encolo pilas en la cola y luego las destruyo con pila_destruir\n");
	cola_t* cola = cola_crear();
	pila_t* pila01 = pila_crear();
	pila_t* pila02 = pila_crear();
	pila_t* pila03 = pila_crear();
	pila_apilar(pila01, "1");
	pila_apilar(pila01, "2");
	pila_apilar(pila01, "3");
	pila_apilar(pila02, "4");
	pila_apilar(pila02, "5");
	pila_apilar(pila02, "6");
	pila_apilar(pila03, "7");
	pila_apilar(pila03, "8");
	pila_apilar(pila03, "9");
	print_test("La cola esta vacia", cola_esta_vacia(cola));
	cola_encolar(cola, pila01);
	cola_encolar(cola, pila02);
	cola_encolar(cola, pila03);
	print_test("La cola no esta vacia", !cola_esta_vacia(cola));
	print_test("veo que encole la primer pila que encole", cola_ver_primero(cola) == pila01);
	void* destruir = pila_destruir;
	cola_destruir(cola, destruir);
	print_test("La cola con 3 pilas encoladas fue destruida", true);
}

void pruebas_cola_alumno(){
	prueba_cola_vacia();
	prueba_cola_encolar();
	prueba_cola_volumen();
	prueba_cola_destruir();
}




