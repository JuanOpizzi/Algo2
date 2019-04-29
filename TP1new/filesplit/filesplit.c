#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ARCH_MAX 9999


void filesplit(FILE* arch, int N){
	FILE *arch_out;
	char buffer_arch[N];
	char* buffer_leer = malloc(N + 1);
	if(!buffer_leer){
		return ;
	}
	int i = 1;
	while (!feof(arch) && i <= ARCH_MAX){
		fread(buffer_leer, 1, N, arch);
		buffer_arch[N] = '\0';
        	sprintf(buffer_arch,"archivo.txt_%04d", i);
        	arch_out = fopen(buffer_arch, "w");
        	fwrite(buffer_leer, sizeof(char), N, arch_out);
		fclose(arch_out);
		i++;
    	}
    	free(buffer_leer);
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
		filesplit(arch, n);
		fclose(arch);
		return 0;
	}		
	return 1;
}
