#include "cola.h"
#include <stdlib.h>

#include <stdio.h>

// Deifinición de la estructura cola y la estructura nodo.
// Alumno: Opizzi Juan Cruz
// Ayudante: Agustina Mendez
typedef struct nodo{ 
	void* dato;
	struct nodo* siguiente;
	}nodo_t;


struct cola{
	nodo_t* primero;
	nodo_t* ultimo;
	};

/* *****************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t* cola_crear(void) {
	cola_t* cola = malloc (sizeof(cola_t));
	if (!cola){
		return NULL;
	}	
	cola->primero = NULL;		
	cola->ultimo = NULL;
	return cola;
}

bool cola_esta_vacia(const cola_t *cola) {
	return (cola->primero == NULL);
}

void* cola_ver_primero(const cola_t *cola ){
	if (cola_esta_vacia(cola)){
		return NULL;
	}
	return cola->primero->dato;
}

nodo_t* nodo_crear(){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (!nodo) {
		return NULL;
	}
	return nodo;
}

bool cola_encolar(cola_t *cola, void* valor) {
	nodo_t* aux = nodo_crear();
	if (!aux) {
		return false;
	}	
	aux->dato = valor;
	aux->siguiente = NULL;		
	if (cola_esta_vacia(cola)) {	
		cola->primero = aux;
	}else{
		cola->ultimo->siguiente = aux;
	}
	cola->ultimo = aux;
	return true;
}

void* cola_desencolar(cola_t *cola) {	
	void* valor_desencolado;	
	if (cola_esta_vacia(cola)) {
		return NULL;
	}
	nodo_t* auxiliar = cola->primero;
	auxiliar->siguiente = cola->primero->siguiente; 
	cola->primero = auxiliar->siguiente; 
	valor_desencolado = auxiliar->dato;
	free(auxiliar);
	return valor_desencolado;
}


void cola_destruir(cola_t *cola, void destruir_dato(void*)) {	
	void* dato;	
	while (!cola_esta_vacia(cola)){
		dato = cola_desencolar(cola);
		if(destruir_dato){
			destruir_dato(dato);
		}
	}	
	free(cola);
}


