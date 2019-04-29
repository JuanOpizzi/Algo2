#include "strutil.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	int i = 0;
	const char* hola = {"hola,como,estas,todo,bien"};
	//char greeting[6] = {"H,e,l,l,o\0"};
	char** retorno = split(hola, ',');
	while(i < 5){
		printf("%s \n", retorno[i]);
		i++;
	}
	for (int a=0; a<1; a++){
		free(retorno[a]);
	}
	free(retorno);
}
