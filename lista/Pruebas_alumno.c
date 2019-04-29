#include "lista.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>

#include <stdio.h>
#include <stdlib.h>



/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
	
void prueba_lista_vacia(){
	printf("Prueba 01\n");
	lista_t* lista_vacia = lista_crear();
	print_test("Mi lista esta vacia", lista_esta_vacia(lista_vacia));
	print_test("Mi lista tiene cero elementos", lista_largo(lista_vacia) == 0);
	print_test("La lista carece de un primer elemento", lista_ver_primero(lista_vacia) == NULL);
	print_test("La lista no tiene nigun elemento al final", lista_ver_ultimo(lista_vacia) == NULL);
	print_test("Intento borrar y recibo NULL", lista_borrar_primero(lista_vacia) == NULL);
	lista_destruir(lista_vacia, NULL);	
	print_test("La lista fue destruida", true);
}

void prueba_lista_insertar(){
	printf("Prueba 02\n");
	lista_t* lista_insert = lista_crear();
	print_test("Veo que la lista esta vacia", lista_esta_vacia(lista_insert));
	printf("Inserto elementos del mismo tipo\n");	
	int arreglo[] = {505, 200, 3500};
	lista_insertar_primero(lista_insert, &arreglo[0]);	
	print_test("Veo el primer elemento de la lista", lista_ver_primero(lista_insert) == &arreglo[0]);
	lista_insertar_primero(lista_insert, &arreglo[1]);
	print_test("Veo el primer elemento de la lista", lista_ver_primero(lista_insert) == &arreglo[1]);
	print_test("Veo el ultimo elemento de la lista", lista_ver_ultimo(lista_insert) == &arreglo[0]);
	lista_insertar_ultimo(lista_insert, &arreglo[2]);
	print_test("Veo el ultimo elemento de la lista", lista_ver_ultimo(lista_insert) == &arreglo[2]);
	print_test("Veo el largo de la lista", lista_largo(lista_insert) == 3);
	print_test("Borro mi primer elemento de la lista", lista_borrar_primero(lista_insert) == &arreglo[1]);
	print_test("Veo el largo de la lista", lista_largo(lista_insert) == 2);
	lista_destruir(lista_insert, NULL);	
	print_test("La lista fue destruida", true);
}

void prueba_lista_iterar_vacio(){
	printf("Prueba 03\n");
	lista_t* lista_void = lista_crear();
	printf("Utilizo el iterador insertando al principio y fin y luego veo que este todo bien\n");	
	lista_iter_t* iter = lista_iter_crear(lista_void);
	print_test("Estoy al final de la lista", lista_iter_al_final(iter));
	char* cadena[] = {"Hola", "Mundo", "Chau"};
	print_test("Inserto en la lista con el iterador", lista_iter_insertar(iter, &cadena[0]));
	print_test("Inserto en la lista con el iterador", lista_iter_insertar(iter, &cadena[1]));
	print_test("Veo el ACTUAL elemento del iterador", lista_iter_ver_actual(iter) == &cadena[1]);
	print_test("Veo el ultimo elemento de la lista", lista_ver_ultimo(lista_void) == &cadena[0]);	
	print_test("Itero al SIGUIENTE elemento de la lista", lista_iter_avanzar(iter));
	print_test("NO estoy al final de la lista", !lista_iter_al_final(iter));
	print_test("Borro el ultimo elemento de la lista", lista_iter_borrar(iter) == &cadena[0]);
	print_test("Estoy al final de la lista", lista_iter_al_final(iter));
	print_test("Inserto en la lista con el iterador", lista_iter_insertar(iter, &cadena[2]));
	lista_iter_destruir(iter);
	lista_destruir(lista_void, NULL);
	print_test("La lista y el iterador fueron destruidos", true);
}

void prueba_lista_iterar(){	
	printf("Prueba 04\n");
	lista_t* la_lista = lista_crear();
	printf("Recorro una lista con el iterador\n");
	print_test("Veo que la lista esta vacia", lista_esta_vacia(la_lista));
	char* arr[] = {"F","S","D"};
	lista_insertar_primero(la_lista, &arr[0]);
	lista_insertar_ultimo(la_lista, &arr[1]);
	lista_insertar_ultimo(la_lista, &arr[2]);
	lista_iter_t* el_iter = lista_iter_crear(la_lista);
	print_test("Veo que la lista no esta vacia", !lista_esta_vacia(la_lista));
	print_test("Veo el primero elemento de la lista", lista_iter_ver_actual(el_iter) == &arr[0]);
	print_test("Me fijo que no llegue al final de la lista", !lista_iter_al_final(el_iter));	
	print_test("Itero al siguiente elemento de la lista", lista_iter_avanzar(el_iter));
	print_test("Veo el segundo elemento de la lista", lista_iter_ver_actual(el_iter) == &arr[1]);
	print_test("Itero al siguiente elemento de la lista", lista_iter_avanzar(el_iter));
	print_test("Veo el ultimo elemento de la lista", lista_iter_ver_actual(el_iter) == &arr[2]);
	print_test("Estoy en el ultimo elemento pero el iterador no llego al final", !lista_iter_al_final(el_iter));
	print_test("Itero al final de la lista", lista_iter_avanzar(el_iter));
	print_test("Estoy en al final de la lista", lista_iter_al_final(el_iter));
	lista_iter_destruir(el_iter);
	lista_destruir(la_lista, NULL);
	print_test("La lista y el iterador fueron destruidos", true);
}

void prueba_lista_iterar2(){
	printf("Prueba 05\n");
	lista_t* lista2 = lista_crear();
	printf("Utilizo el iterador para insertar y borrar\n");
	print_test("Veo que la lista esta vacia", lista_esta_vacia(lista2));
	int arr[] = {40, 50, 60};
	lista_insertar_primero(lista2, &arr[0]);
	lista_insertar_ultimo(lista2, &arr[1]);
	lista_iter_t* iter2 = lista_iter_crear(lista2);
	print_test("Veo que la lista no esta vacia", !lista_esta_vacia(lista2));
	print_test("Veo el primero elemento  de la lista", lista_iter_ver_actual(iter2) == &arr[0]);
	print_test("Inserto en la lista con el iterador", lista_iter_insertar(iter2, &arr[2]));
	print_test("Verifico con la lista que inserte al principio de la lista", lista_ver_primero(lista2) == &arr[2]);
	print_test("Veo el actual elemento de la lista", lista_iter_ver_actual(iter2) == &arr[2]);
	print_test("Itero al siguiente elemento de la lista", lista_iter_avanzar(iter2));
	print_test("Veo el segundo elemento de la lista", lista_iter_ver_actual(iter2) == &arr[0]);
	print_test("Itero al ultimo elemento de la lista", lista_iter_avanzar(iter2));
	print_test("Veo el ultimo elemento de la lista", lista_iter_ver_actual(iter2) == &arr[1]);
	print_test("Verifico con la lista que inserte al final de la lista con el iterador", lista_ver_ultimo(lista2) == &arr[1]);
	print_test("Me fijo que no llegue al final de la lista", !lista_iter_al_final(iter2));
	print_test("Borro el ultimo elemento de la lista", lista_iter_borrar(iter2) == &arr[1]);
	lista_iter_destruir(iter2);
	lista_destruir(lista2, NULL);
	print_test("La lista y el iterador fueron destruidos", true);
}

void prueba_lista_iter_borrar(){
	printf("Prueba 06\n");
	printf("Utilizo el iterador borrando al principio y fin y luego veo que este todo bien\n");
	lista_t* lista = lista_crear();
	int arr[] = {1,2,3,14};
	lista_insertar_primero(lista, &arr[0]);
	lista_insertar_ultimo(lista, &arr[1]);
	lista_insertar_ultimo(lista, &arr[2]);
	lista_insertar_ultimo(lista, &arr[3]);
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("Veo el primero de la lista", lista_iter_ver_actual(iter) == &arr[0]);
	print_test("Borro el primer elemento de la lista", lista_iter_borrar(iter) == &arr[0]); 
	print_test("Uso la lista para ver que el primer elemento se borro", lista_ver_primero(lista) == &arr[1]);//
	print_test("Avanzo el iterador", lista_iter_avanzar(iter));
	print_test("Avanzo el iterador", lista_iter_avanzar(iter));
	print_test("Borro el ultimo elemento de la lista", lista_iter_borrar(iter) == &arr[3]); 
	print_test("Uso la lista para ver que elimine el ultimo elemento", lista_ver_ultimo(lista) == &arr[2]);//
	lista_iter_destruir(iter);
	lista_destruir(lista, NULL);
	print_test("La lista y el iterador fueron destruidos", true);
}
  
void prueba_lista_destruir(){
	printf("Prueba 07\n");
	lista_t* lista_dest = lista_crear();
	pila_t* pila01 = pila_crear();
	pila_t* pila02 = pila_crear();
	pila_t* pila03 = pila_crear();
	pila_apilar(pila01, "1");
	pila_apilar(pila01, "2");
	pila_apilar(pila01, "3");
	pila_apilar(pila02, "4");
	pila_apilar(pila02, "5");
	pila_apilar(pila02, "6");
	pila_apilar(pila03, "7");
	pila_apilar(pila03, "8");
	pila_apilar(pila03, "9");
	print_test("La lista esta vacia", lista_esta_vacia(lista_dest));
	lista_insertar_primero(lista_dest, pila01);
	lista_insertar_ultimo(lista_dest, pila02);
	lista_insertar_ultimo(lista_dest, pila03);
	print_test("La lista no esta vacia", !lista_esta_vacia(lista_dest));
	void* destruir = pila_destruir;
	lista_destruir(lista_dest, destruir);
	print_test("La lista con 3 pilas insertadas fue destruida", true);
}

void pruebas_lista_alumno() {
	prueba_lista_vacia();
	prueba_lista_insertar();
	prueba_lista_iterar_vacio();
	prueba_lista_iterar();
	prueba_lista_iterar2();
	prueba_lista_iter_borrar();
	prueba_lista_destruir();
}







