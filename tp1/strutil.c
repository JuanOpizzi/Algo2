#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE 
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>


void vector_inicializar(char** vector,size_t tam){
	for(int i = 0; i< tam;i ++){
		vector[i]= NULL;
	}
}

char** vector_crear(size_t tam) {
    char** vector = malloc(tam * sizeof(char*));

    if (vector == NULL) {
        return NULL;
    }

	vector_inicializar(vector,tam);
    return vector;
}


char** split (const char* str,char sep){
	char aux;
	aux = sep;
	char** arreglo = vector_crear(100);
	char* linea;
	char* inicial;
	char* fin;
	size_t arreglo_pos = 0;
	if(!aux || !str){
		return NULL;
	}
	linea = strdup(str);
	fin = linea;
	inicial = linea;
	while(inicial != NULL){
		strsep(&fin,&aux);
		arreglo[arreglo_pos] = strdup(inicial);
		arreglo_pos++;
		inicial = fin;
	}
	//arreglo[arreglo_pos] = NULL;
	free(linea);
	return arreglo;
}

void free_strv(char *strv[]){
        int i = 0;
	while(strv[i] != NULL) {
		free(strv[i]);
		i ++;
	}
	free(strv);
} 

char* join(char** strv, char sep){
	int tam = 0;
	int z   = 0;
	int i   = 0;
	size_t b= 0;
	while (strv[tam] != NULL){
		b += (strlen(strv[tam])+1);
		tam++;		
	}			
	char * cadena = malloc((b+1) * sizeof(char));
	if (tam == 0){ 
		cadena[0] = '\0';
		return cadena;
	}	
	for (int y=0; y < tam; y++){
		while(strv[y][z] != '\0'){ 
			cadena[i] = strv[y][z];
			i++;
			z++;		
		}
		cadena[i] = sep;
		i++;
		z=0;	
	}	
	cadena[i-1]= '\0';
	return cadena;
}


//tengo que liberar la memoria pedida por strdup igual que con el getline
