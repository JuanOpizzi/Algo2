#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimir(char* linea, size_t ini, size_t fin){
	for(int i = (int)ini; i < (int)fin; i++){
		printf("%c", linea[i]);
	}
	printf("\n");	
}

void fixcol(FILE* arch, int N){
	char* linea      = NULL;
	size_t capacidad = 0;
	ssize_t longitud = getline(&linea, &capacidad, arch);
	char* puntero    = linea;
	while (longitud != -1){
		int bytes_leidos = 0;
		while(bytes_leidos < longitud){ 
			int faltante = (int) longitud - bytes_leidos;
			int tam = N;
			if(faltante < N){
				tam = faltante;	
			}
			char* cadena = malloc(sizeof(char)*(tam+1)); 
			if(!cadena){
				return;
			} 
			cadena[0] ='\0';
			memcpy(cadena,puntero,tam);
			puntero += tam;
			cadena[tam]='\0';
			fprintf(stdout, " %s\n",cadena);
			bytes_leidos += tam;
			free(cadena);
		}
		free(linea);
		linea    = NULL;
		longitud = getline(&linea,&capacidad,arch);
		puntero  = linea;
	}	
    	free(linea);
	return ;
}



int main(int argc, char *argv[]) {
	int n = atoi(argv[2]);	
	if (argc != 3){
		fprintf(stderr, "Error, la cantidad de archivos no es la correcta \n");
		return 1;	
	}		
	else if (n > 0){
		FILE* arch = fopen(argv[1],"r");		
		fixcol(arch, n);
		fclose(arch);
		return 0;
	}		
	return 1;
}

