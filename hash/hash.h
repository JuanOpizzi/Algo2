#ifndef HASH_H
#define HASH_H
#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/


struct hash;
struct hash_iter;

typedef struct hash hash_t;
typedef struct hash_iter hash_iter_t;

typedef void (*hash_destruir_dato_t)(void *);

/* ******************************************************************
 *                    PRIMITIVAS DEL HASH
 * *****************************************************************/


// Crea una hash.
// Pre: Recibe por parametro un destructor para destruir los datos dentro del hash de ser necesario.
// Post: devuelve un nuevo hash vacío.
hash_t *hash_crear(hash_destruir_dato_t destruir_dato);

//Guarda un elemento en el hash, si la clave ya se encuentra en el hash, la reemplaza. De no poder guardarlo devuelve false.
// Pre: El hash fue creado.
// Post: Se guardo la clave y el dato dentro del hash en la misma posicion.
bool hash_guardar(hash_t *hash, const char *clave, void *dato);

// Borra el elemento del hash que este en la clave que se recibe por parametro. Devuelve NULL en caso de que el dato no exista.
// Pre: El hash fue creado.
// Post: se devolvio el elemento borrado del hash.
void *hash_borrar(hash_t *hash, const char *clave);

// Pre: El hash fue creado.
// Post: Se devolvio el dato guardado en una posicion del hash, si la clave no pertenece al hash o la posicion no tiene un dato se devolvio NULL
void *hash_obtener(const hash_t *hash, const char *clave);

// Pre: El hash fue creado
// Post: se devolvio true si la clave existe en el hash, caso contrario se devolvio false
bool hash_pertenece(const hash_t *hash, const char *clave);

// Devuelve la cantidad de elementos que tiene el hash.
// Pre: El hash fue creado
size_t hash_cantidad(const hash_t *hash);

// Destruye el hash y libera la memoria de las posiciones del hash en caso de estar cargadas con algun dato.
// Pre: El hash fue creado
// Post: Se destruyo el hash
void hash_destruir(hash_t *hash);

// Crea un iterador para el hash.
// Post: devuelve un iterador colocado en el primer elemento del hash si es que existe,
// si el hash esta vacio el iterador apunta a NULL.
hash_iter_t *hash_iter_crear(const hash_t *hash);

// Devuelve true en caso de que se pueda avanzar en el hash con el iterador.
// Devuelve false en caso contrario.
bool hash_iter_avanzar(hash_iter_t *iter);

// Devuelve clave en la que esta parado el iterador.
const char *hash_iter_ver_actual(const hash_iter_t *iter);

// Devuelve verdadero o falso, según si el iterador puede o no seguir avanzando en el hash.
// Pre: el iterador fue creado.
bool hash_iter_al_final(const hash_iter_t *iter);

// Destruye el iterador si este ya llego al final del hash.
// Pre: el iterador fue creado.
void hash_iter_destruir(hash_iter_t* iter);

#endif // HASH_H
