#ifndef LISTA_H
#define LISTA_H
#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */

struct lista;
typedef struct lista lista_t;

typedef struct lista_iter lista_iter_t;
/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos insetados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al comienzo
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void* lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t* lista);

// Devuelve el largo de la lista, devuelve 0 si la lista esta vacia.
// Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

// Crea un iterador para la lista.
// Post: devuelve un iterador colocado en el primer elemento de la lista si es que existe,
// si la lista esta vacia el iterador apunta a NULL.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza una posicion al iterador dentro de la lista devolviendo true,
// devuelve false en otro caso.
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el elemento de la lista al que esta apuntando el iterador en ese momento.
// Devuelve NULL en caso de que la lista este vacia.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve verdadero o falso, según si el iterador llego o no al final de la lista.
// Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador si este ya llego al final de la lista.
// Pre: el iterador fue creado.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un elemento en la lista previo al elemento que esta apuntando el iterador, 
// el iterador ahora apunta al elemento insertado y el siguiente es el elemento que estaba
// apuntando el iterador.
// Pre: el iterador fue creado.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Elimina el elemento de la lista al que el iterador este apuntando.
// Pre: la lista fue creada.
// Post: se elimino el actual elemento del iterador y esta apunta al siguiente.
void *lista_iter_borrar(lista_iter_t *iter);

// Recorre la lista entera y permite utilizar los elementos de la lista sin modificarlos,
// Pre: visitar es una funcion que se recibe por parametro la cual recibe el dato de la lista
// y un elemento extra con el que hara lo que quiera con el dato de la lista.
// Post: la lista fue creada, itera de forma automatica. 
void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_alumno.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.

void pruebas_lista_alumno(void);



#endif // LISTA_H
