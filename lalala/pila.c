#include "pila.h"
#include <stdlib.h>

#include <stdio.h>


/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

#define CAPACIDAD 5

bool pila_redimensionar(pila_t* pila, size_t capacidad_nuevo);

pila_t* pila_crear(void) {
	pila_t* pila = malloc (sizeof(pila_t));	
	if (pila == NULL) {
		return NULL;
		}
	pila->datos = malloc (CAPACIDAD*sizeof(void*));
	pila->capacidad = CAPACIDAD;	
	pila->cantidad = 0;
	return pila;
}

void pila_destruir(pila_t *pila) {
	if (pila != NULL) {
		free(pila->datos);
		free(pila);
		}
}

bool pila_esta_vacia(const pila_t *pila) {
	return (pila->cantidad == 0);
}

void* pila_ver_tope(const pila_t *pila) {
	if (pila->cantidad == 0) {
		return NULL;
		}
	return pila->datos[pila->cantidad-1];
}

bool pila_apilar(pila_t *pila, void* valor) {
	if (pila->cantidad == pila->capacidad) {
		if(pila_redimensionar(pila, pila->capacidad*2) == false){
			return false;
			}
		}
	pila->datos[pila->cantidad] = valor;
	pila->cantidad += 1;
	return true;
}

void* pila_desapilar(pila_t *pila) {
	void* valor_desapilado;	
	if (pila->cantidad == 0) {
		return NULL;
		}
	valor_desapilado = pila->datos[pila->cantidad-1];
	pila->cantidad -= 1;
	if (pila->cantidad < (pila->capacidad / 4)){
		pila_redimensionar(pila, pila->capacidad/2);
		}
	return valor_desapilado;
}

bool pila_redimensionar(pila_t* pila, size_t capacidad_nuevo) {
  	void** datos_nuevo = realloc(pila->datos, capacidad_nuevo * sizeof(void*));
	if(capacidad_nuevo == 0){
		capacidad_nuevo = CAPACIDAD;
		}    
	if (datos_nuevo == NULL) {
        	return false;
    		}
    	pila->datos = datos_nuevo;
    	pila->capacidad = capacidad_nuevo;
    	return true;
}






