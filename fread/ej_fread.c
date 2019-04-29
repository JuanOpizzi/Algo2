#include<stdio.h>
#include<stdlib.h>

#define NOMBRE_ARCHIVO "lorem.txt"
#define CANT_BYTES 50

int main()
{
	FILE* archivo = fopen(NOMBRE_ARCHIVO, "r");
	if(!archivo) return -1;

	// Leo CANT_BYTES del archivo.
	char* buffer = malloc(CANT_BYTES + 1);
	if(!buffer) return -2;

	size_t res = fread(buffer, 1, CANT_BYTES, archivo);
	buffer[CANT_BYTES] = '\0';  // Solo porque en este ejemplo quiero imprimir.

	printf("buffer: %s\n", buffer);
	printf("res: %zd\n", res);
	
	// Veo cuanto se avanzo del archivo.
	printf("ftell: %ld\n", ftell(archivo));

	// Vuelvo a leer.
	res = fread(buffer, 1, CANT_BYTES, archivo);
	buffer[CANT_BYTES] = '\0';

	printf("buffer: %s\n", buffer);
	printf("res: %zd\n", res);
	
	free(buffer);
	fclose(archivo);
	return 0;
}