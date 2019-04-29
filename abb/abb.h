#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>

typedef struct abb abb_t;
typedef struct abb_iter abb_iter_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

/*----------------------PRIMITIVAS ABB--------------------------------*/

/* PRE: Crea un árbol binario de búsqueda. Recibe como parámetro la función de 
 * 		comparación a utilizar y la función para destrucción de datos. 
 * POST: Devuelve un puntero al ABB.
 */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/* Guarda un elemento en el ABB, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * PRE: La estructura ABB fue inicializada.
 * POST: Se almacenó el par (clave, dato).
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/* PRE: La estructura ABB fue inicializada.
 * POST Borro un elemento del ABB y de volvio el dato, de lo contrario,
 * 		 devolvio NULL;
 */
void *abb_borrar(abb_t *arbol, const char *clave);

/* PRE: La estructura ABB fue inicializada.
 * POST: Devuelve el valor obtenido del ABB, si la clave no se encuentra
 * 		 devuelve NULL.
 */
void *abb_obtener(const abb_t *arbol, const char *clave);

/* PRE: La estructura ABB fue inicializada.
 * POST: Si la clave pertenece al ABB devuelve True; de lo contrario,
 * 		 devuelve false
 */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/* PRE: La estructura ABB fue inicializada.
 * POST: Devuelve la cantidad de elementos del ABB.
 */
size_t abb_cantidad(abb_t *arbol);

/* PRE: La estructura ABB fue inicializada.
 * POST: Destruye la estructura liberando la memoria pedida y llamando a 
 * 		 la función destruir para cada par (clave, dato).
 */
void abb_destruir(abb_t *arbol);


/*-----------------------ITERADOR ABB---------------------------------*/

// CREAR ITERADOR
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

// AVANZAR
bool abb_iter_in_avanzar(abb_iter_t *iter);

// VER EL ACTUAL
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// ESTA AL FINAL
bool abb_iter_in_al_final(const abb_iter_t *iter);

// DESTRUIR ITERADOR
void abb_iter_in_destruir(abb_iter_t* iter);

// ITERADOR IN ORDER RECURSIVO
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

#endif 
