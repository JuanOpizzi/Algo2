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

#define CAPACIDAD_INICIAL 5
#define PILA_UN_CUARTO 4
#define PILA_MITAD  2


bool pila_redimensionar(pila_t* pila, size_t capacidad_nuevo);

pila_t* pila_crear(void) {
	pila_t* pila = malloc (sizeof(pila_t));	
	if (!pila) {
		return NULL;
	}
	pila->datos = malloc (CAPACIDAD_INICIAL*sizeof(void*));
	if (!pila->datos) {
		free(pila);
		return NULL;
	}
	pila->capacidad = CAPACIDAD_INICIAL;	
	pila->cantidad = 0;
	return pila;
}

void pila_destruir(pila_t *pila) {
	if (pila) {
		free(pila->datos);
		free(pila);
	}
}

bool pila_esta_vacia(const pila_t *pila) {
	if(!pila) {
		return true;
	}
	return (pila->cantidad == 0);
}

// No valido si la pila fue creada dentro de la primitiva porque eso ya se valida al llamar a pila_esta_vacia	 
void* pila_ver_tope(const pila_t *pila) {
	if (pila_esta_vacia(pila)) {
		return NULL;
	}
	return pila->datos[pila->cantidad-1];
}

bool pila_apilar(pila_t *pila, void* valor) {
	if (!pila) {
		return false; 
	}
	if (pila->cantidad == pila->capacidad) {
		if(!pila_redimensionar(pila, pila->capacidad*2)){
			return false;
		}
	}
	pila->datos[pila->cantidad] = valor;
	pila->cantidad ++;
	return true;
}

void* pila_desapilar(pila_t *pila) {	
	if (pila_esta_vacia(pila)) {
		return NULL;
	}
	void* valor_desapilado = pila->datos[pila->cantidad-1];
	pila->cantidad --;
	if (pila->cantidad < (pila->capacidad / PILA_UN_CUARTO)) {
		pila_redimensionar(pila, pila->capacidad /PILA_MITAD);
	}
	return valor_desapilado;
}

bool pila_redimensionar(pila_t* pila, size_t capacidad_nuevo) {
	if(!pila) {
		return false;
	}
	if(capacidad_nuevo == 0) {
		capacidad_nuevo = CAPACIDAD_INICIAL;
	}    
  	void** datos_nuevo = realloc(pila->datos, capacidad_nuevo * sizeof(void*));
	if (!datos_nuevo) {
        	return false;
	}
    	pila->datos = datos_nuevo;
    	pila->capacidad = capacidad_nuevo;
    	return true;
}






