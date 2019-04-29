#include "strutil.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
	const char* arreglo = {"hola,mundo,como,estas,jeje"};
	int i = 0;
	char** retorno = split(arreglo, ',');
	while(i < 5){
		printf("%s \n", retorno[i]);
		i++;
	}
	for (int a=0; a<5; a++){
		free(retorno[a]);
	}
	free(retorno);
}
