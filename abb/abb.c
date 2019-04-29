#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "abb.h"
#include "pila.h"

#define IZQ -1
#define DER  1

// Opizzi, Juan Cruz - 99807 
// Silvestri, María Carolina - 99175
// Corrige: Martín Buchwald


//FUNCA  Update: aprobado
/* *****************************************************************
 *           DEFINICION DE ESTRUCTURAS DEL ABB Y SU ITERADOR
 * *****************************************************************/

typedef struct abb_nodo{
	void* dato;
	char* clave;
	struct abb_nodo* izq;
	struct abb_nodo* der;
}abb_nodo_t;

struct abb{
	abb_nodo_t* raiz;
	size_t cantidad;
	abb_destruir_dato_t destruir_dato;
	abb_comparar_clave_t cmp;
};

struct abb_iter{
	const abb_t* abb;
	pila_t* pila;
};

/* *****************************************************************
 *           	DEFINICION DE PRIMITIVAS AUXILIARES
 * *****************************************************************/
// Devuelve true si la clave pertenece
bool clave_pertenece(const abb_t *abb, const char *clave, abb_nodo_t* raiz);

//Crea el nodo a guardar
abb_nodo_t* nodo_crear(char* clave, void* dato);

//Guardar recursivo
bool abb_guardar_rec(abb_t* abb, char * clave, abb_nodo_t* raiz, void *dato);

//Inserta el nodo
bool insertar_nodo_nuevo(char* clave, void* dato, int i, abb_nodo_t* raiz, abb_t* abb);

//Apila los elemetos del abb de menor a mayor
void llenar_pila(pila_t* pila, abb_nodo_t* nodo);

/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

//CREAR
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
	if (!abb) return NULL;
	abb->cantidad      = 0;
	abb->cmp           = cmp;
	abb->destruir_dato = destruir_dato;
	abb->raiz          = NULL;
	return abb;
}

//CANTIDAD DE ELEMENTOS
size_t abb_cantidad(abb_t *abb){
	return abb->cantidad;
}

//LA CLAVE PERTENECE
bool abb_pertenece(const abb_t *abb, const char *clave){
	return clave_pertenece(abb, clave, abb->raiz);
}

//OBTENER DATO
void* dato_obtener(const abb_t *abb, const char *clave, abb_nodo_t* raiz){
	if(abb->cmp(raiz->clave, clave) == 0){	// 1
		return raiz->dato;
	}
	if(abb->cmp(raiz->clave, clave) < 0){
		return dato_obtener(abb, clave, raiz->der);
	}
	return dato_obtener(abb, clave, raiz->izq);
}

void *abb_obtener(const abb_t *abb, const char *clave){
	if(!abb_pertenece(abb, clave)){
		return NULL;
	}
	return dato_obtener(abb, clave, abb->raiz);	
}

//DESTRUIR ABB Y SUS NODOS

/*Función auxiliar para destuir los nodos*/
void destruir_nodos(abb_nodo_t* raiz, abb_destruir_dato_t destruir_dato){
	if(!raiz){
		return;
	}
	destruir_nodos(raiz->izq, destruir_dato);
	destruir_nodos(raiz->der, destruir_dato);	
	if (destruir_dato){
		destruir_dato(raiz->dato);
	}
	free(raiz->clave);
	free(raiz);
	return;
}

void abb_destruir(abb_t *abb){
	destruir_nodos(abb->raiz, abb->destruir_dato);
	free(abb);
}

// BORRAR NODO DEL ABB
void* abb_borrar_rec(abb_nodo_t** punt_nodo_busq, const char* clave, abb_comparar_clave_t cmp){ 	
	abb_nodo_t* nodo_busq = *punt_nodo_busq;
	int comp = cmp(nodo_busq->clave, clave);
	if(!comp){
		// Tiene dos hijos -TE ODIO-
		if(nodo_busq->der && nodo_busq->izq){
			abb_nodo_t* aux = nodo_busq->der;
			while(aux->izq){
				aux = aux->izq;	
			}
			char* clave_n = nodo_busq->clave;
			void* dato_n = nodo_busq->dato;
			nodo_busq->clave = aux->clave;
			nodo_busq->dato = aux->dato;
			aux->dato = dato_n;
			aux->clave = clave_n;		
			return abb_borrar_rec(&nodo_busq->der, clave, cmp);
		}
		void* dato = nodo_busq->dato;
		free(nodo_busq->clave);
		// Tiene un hijo
		if(!nodo_busq->der){
			*punt_nodo_busq = nodo_busq->izq;
		}else if(!nodo_busq->izq){
			*punt_nodo_busq = nodo_busq->der;
		}
		// No tiene hijos
		if(!nodo_busq->der && !nodo_busq->izq){
			*punt_nodo_busq = NULL;
		}
		free(nodo_busq);
		return dato;
	}	
	if(comp >0){
		return abb_borrar_rec(&nodo_busq->izq,clave,cmp);
	}	
	return abb_borrar_rec(&nodo_busq->der,clave,cmp);
}

void *abb_borrar(abb_t* abb, const char *clave){
	if(!abb || !abb_pertenece(abb,clave)){
		return NULL;
	}
	void* dato = abb_borrar_rec(&abb->raiz, clave, abb->cmp);
	abb->cantidad--;
	return dato;
}

// GUARDAR
bool abb_guardar_rec(abb_t* abb, char * clave, abb_nodo_t* raiz, void *dato){
	//Actuliza el dato
	int comp = abb->cmp(raiz->clave, clave);
	if(comp == 0){		// 2
		if(abb->destruir_dato){ 
			abb->destruir_dato(raiz->dato);
		}
		raiz->dato = dato;
		free(clave);
		return true;
	}
	//Izq
	if(comp > 0){
		if(!raiz->izq){
			return insertar_nodo_nuevo(clave, dato, IZQ, raiz, abb);
		}
		return abb_guardar_rec(abb, clave, raiz->izq, dato);
	}
	//der
	if(comp < 0){
		if(!raiz->der){
			return insertar_nodo_nuevo(clave, dato, DER, raiz, abb);
		}
		return abb_guardar_rec(abb, clave, raiz->der, dato);				
	}	
	return false;	
}

bool abb_guardar(abb_t *abb, const char *clave, void *dato){
	char* copia = malloc(strlen(clave)+1);
	if(!copia){
		return false;
	}
	strcpy(copia, clave);
	if(!abb->raiz){		
		abb_nodo_t* nodo = nodo_crear(copia, dato);
		abb->raiz        = nodo;
		abb->cantidad = 1;
		return true;
	}
	return abb_guardar_rec(abb, copia, abb->raiz, dato);
}
	
/* *****************************************************************
 *                    ITERADOR INTERNO INORDER
 * *****************************************************************/
 
void abb_in_order_rec(abb_nodo_t *nodo, bool visitar(const char *, void *, void *), void *extra){
	if(!nodo){
		return;
	}
	abb_in_order_rec(nodo->izq, visitar, extra);
	if(!visitar(nodo->clave, nodo->dato, extra)){ 
		return;
	}
	abb_in_order_rec(nodo->der, visitar, extra);
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
	if(!arbol || !arbol->raiz){
		return;
	}
	abb_in_order_rec(arbol->raiz, visitar, extra);
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// CREAR ITERADOR
abb_iter_t *abb_iter_in_crear(const abb_t *abb){
	abb_iter_t* iter = malloc(sizeof(abb_iter_t));
	if(!iter){ 
		return NULL;
	}
	pila_t* pila = pila_crear();
	if(!pila){
		free(iter);
		return NULL;
	}
	//apilar
	llenar_pila(pila, abb->raiz);
	iter->pila = pila;	
	iter->abb = abb;
	return iter;
}

// ITERADOR AL FINAL
bool abb_iter_in_al_final(const abb_iter_t *iter){
	return pila_esta_vacia(iter->pila);
}

// ITERADOR AVANZAR
bool abb_iter_in_avanzar(abb_iter_t *iter){
	if(!iter || abb_iter_in_al_final(iter)){
		return false;
	}
	pila_desapilar(iter->pila);
	return true;
}

// ITERADOR VER ACTUAL
const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	if(!pila_esta_vacia(iter->pila)){
		abb_nodo_t* nodo = pila_ver_tope(iter->pila);
		return nodo->clave;
	}
	return NULL;
}

// DESTRUIR ITERADOR
void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila);
	free(iter);
}

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

bool clave_pertenece(const abb_t *abb, const char *clave, abb_nodo_t* raiz){
	if(!raiz){ 
		return false;
	}
	int comp = abb->cmp(raiz->clave, clave);
	if(comp == 0){		// 3
		return true;
	}
	if(comp < 0){
		return clave_pertenece(abb, clave, raiz->der);
	}	
	return clave_pertenece(abb, clave, raiz->izq);
}

abb_nodo_t* nodo_crear(char* clave, void* dato){
	abb_nodo_t* nodo = malloc(sizeof(abb_t));
	if(!nodo){
		return NULL;
	}
	nodo->clave = clave;
	nodo->dato  = dato;
	nodo->izq   = NULL;
	nodo->der   = NULL;
	return nodo;
}

bool insertar_nodo_nuevo(char* clave, void* dato, int i, abb_nodo_t* raiz, abb_t* abb){
	abb_nodo_t* nodo = nodo_crear(clave, dato);
	if(!nodo){ 
		return false;
	}
	if(i == IZQ){ 
		raiz->izq = nodo;
	}
	if(i == DER){
		raiz->der = nodo;
	}
	abb->cantidad++;
	return true;
}

void llenar_pila(pila_t* pila, abb_nodo_t* nodo){	
	if(!nodo){ 
		return;
	}
	if(nodo->der){
		llenar_pila(pila, nodo->der);
	}
	pila_apilar(pila, nodo);
	if(nodo->izq){
		llenar_pila(pila, nodo->izq);
	}
}
