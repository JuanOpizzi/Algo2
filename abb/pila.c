#include "pila.h"
#include <stdlib.h>
#define CAP_INICIAL 25
#define CUARTO 4
#define MITAD 2
#define DOBLAR_CAP 2
#define VACIO 0

/* Definición del struct pila proporcionado por la cátedra.*/
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// CREAR PILA
pila_t* pila_crear(void){
	pila_t* pila = malloc(sizeof(pila_t));
	if (!pila) return NULL;
	pila->capacidad = CAP_INICIAL;
	pila->datos = malloc(pila->capacidad * sizeof(void*));
	if (!pila->datos){
		free(pila);
		return false;
	}
	pila->cantidad = VACIO;
	return pila;
}

//DESTRUIR PILA
void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}

//PILA VACIA
bool pila_esta_vacia(const pila_t *pila){
	return (pila->cantidad == 0);
}

//REDIMENSIONAR
bool redimensionar(pila_t* pila, size_t t_nuevo){
	void* datos_nuevo = realloc(pila->datos,t_nuevo * sizeof(void*));
	if (!datos_nuevo)return false;
	pila->datos = datos_nuevo;
    pila->capacidad = t_nuevo;
    return true;
}

//APILAR
bool pila_apilar(pila_t *pila, void* valor){
	if(pila->cantidad >= pila->capacidad){
		if(redimensionar(pila,pila -> capacidad * DOBLAR_CAP) == false){	
			return false;
		}
	} 
	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	return true;		
};

//VER TOPE
void* pila_ver_tope(const pila_t *pila){
	if(pila_esta_vacia(pila)) return NULL;
	return pila->datos[pila->cantidad-1];
}

//DESAPILAR
void* pila_desapilar(pila_t *pila){
	if(pila_esta_vacia(pila)) return NULL;
	pila->cantidad--;
	if(pila->cantidad < pila->capacidad/ CUARTO){
		redimensionar(pila, pila->capacidad/ MITAD);
	}
	return pila->datos[pila->cantidad];
}
