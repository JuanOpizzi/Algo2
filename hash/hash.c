#include "lista.h"
#include "hash.h"
#include "testing.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CANT_INICIAL 0
#define TAM_INICIAL 101000
#define VAL_RED 6
#define FACT_CARGA 0.8

/* Silvestri, María Carolina - 99175 */
/* Opizzi, Juan Cruz - 99807 */

// 24/6/17 Hash aprobado

/*--------------------Definición de las estructuras-------------------*/

typedef struct hash{
		size_t cant;
		size_t tam;
		lista_t** tabla;
		hash_destruir_dato_t destructor;
}hash_t;

typedef struct campo{
	char* clave;
	void* dato;	
}campo_t;

typedef struct hash_iter{
	const hash_t* hash;
	lista_iter_t* iter_lista; // LO CAMBIE! confundía mucho...
	size_t cant_it;
	size_t pos_act;
}hash_iter_t;

/*---------------Declaración de funciones auxiliares------------------*/

typedef void (*hash_destruir_dato_t)(void *);

size_t hashing(const char *key, size_t largo);

campo_t* campo_crear(void* dato, char* clave);

bool redimensionar(hash_t* hash, size_t nuevo_tam);

float factor_carga(hash_t* hash);

lista_iter_t* auxiliar(hash_t* hash, const char* clave);

/*-----------------------PRIMITIVAS DEL HASH--------------------------*/

//CREAR
hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
	hash_t* hash = malloc(sizeof(hash_t));
	if(!hash){
		return NULL;
	}		
	lista_t** lista = malloc(TAM_INICIAL * sizeof(lista_t*));
	if(!lista){
		free(hash);
		return NULL;
	}
	hash->tabla = lista;
	for (int i = 0; i < TAM_INICIAL; i++){
		hash->tabla[i] = lista_crear();
	}
	hash->cant = CANT_INICIAL;
	hash->tam = TAM_INICIAL;
	hash->destructor = destruir_dato;
	return hash;
}

//GUARDAR
bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	//Condicion redimension
	if(factor_carga(hash) >= FACT_CARGA){
		if(!redimensionar(hash, hash->tam * VAL_RED)){
			return false;
		}	
	}
	//Copio la clave
	char* clave_copia = malloc(strlen(clave)+1);
	if(!clave_copia){
		return false;
	}
	strcpy(clave_copia, clave);
	lista_iter_t* iter_lista = auxiliar(hash, clave_copia);
	//Actualizo
	if(!lista_iter_al_final(iter_lista)){
		campo_t* aux = lista_iter_ver_actual(iter_lista);
		if(hash->destructor){
			hash->destructor(aux->dato);
		}
		aux->dato = dato;	
		free(clave_copia);
		lista_iter_destruir(iter_lista);
		return true;
	}
	campo_t* nuevo = campo_crear(dato, clave_copia);
	if(!nuevo){
		free(clave_copia);
		lista_iter_destruir(iter_lista);
		return false;
	}
	// Es nuevo entonces inserto
	lista_iter_insertar(iter_lista, nuevo);	
	hash->cant++;
	lista_iter_destruir(iter_lista);
	return true;	
}

//PERTENECE
bool hash_pertenece(const hash_t *hash, const char *clave){
	lista_iter_t* iter_lista = auxiliar((hash_t*)hash, clave);
	if(!iter_lista){ 
		return false;
	}
	if(lista_iter_al_final(iter_lista)){
		lista_iter_destruir(iter_lista);
		return false;
	}
	lista_iter_destruir(iter_lista);
	return true;
}

//BORRAR
void *hash_borrar(hash_t *hash, const char *clave){
	if(!hash_pertenece(hash, clave)){
		return NULL;
	}
	lista_iter_t* iter_lista = auxiliar(hash, clave);
	if(lista_iter_al_final(iter_lista)){
		lista_iter_destruir(iter_lista);
		return NULL;
	}
	campo_t* aux = lista_iter_ver_actual(iter_lista);
	void* dato = aux->dato;
	free(aux->clave);
	free(aux);
	lista_iter_borrar(iter_lista);
	lista_iter_destruir(iter_lista);
	hash->cant--;
	return dato;
}

//OBTENER
void *hash_obtener(const hash_t *hash, const char *clave){
	size_t pos = hashing(clave, hash->tam);
	if(!hash->tabla[pos]){
		return NULL;
	}
	lista_iter_t* iter_lista = auxiliar((hash_t*) hash, clave);
	if(!lista_iter_al_final(iter_lista)){
		campo_t* aux = lista_iter_ver_actual(iter_lista);
		lista_iter_destruir(iter_lista);
		return aux->dato;
	}
	lista_iter_destruir(iter_lista);
	return NULL;
}

//CANTIDAD
size_t hash_cantidad(const hash_t *hash){
	return hash->cant;
}

//DESTRUIR
void hash_destruir(hash_t *hash){
	for(int i = 0; i < hash->tam ; i++){
		if(hash->tabla[i]){
			lista_iter_t* iter_lista = lista_iter_crear(hash->tabla[i]);
			while(!lista_iter_al_final(iter_lista)){
				campo_t* aux = lista_iter_ver_actual(iter_lista);
				if(hash->destructor){
					hash->destructor(aux->dato);
				}
				free(aux->clave);
				free(aux);
				lista_iter_avanzar(iter_lista);
			}
		lista_iter_destruir(iter_lista);
		lista_destruir(hash->tabla[i], NULL);
		}	
	}
	free(hash->tabla);
	free(hash);
}

/*---------------------PRIMITIVAS DEL ITERADOR------------------------*/

//CREAR ITER
hash_iter_t *hash_iter_crear(const hash_t *hash){
	if(!hash){
		return NULL;
	}
	hash_iter_t* iter = malloc(sizeof(hash_iter_t));
	if(!iter){
		return NULL;
	}
	iter->hash = hash;
	iter->iter_lista = NULL;
	size_t pos = CANT_INICIAL;
	while (pos < hash->tam){
		if(hash->tabla[pos]){
			if(!lista_esta_vacia(iter->hash->tabla[pos])){
				iter->pos_act = pos;
				iter->iter_lista = lista_iter_crear(iter->hash->tabla[pos]);
				break;
			}
		}
		pos++;
	}
	iter->cant_it = 0;
	return iter;
}

//ITER AL FINAL
bool hash_iter_al_final(const hash_iter_t *iter){
	if(hash_cantidad(iter->hash) == iter->cant_it){
		 return true;
	}
	if(lista_iter_al_final(iter->iter_lista)){
		size_t i = iter->pos_act+1;
		while(i < iter->hash->tam){
			if(!iter->hash->tabla[i]){
				return false;
			}
			i++;
		}
		return true;	
	}
	return false;
}

//ITER AVANZAR
bool hash_iter_avanzar(hash_iter_t *iter){
	if(hash_iter_al_final(iter)){
		return false;
	}	
	iter->cant_it++;
	lista_iter_avanzar(iter->iter_lista);
	if (!lista_iter_al_final(iter->iter_lista)) {
        	return true;
    	}
    	lista_iter_destruir(iter->iter_lista);
	iter->iter_lista = NULL;
    	for(size_t i = iter->pos_act+1; i<iter->hash->tam; i++){
		if(!lista_esta_vacia(iter->hash->tabla[i])){
			iter->pos_act = i;
			iter->iter_lista = lista_iter_crear(iter->hash->tabla[i]);
			return true;
		}
	}
	return false;
}

//VER ACTUAL
const char *hash_iter_ver_actual(const hash_iter_t *iter){
	if(hash_iter_al_final(iter)){
		return NULL;
	}
	campo_t* celda = lista_iter_ver_actual(iter->iter_lista);
	return celda->clave;
}

//DESTRUIR
void hash_iter_destruir(hash_iter_t* iter){	
	lista_iter_destruir(iter->iter_lista);
	free(iter);
}

/*-----------------------FUNCIONES AUXILIARES-------------------------*/

//HASHING
size_t hashing(const char *key, size_t largo){
    size_t hash, i;
    for(hash = i = 0; i < strlen(key); ++i){
    	size_t aux = (size_t)(key[i]);
        hash += aux;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    	}
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    hash %= largo;
    return hash;
}

//CREAR CAMPO
campo_t* campo_crear(void* dato, char* clave){
	campo_t* campo = malloc(sizeof(campo_t));	
	if(!campo){
		return NULL;
	}
	campo->clave = clave;
	campo->dato = dato;
	return campo;
}	

//FACTOR DE CARGA
float factor_carga(hash_t* hash){
	float factor = (float)(hash->cant/hash->tam);
	return factor;
}

//REDIMENSIONAR
bool redimensionar(hash_t* hash, size_t nuevo_tam){
	lista_t** tabla_nueva = malloc(nuevo_tam * sizeof(lista_t*));
	size_t cant = hash->cant;
	if(!tabla_nueva){
		return false;
	}
	for(int i = 0; i < nuevo_tam; i++){
		tabla_nueva[i] = lista_crear();
	}
	for(int j = 0; j < hash->tam; j++){
		if(hash->tabla[j]){
			while(!lista_esta_vacia(hash->tabla[j])){
				campo_t* aux = lista_borrar_primero(hash->tabla[j]);
				size_t pos = hashing(aux->clave, nuevo_tam);
				lista_insertar_ultimo(tabla_nueva[pos],aux);
			}
			lista_destruir(hash->tabla[j], NULL);
		}
	}	
	free(hash->tabla);
	hash->tabla = tabla_nueva;
	hash->tam = nuevo_tam;
	hash->cant = cant;
	return true;
}

lista_iter_t* auxiliar(hash_t* hash, const char* clave){
	size_t pos = hashing(clave, hash->tam);
	lista_iter_t* iter_lista = lista_iter_crear(hash->tabla[pos]);
	if(!iter_lista){
		return NULL;
	}
	while(!lista_iter_al_final(iter_lista)){
		campo_t* aux = lista_iter_ver_actual(iter_lista);
		if(strcmp(clave, aux->clave) == 0){
			return iter_lista;
		}
		lista_iter_avanzar(iter_lista);
	} 	
	return iter_lista;
}
