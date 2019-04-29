#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Opizzi, Juan Cruz - 99807 
// Silvestri, María Carolina - 99175
// Corrige: Martín Buchwald

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNOS
 * *****************************************************************/

// Funciones auxiliares de comparación

int cmp_str (const void *a, const void *b){
	return(strcmp((char*)a, (char*)b));
}	

int cmp_num (const void *a, const void *b){
	if (*(int*)a > *(int*)b){
		return 1;
	}else if (*(int*)a < *(int*)b){
		return -1;
	}
	return 0;
}	

void pruebas_basicas(){
	
	int arreglo[] = {505, 200, 800, 750, 6};
	int largo1 = 5;
	
	heap_t* heap = heap_crear(cmp_num);
	
	print_test("Creo un heap",heap);
	print_test("Está vacío", heap_esta_vacio(heap));
	print_test("Tiene 0 elementos", heap_cantidad(heap) == 0);
	printf("\n");
	printf("~~Encolo los 3 primeros elementos de {505, 200, 800, 750, 6}\n");
	for(int i =0; i < (largo1-2); i++){
		heap_encolar(heap, &arreglo[i]);
	}
	print_test("El heap no esta vacío", !heap_esta_vacio(heap));
	print_test("La cantidad de elementos es 3", heap_cantidad(heap) == (largo1-2));
	print_test("El máximo de mi heap es 800", heap_ver_max(heap) == &arreglo[2]);
	
	print_test("Elimino el último elemento que encole en mi heap", heap_desencolar(heap) == &arreglo[2]);
	print_test("Elimino el segundo elemento que encole en mi heap", heap_desencolar(heap) == &arreglo[0]);
	print_test("Elimino el único elemento que queda en mi heap", heap_desencolar(heap) == &arreglo[1]);
	print_test("El heap esta vacío", heap_esta_vacio(heap));
	print_test("La cantidad de elementos es 0", heap_cantidad(heap) == 0);
	printf("\n");
	
	printf("~~Encolo los últimos 2 elementos de {505, 200, 800, 750, 6}\n");
	heap_encolar(heap, &arreglo[3]);
	heap_encolar(heap, &arreglo[4]);
	print_test("El heap no esta vacío", !heap_esta_vacio(heap));
	print_test("La cantidad de elementos es 2", heap_cantidad(heap) == 2);
	print_test("El máximo de mi heap es 750", heap_ver_max(heap) == &arreglo[3]);
	print_test("Elimino", heap_desencolar(heap) == &arreglo[3]);
	print_test("Elimino", heap_desencolar(heap) == &arreglo[4]);
	print_test("El heap esta vacío", heap_cantidad(heap) == 0);
	
	heap_destruir(heap, NULL);
	print_test("EL heap fue destruido", true);	
}

void pruebas_vacio(){
	heap_t* heap = heap_crear(cmp_str);
	
	print_test("Creo un heap",heap);
	print_test("Está vacío", heap_esta_vacio(heap));
	print_test("Tiene 0 elementos", heap_cantidad(heap) == 0);
	print_test("Desencolar un elemento tiene que ser NULL", heap_desencolar(heap) == NULL);
	
	heap_destruir(heap, NULL);
	print_test("EL heap fue destruido", true);		
}

void pruebas_heapsort(){
	
	char* l1 = "C";
	char* l2 = "A";
	char* l3 = "R";
	char* l4 = "O";
	
	void* nombre[] = {l1,l2,l3,l4};
	size_t largo = 4;
	
	printf("El que encolamos es: ");
	for(int i = 0; i < largo; i++){
		printf("%s", (char*)nombre[i]);
	}
	printf("\n");	
	
	heap_sort(nombre, largo, cmp_str);
	
	printf("Luego de aplicar heapsort queda: ");
	for(int j = 0; j < largo; j++){	
		printf("%s", (char*)nombre[j]);
	}
	printf("\n");
	print_test("Heapsort aplicado", true);
}

void pruebas_volumen(size_t largo){
	
	heap_t* heap = heap_crear(cmp_str);
	
	print_test("Creo un heap",heap);
	print_test("Está vacío", heap_esta_vacio(heap));
	print_test("Tiene 0 elementos", heap_cantidad(heap) == 0);
	
	const size_t largo_clave = 20;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%08d", i);
        ok = heap_encolar(heap, claves[i]);
        if (!ok) break;
    }

	print_test("Ver máximo es el elemento mas grande", heap_ver_max(heap) == claves[largo-1]);
    print_test("Almaceno muchos elementos", ok);
    print_test("La cantidad de elementos es correcta", heap_cantidad(heap) == largo);

    for (size_t i = largo; i > 0; i--){
		heap_desencolar(heap);
    }

    print_test("Borrar muchos elementos", ok);
    print_test("La cantidad de elementos es 0", heap_cantidad(heap) == 0);

    heap_destruir(heap, NULL);
    free(claves);
}

void pruebas_heap_arreglo(size_t largo){			
	
	char** vector01 = malloc(sizeof(char*) * largo);

    for (unsigned i = 0; i < largo; i++) {
        char sub_vec[40];
        sprintf(sub_vec, "%20d", i);
        vector01[i] = sub_vec;
    }

	heap_t* heap = heap_crear_arr((void*)vector01, largo, cmp_str);
		
	print_test("El heap no está vacío", !heap_esta_vacio(heap));
	printf("Se cargaron todos los valores \n");
	
	print_test("Veo el máximo", heap_ver_max(heap) == vector01[largo-1]);
	print_test("La cantidad de elementos es el largo", heap_cantidad(heap) == largo);
    	
	for (size_t i = largo; i > 0; i--){
		heap_desencolar(heap);
    }
    
	print_test("Desencolo todo", true);
    print_test("La cantidad de elementos es 0", heap_cantidad(heap) == 0);
	
	heap_destruir(heap, NULL);
	print_test("Destruyo el heap", true);
    free(vector01);
}


void pruebas_heap_alumno() {
    //PRUEBAS ALUMNO
	printf("...................................\nPRUEBAS BASICAS:\n\n");
	pruebas_basicas();
	printf(".....................................\nPRUEBAS VACIO:\n\n");
	pruebas_vacio();
	printf("...................................\nPRUEBAS VOLUMEN:\n\n");
	pruebas_volumen(500);
	printf("..................................\nPRUEBAS HEAPSORT:\n\n");
	pruebas_heapsort();
	printf("...........................\nPRUEBAS HEAP DE ARREGLO:\n\n");
	pruebas_heap_arreglo(500);
	printf("..................................\n~~~FIN PRUEBAS~~~\n\n");
}
