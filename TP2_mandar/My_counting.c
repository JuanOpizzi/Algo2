#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "counting_filters.h"

#define C_HASH 5
#define TAM_VEC 100003

typedef size_t (*f_hash_t) (const char *, size_t);

struct counting_filters{
	size_t** contadores;
	f_hash_t vec_func[C_HASH]; 
};

/*----------------------FUNCIONES DE HASHING--------------------------*/

// PRIMERA FUNCION DE HASHING
size_t hashing1(const char *key, size_t largo){
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

// SEGUNDA FUNCION DE HASHING
size_t hashing2(const char* clave,size_t tam){
    unsigned int num1 = 378551;
    unsigned int num2 = 63689;
    unsigned int clave_numerica = 0;
    for(int i = 0; *clave; clave++, i++){
	clave_numerica = clave_numerica * num2 + (*clave);
	num2 = num2 * num1;
    }
    return (clave_numerica%tam);
}

// TERCERA FUNCION DE HASHING
size_t hashing3(const char *key, /*(unsigned int)*/ size_t H_SIZE){
    unsigned int hash_val = 0;
    while( *key != '\0'){
	hash_val += *key++;
    }
    return( hash_val % H_SIZE);
}

// CUARTA FUNCION DE HASHING
size_t hashing4(const char *key, /*(unsigned int)*/size_t H_SIZE){
    unsigned int hash_val = 0;
    while( *key != '\0'){
	hash_val = (hash_val << 5) + *key++;
    }
    return( hash_val % H_SIZE);
}

// QUINTA FUNCION DE HASHING
size_t hashing5(const char *v, size_t largo){
    int h;	
    for(h = 0; *v != '\0'; v++){
	h = (64*h + *v) % 101;
    }
    return h;	
}	


/*------------------------AUXILIARES---------------------------------*/

// Búsqueda binaria para encontrar el mínimo
/*
size_t busq_min(size_t a_hash[], size_t ini, size_t fin){
	if(ini == fin){ 
		return a_hash[ini];
	}	
	size_t med = (ini+fin)/2;
	size_t izq = busq_min(a_hash, ini , med);
	size_t der = busq_min(a_hash, med+1, fin);
	if(izq > der){ 
		return der;
	}
	return izq;
}
*/
/* *****************************************************************
 *               PRIMITIVAS DEL COUNTING FILTERS				   *
 * *****************************************************************/

count_t* crear_counting(){
	count_t* count = malloc(sizeof(count_t));
	if (!count){ 
		return NULL;
	}
	size_t** arr = malloc(sizeof(size_t*) * C_HASH);
	if(!arr){
		free(count);
		return NULL;
	}
	count->contadores = arr;
	for (int i = 0; i < C_HASH; i++){
		count->contadores[i] = malloc(sizeof(size_t) * TAM_VEC);
		if(!count->contadores){
			for(int j = i; j>=0; j--){
				free(count->contadores[j]);
			}
			free(count->contadores);
			free(count);
			return NULL;
		}
	}//con esto obtuve los k contadores de tamaño TAM_VEC
	for(int a = 0; a < C_HASH; a++){
		for(int b = 0; b < TAM_VEC; b++){
			count->contadores[a][b] = 0;
		}
	}// con esto inicializo los k contadores de tamaño TAM_VEC	
	count->vec_func[0] = hashing1;
	count->vec_func[1] = hashing2;
	count->vec_func[2] = hashing3;
	count->vec_func[3] = hashing4;
	count->vec_func[4] = hashing5;
	return count;
}


//PRE: el counting fue creado
bool couting_guardar(count_t* count, const char* clave){
	for(int i = 0; i < C_HASH; i++){
		size_t pos = count->vec_func[i](clave, TAM_VEC);
		count->contadores[i][pos] += 1;
	}
	return true;	
}

//PRE: el counting fue creado
size_t obtener_counting(count_t* count, const char* clave){
	int a = 0;	
	size_t pos = count->vec_func[0](clave, TAM_VEC);
	for(int i = 1; i < C_HASH; i++){
		size_t pos1 = count->vec_func[i](clave, TAM_VEC);
		if(count->contadores[i][pos1] < count->contadores[i][pos]){
			a = i;
			pos = pos1;		
		}		
	}
	return count->contadores[a][pos];
}

void destruir_counting(count_t* count){
	for(int i = 0; i < C_HASH; i++){
		free(count->contadores[i]);
	}		
	free(count->contadores);
	free(count);	
}

