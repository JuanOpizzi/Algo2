#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strutil.h"
#include "hash.h"
#include "heap.h"
#include "counting_filters.h"
#include "lista.h"

/*-------------Estructura auxiliar-------------*/

// SI LO LLAME IGUAL QUE EN EL HASH Y QUEEEE
typedef struct campo{
	const char* clave;
	size_t dato;	
}campo_t;

/*--------------Funciones Auxiliares----------*/

// igual que en procesar usuarios :D
void free_strv(char** strv){
	for(size_t i = 0;  strv[i] != NULL; i++){
		free(strv[i]);
	}
	free(strv);
}

// Comparacion
int cmp(const void* a, const void* b){
	if (((campo_t*)a)->dato < ((campo_t*)b)->dato){
		return 1;
	}else if (((campo_t*)a)->dato > ((campo_t*)b)->dato){
		return -1;
	}
	return 0;
}

/*-----------------HASHtags------------------*/


void imprimir_TT(heap_t* heap, int k){
	printf("TOP %d de tweets:\n", k);
	lista_t* lista = lista_crear(); // si uso una lista puedo devolver los tweets ordenados de forma descendente
	if(!lista){
		printf("No se pudo imprimir el TT\n");
		return;
	}
	while(!heap_esta_vacio(heap)){
		campo_t* campo = (campo_t*)heap_desencolar(heap);
		lista_insertar_primero(lista, campo);
	}
	while(!lista_esta_vacia(lista)){
		campo_t* val = (campo_t*)lista_borrar_primero(lista);		
		printf("tweet: %s ", val->clave);		
		printf("cant: %d\n", (int)val->dato); 
		free(val); // aca libero tambien la memoria de lo que desencolo
	}
	lista_destruir(lista, free);
}

void cargar_hash(hash_t* hash, int n){
	int i = 0;
	count_t* count = crear_counting();
	if (!count){ 
		return;
	}
	char* linea = NULL;
	size_t capacidad = 0;
	ssize_t longitud = getline(&linea, &capacidad, stdin);
	while(longitud != -1 && i < n){
		linea[strlen(linea)-1] = '\0';
		char** arreglo = split(linea, ',');
		for(int i = 1; arreglo[i]; i++){
			couting_guardar(count, arreglo[i]);
			size_t* veces = malloc(sizeof(size_t));
			if(!veces){
				destruir_counting(count);
				hash_destruir(hash);
				free(linea);
				return;
			}
			*veces = obtener_counting(count, arreglo[i]);
			hash_guardar(hash, arreglo[i], veces);	
		}	
		i++;
		longitud = getline(&linea, &capacidad, stdin);
		free_strv(arreglo);		
	}
	free(linea);
	destruir_counting(count);
}

void cargar_heap(heap_t* heap, hash_t* hash, hash_iter_t* iter ,int k){
	for(int j = 0; j < k; j++){
		const char* clave = hash_iter_ver_actual(iter);
		campo_t* nodo = malloc(sizeof(campo_t));
		if(!nodo){
			hash_iter_destruir(iter);
			heap_destruir(heap, NULL);
			return;
		}
		nodo->dato = *(size_t*)hash_obtener(hash, clave); //no me queda otra que caster
		nodo->clave = clave;		            // xq no puedo desreferenciar void*
		heap_encolar(heap, nodo);
		hash_iter_avanzar(iter);
	}
	while(!hash_iter_al_final(iter)){
		const char* clave = hash_iter_ver_actual(iter);
		size_t val_obt = *(size_t*)hash_obtener(hash, clave); //misma razon que arriba
		campo_t* val_nodo = heap_ver_max(heap);  //le saque el casteo, no cambio lo que devuelve la prueba pero lo dejo asi 
		if(!val_nodo){ 
			return;
		}
		if (val_obt >= val_nodo->dato){ //solo entra cuando son iguales 
			campo_t* nodo = malloc(sizeof(campo_t)); 
			if(!nodo){
				hash_iter_destruir(iter);
				heap_destruir(heap, NULL);
				return;
			}
			nodo->dato = val_obt;
			nodo->clave = clave;
			heap_encolar(heap, nodo);
			campo_t* aux = heap_desencolar(heap);
			free(aux);//libero la memoria de lo que desencolo		
		}
		hash_iter_avanzar(iter);
	}
}
void procesar_tweets(int n, int k){
	
	hash_t* hash = hash_crear(free);
	if (!hash){ 
		return;
	}
	cargar_hash(hash, n);
	hash_iter_t* iter = hash_iter_crear(hash);
	heap_t* heap = heap_crear(cmp);
	if (!iter || !heap){ 
		return;
	}
	cargar_heap(heap, hash, iter, k);
	imprimir_TT(heap, k);
	heap_destruir(heap, free);
	hash_iter_destruir(iter);
	hash_destruir(hash);
}

int main(int argc, char *argv[]) {
	if (argc != 3){	
		fprintf(stderr, "Error argumentos inválidos\n");
		return -1;	
	}
	int n = atoi(argv[1]); 
	int k = atoi(argv[2]); 
	if ( n < k ){
		fprintf(stderr, "Error argumentos inválidos\n");
		return -1;
	}		
	procesar_tweets(n, k);
	return 0;
}
