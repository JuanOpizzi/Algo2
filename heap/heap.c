#include "heap.h"
#include <stdlib.h>
#include <string.h>
#define TAM  75
#define REDUCIR 2
#define AGRANDAR 2

// Opizzi, Juan Cruz - 99807 
// Silvestri, María Carolina - 99175
// Corrige: Martín Buchwald


//HEAP APROBADO	
/* *****************************************************************
 *           		DEFINICION DE ESTRUCTURAS					   *
 * *****************************************************************/

struct heap{
	size_t cant;
	size_t tam; 
	void** vector;
    cmp_func_t cmp;
};

/* *****************************************************************
 *          	 DEFINICION DE PRIMITIVAS AUXILIARES			   *
 * *****************************************************************/

void upheap(void* arreglo[], size_t posicion, cmp_func_t cmp);

void downheap(void* arreglo[], size_t N, size_t pos, cmp_func_t cmp);

void heapify(void* arreglo[], size_t N, cmp_func_t cmp);

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp);

void swap(void** elem1,void** elem2);

bool heap_redimensionar(heap_t* heap, size_t tam_nuevo);

/* *****************************************************************
 *                    	PRIMITIVAS DEL HEAP						   *
 * *****************************************************************/

heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap){
		return NULL;
	}
	heap->cmp    = cmp;
	heap->tam    = TAM;
	heap->cant   = 0;
	void** vector = malloc(heap->tam*sizeof(void*));
	if(!vector){
		free(heap);
		return NULL;
	}
	heap->vector  = vector; 
	return heap;
}	

size_t heap_cantidad(const heap_t *heap){
	return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap){
	return heap->cant == 0;
}	

void *heap_ver_max(const heap_t *heap){
	if(!heap_esta_vacio(heap)){
		return heap->vector[0];
	}
	return NULL;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	void ** elem = malloc(sizeof(void*) *n);
	for (int i = 0; i < n; i ++){
		elem[i] = arreglo[i];
	}
	heapify(elem,n,cmp);
	heap_t* heap = malloc(sizeof(heap_t));
	if (!heap){
		return NULL;
	}
	heap->vector = elem;
	heap->cant   = n;
	heap->tam    = n ;
	heap->cmp    = cmp;
	return heap;
}

bool heap_encolar(heap_t *heap, void *elem){
	if (!elem){
		return false;
	}
	if (heap->cant >= heap->tam){
		bool redimension = heap_redimensionar(heap, AGRANDAR * heap->tam);
		if (!redimension){
			return false;
		}
	}
	size_t pos = heap->cant;
	heap->vector[pos] = elem;
	heap->cant++;
	upheap(heap->vector, pos, heap->cmp);
	return true;
}

void *heap_desencolar(heap_t *heap){
	if(heap_cantidad(heap) == 0 ){ 
		return NULL;
	}
	void * maximo = heap_ver_max(heap);
	void * intercambio = heap->vector[heap->cant-1];
	heap->vector[0]    = intercambio;
	heap->vector[heap->cant-1] = maximo;
	heap->cant--;
	downheap(heap->vector, heap->cant, 0, heap->cmp);
	if (heap->cant < heap->tam / REDUCIR){
		bool redimension = heap_redimensionar(heap, heap->tam / REDUCIR);
		if (!redimension){
			return NULL;
		}
	}
	return maximo;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	if (destruir_elemento){
		while (!heap_esta_vacio(heap)){
			destruir_elemento(heap_desencolar(heap));
		}
	}
	free(heap->vector);
	free(heap);
}	

/* *****************************************************************
 *                    FUNCIONES AUXILIARES						   *
 * *****************************************************************/

void upheap(void* arreglo[], size_t posicion, cmp_func_t cmp){
	if(posicion == 0){
		return;
	}
	size_t padre = (posicion-1)/2;
	if(cmp(arreglo[padre] , arreglo[posicion]) < 0){
		swap(&arreglo[padre], &arreglo[posicion]);
		upheap(arreglo, padre, cmp);
	}
}

void downheap(void* arreglo[], size_t n, size_t pos, cmp_func_t cmp){
	if(n <= pos){
		return;
	}
	size_t max      = pos;
	size_t hijo_izq = 2*pos + 1;
	size_t hijo_der = 2*pos + 2; //hijo_izq + 1
	if((hijo_izq < n) && (cmp(arreglo[hijo_izq],arreglo[max]) > 0)){
		max = hijo_izq;
	}
	if((hijo_der < n) && (cmp(arreglo[hijo_der],arreglo[max]) > 0)){
		max = hijo_der;
	}
	if(max != pos){
		swap(&arreglo[max], &arreglo[pos]);
		downheap(arreglo, n, max, cmp);
	}
}

void heapify(void* arreglo[], size_t n, cmp_func_t cmp){
	for(int i = (int)n/2; i >= 0; i--){
		downheap(arreglo, n, i, cmp);
	}		
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heapify(elementos,cant,cmp);
	int n = (int)cant-1;
	for( int i = n; i < cant; i--){
		swap(&elementos[0],&elementos[i]);
		downheap(elementos, i, 0,cmp);
	}
}

void swap(void** elem1,void** elem2){
	void* guardado = *elem1;
	*elem1 = *elem2;
	*elem2 = guardado;
}

bool heap_redimensionar(heap_t* heap, size_t tam_nuevo) {
    	void* vector_nuevo = realloc(heap->vector, sizeof(void*) * tam_nuevo);
	if (!vector_nuevo){
		return false;
	}
	heap->vector = vector_nuevo;
	heap->tam = tam_nuevo;	
    	return true;
}
