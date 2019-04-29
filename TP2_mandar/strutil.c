#include "strutil.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Silvestri, María Carolina - 99175
// Corrige: Joaquín Torré

// FREE 
//~ void free_strv(char** strv){
	//~ for(size_t i = 0;  strv[i] != NULL; i++){
		//~ free(strv[i]);
	//~ }
	//~ free(strv);
//~ }

// SPLIT
char** split(const char* str, char sep){ 
	size_t cont_sep = 0, largo = strlen(str); 
	if(sep == '\0') return NULL;
	// Cuento cantidad de separadores
	for(int i = 0;  i < largo; i++){
		if(str[i] == sep) cont_sep++;
	}	
	char** cadenas_sep = malloc(sizeof(char*) * (cont_sep + 2));
	if(!cadenas_sep) return NULL;
	
	for(size_t i = 0; i < cont_sep+1; i++){
		size_t bits_copy = 0;
		for(int j = 0; j < largo; j++){
			if(str[j] == sep || str[j] =='\0') break;
			bits_copy++;
		}
		char* sub_cad = calloc(sizeof(char),(bits_copy + 1));
		if(!sub_cad){
			//~ free_strv(cadenas_sep);	
			return NULL;
		}
		cadenas_sep[i] = sub_cad; // Cad_sep apunta a sub_cad
		memcpy(sub_cad, str, bits_copy);
		str+= (bits_copy+1); // Avanzo el puntero
	}	
	cadenas_sep[cont_sep+1] = NULL;
	return cadenas_sep;
}

//JOIN
char* join(char** strv, char sep){
	if(!strv || sep == '\0') return NULL;
	size_t n = 0, tam_total = 0;
		
	// Cuento le largo total de la cadena final
	while(strv[n]){
		tam_total += (strlen(strv[n])+1);
		n++;
	}
	if(tam_total == 0 || !strv[0]){
		char* cad = malloc(sizeof(char));
		cad[0] = '\0';
		return cad;
	}
	char* cad = calloc(tam_total,sizeof(char));
	if(!cad) return NULL;
	char* buff = cad; // Buffer que apunte a la cadena
	
	for(size_t i = 0; i < n; i++){
		strcat(buff, strv[i]);
		buff+=strlen(strv[i]); // Avanzo el puntero
		if(strv[i+1]){
			buff[i] = sep;
			buff[i+1] = '\0';
		}
	}
	return cad;
}


	
	
