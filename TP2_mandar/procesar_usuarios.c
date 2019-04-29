#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strutil.h"
#include "hash.h"
#include "lista.h"
// no me quedo otra que copiar al especial
void free_strv(char** strv){
	for(size_t i = 0;  strv[i] != NULL; i++){
		free(strv[i]);
	}
	free(strv);
}

//Esto lo traje devuelta a la vida para hallar el maximo de hashtags 
size_t maximo(hash_t* hash) {
	hash_iter_t* iter = hash_iter_crear(hash);
	if(!iter){
		return -1;
	}	
	size_t pos = 0;
	while(!hash_iter_al_final(iter)){
		const char* aux = hash_iter_ver_actual(iter);
		size_t     cant = *(size_t*) hash_obtener(hash, aux);
		if (pos < cant){
			pos = cant;
		}
		hash_iter_avanzar(iter);
	}
	hash_iter_destruir(iter);
	return pos;
}

hash_t* cargar_hash(FILE* arch){
	char* linea = NULL;
	size_t capacidad = 0;
	hash_t* hash = hash_crear(free);
	if(!hash){
		fclose(arch);
		return NULL;
	}
	ssize_t longitud = getline(&linea, &capacidad, arch);
	while(longitud != -1){
		size_t a = 1; // para no contar al usuario
		linea[strlen(linea)-1] = '\0'; 
		char** arreglo = split(linea, ','); 		
		size_t* cant = malloc(sizeof(size_t)); // pido memoria para no pisar la variable
		if(!cant){
			free_strv(arreglo);
			free(linea);
			fclose(arch);
			hash_destruir(hash);
			return NULL;
		}
		while(arreglo[a]){
			a++;
		}
		*cant = a-1; // -1 para no contar al usuario y asigno la cantidad de hashtags
		if(hash_pertenece(hash, arreglo[0])){ // v
			*cant += *(size_t*)hash_obtener(hash, arreglo[0]);
		}
		hash_guardar(hash, arreglo[0], cant);
		longitud = getline(&linea, &capacidad, arch);
		free_strv(arreglo);
	}
	free(linea);
	return hash;
}

lista_t** diccionario_ordenado(hash_t* hash, size_t maximal){
	hash_iter_t* iter = hash_iter_crear(hash);
	if(!iter){
		hash_destruir(hash);
		return NULL;
	}
	lista_t** dic_lista = malloc(sizeof(lista_t*) * maximal);
	if(!dic_lista){
		hash_iter_destruir(iter);
		hash_destruir(hash);
		return NULL;
	}
	for(int j=0; j < maximal; j++){ 
		lista_t* lista = lista_crear();
		if (!lista){ 
			hash_destruir(hash);
			hash_iter_destruir(iter);
			free(dic_lista); 
			return NULL;
		} 
		dic_lista[j] = lista;
	} 
	while(!hash_iter_al_final(iter)){	
		char* clave = (char*)hash_iter_ver_actual(iter);
		size_t valor = *(size_t*)hash_obtener(hash,clave);		
		lista_insertar_primero(dic_lista[valor-1],clave); // no se si este -1 soluciona el problema, pero al menos asi corre todo
		hash_iter_avanzar(iter);	
	}
	hash_iter_destruir(iter);
	return dic_lista;
}

void imprimir(lista_t** dic_lista, size_t maximal){
	printf("Usuarios: \n");
	for(int i = 0; i < maximal; i++){
		if(lista_esta_vacia(dic_lista[i])){
			lista_destruir(dic_lista[i], NULL);	
			continue;
		}
		printf("%d: ",i+1); //asi arreglo que los usuarios que tienen 1 tweet no aparezcan con 0 tweets
				    //en realidad pasa para todos los usuarios pero asi me di cuenta
				    //fbarrios tiene 9 tweets y devuelvo que tiene 9
				    //lo mismo con military_tech, tiene 2, devuelve 2	
		while(!lista_esta_vacia(dic_lista[i])){
			char* aux = (char*)lista_borrar_primero(dic_lista[i]);
			printf("%s,", aux);	
		}
		lista_destruir(dic_lista[i], NULL);
		printf("\n");		
	}	
}

void procesar_usuarios(FILE* arch){
	printf("hola\n");
	hash_t* hash = cargar_hash(arch);
	if(!hash){
		fclose(arch);
		return;
	}
	size_t maximal = maximo(hash); //Traumas de Discreta
	lista_t** dic_lista = diccionario_ordenado(hash, maximal);	
	if(!dic_lista){
		fclose(arch);
		return;
	}
	// Imprimo usuarios
	imprimir(dic_lista, maximal);
	free(dic_lista);
	hash_destruir(hash);
}

int main(int argc, char *argv[]) {
	if (argc == 0){
		fprintf(stderr, "Argumentos inválidos\n");
		return -1;	
	}
	FILE* arch = fopen(argv[1],"r"); 
	if(!arch){
		printf("No existe tal archivo\n");
		return -2;
	}	
	procesar_usuarios(arch);
	fclose(arch);
	return 0;
}


