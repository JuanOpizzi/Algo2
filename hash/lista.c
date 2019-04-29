#include "lista.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Alumno: Opizzi Juan Cruz
// Ayudante: Martin
// Deifinición de la estructura lista y la estructura del iterador.

typedef struct nodo{
	void* dato;
	struct nodo* siguiente;
	}nodo_lista_t;

struct lista{
	nodo_lista_t* primero;
	nodo_lista_t* ultimo;
	size_t largo;
	};

struct lista_iter{
	nodo_lista_t* actual;
	nodo_lista_t* anterior;
	lista_t* lista;
	};

/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t* lista_crear(){
	lista_t* lista = malloc (sizeof(lista_t));
	if (!lista){
		return NULL;
	}
	lista->primero = NULL;
	lista->ultimo = NULL;	
	lista->largo = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t* lista){
	return (lista->primero == NULL);
}					 
	
void* lista_ver_ultimo(const lista_t* lista){
	if (lista_esta_vacia(lista)){
		return NULL;
	}
	return lista->ultimo->dato;
}

void* lista_ver_primero(const lista_t* lista){
	if (lista_esta_vacia(lista)){
		return NULL;
	}
	return lista->primero->dato;
}

size_t lista_largo(const lista_t *lista){
	if (lista_esta_vacia(lista)){
		return 0;
	}
	return lista->largo;
}

bool lista_insertar_primero(lista_t* lista, void* valor){
	nodo_lista_t* aux = malloc (sizeof (nodo_lista_t));
	if (!aux){
		return false;
	}
	aux->dato = valor;
	if (lista_esta_vacia(lista)){
		lista->ultimo = aux;
		aux->siguiente = NULL; 
	}
	else{
		aux->siguiente = lista->primero;
	}	
	lista->primero = aux;
	lista->largo ++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_lista_t* aux = malloc (sizeof(nodo_lista_t));
	if (!aux){
		return false;
	}
	aux->dato = dato;
	aux->siguiente = NULL;
	if (lista_esta_vacia(lista)){
		lista->primero = aux;
	}
	else {
		lista->ultimo->siguiente = aux;
	}	
	lista->ultimo = aux;
	lista->largo ++;
	return true;
}

void* lista_borrar_primero(lista_t *lista){	
	void* valor_borrado;	
	if (lista_esta_vacia(lista)){
		return NULL;
	}
	nodo_lista_t* auxiliar = lista->primero;
	auxiliar->siguiente = lista->primero->siguiente; 
	lista->primero = auxiliar->siguiente; 
	valor_borrado = auxiliar->dato;
	free(auxiliar);
	lista->largo --; 
	return valor_borrado;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
	void* dato;	
	while (!lista_esta_vacia(lista)){
		dato = lista_borrar_primero(lista);
		if (destruir_dato) {
			destruir_dato(dato);
		}
	}	
	free(lista);
}

lista_iter_t* lista_iter_crear(lista_t *lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if (!iter){
		return NULL;
	}
	iter->anterior = NULL;
	iter->actual   = lista->primero;
	iter->lista    = lista;	
	return iter; 
}
	
bool lista_iter_al_final(const lista_iter_t *iter){
	return !iter->actual;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

void* lista_iter_ver_actual(const lista_iter_t *iter){
	return iter->actual->dato;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if (lista_iter_al_final(iter)){
		return false;
	}
	iter->anterior = iter->actual;
	iter->actual = iter->actual->siguiente; 
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
	void* valor_borrado;	
	if (lista_iter_al_final(iter)){
		return NULL;
	}	
	if(!iter->anterior){
		valor_borrado = lista_borrar_primero(iter->lista);
		iter->actual  =	iter->lista->primero;
		return valor_borrado; 
	}
	nodo_lista_t* auxiliar = iter->actual;
	valor_borrado = auxiliar->dato;
	if (!iter->actual->siguiente){
		iter->anterior->siguiente = NULL;
		iter->actual = NULL;
		iter->lista->ultimo = iter->anterior;
	}
	else{
		iter->anterior->siguiente = auxiliar->siguiente;
		iter->actual              = auxiliar->siguiente;
	}	
	free(auxiliar);
	iter->lista->largo --;
	return valor_borrado;
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	if(!iter->anterior){		
		lista_insertar_primero(iter->lista, dato);
		iter->actual              = iter->lista->primero;
		return true;
	}	
	if (lista_iter_al_final(iter)){	
		lista_insertar_ultimo(iter->lista, dato);
		iter->anterior->siguiente = iter->lista->ultimo;		
		iter->actual              = iter->lista->ultimo;
		return true;
	}
	nodo_lista_t* aux = malloc (sizeof (nodo_lista_t));
	if (!aux){
		return false;
	}		       
	aux->dato = dato;	
	aux->siguiente  = iter->actual;
	iter->anterior->siguiente = aux;
	iter->actual = aux;
	iter->lista->largo ++;
	return true;
}

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra){
	bool aux;	
	nodo_lista_t* nodo = lista->primero;	
	while(nodo != NULL){
		aux = visitar(nodo->dato, extra);
		if (!aux){
			return;
		}
		nodo = nodo->siguiente;
	}	
}




