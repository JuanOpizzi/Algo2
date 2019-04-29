#include "vector_dinamico.h"
#include "testing.h"
#include <stdio.h>


/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

/* Pruebas para un vector de tamanio 0. */
void pruebas_vector_nulo() {
    printf("INICIO DE PRUEBAS CON VECTOR DE TAMANIO 0\n");

    /* Declaro las variables a utilizar*/
    vector_t* vec = vector_crear(0);

    /* Inicio de pruebas */
    print_test("crear vector con tamanio 0", vec != NULL);
    print_test("obtener tamanio vector es 0", vector_obtener_tamanio(vec) == 0);

    /* Pruebo que guardar en un vector de tamanio 0 devuelve false siempre (no se puede guardar) */
    print_test("guardar en vec[0] es false", !vector_guardar(vec, 0, 5));
    print_test("guardar en vec[1] es false", !vector_guardar(vec, 1, 10));
    print_test("guardar en vec[15] es false", !vector_guardar(vec, 15, 0));

    /* Pruebo que obtener valores de un vector de tamaño 0 devuelve false */
    int valor;
    print_test("obtener vec[0] es false", !vector_obtener(vec, 0, &valor));
    print_test("obtener vec[1] es false", !vector_obtener(vec, 1, &valor));

    /* Destruyo el vector*/
    vector_destruir(vec);
    print_test("el vector fue destruido", true);
}

/* Pruebas de guardar y obtener algunos elementos*/
void pruebas_vector_algunos_elementos() {
    printf("INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS\n");

    /* Creo un vector de tamanio 5*/
    vector_t* vec2 = vector_crear(5);

    print_test("crear vec2 con tamanio 5", vec2 != NULL);
    print_test("obtener tamanio es 5", vector_obtener_tamanio(vec2) == 5);

    /* Pruebo que guardar en un vector de tamanio 5 funciona para posiciones menores que 5 */
    print_test("guardar 20 en vec2[0] es true", vector_guardar(vec2, 0, 20));
    print_test("guardar 30 en vec2[1] es true", vector_guardar(vec2, 1, 30));
    print_test("guardar 15 en vec2[0] es true", vector_guardar(vec2,0,15));
    print_test("guardar 7 en vec2[4] es true", vector_guardar(vec2, 4, 7));

    /* Pruebo que guardar en un vector de tamanio 5 no funciona para posiciones mayores o iguales que 5 */
    print_test("guardar 35 en vec2[5] es false", !vector_guardar(vec2, 5, 35));
    print_test("guardar 40 en vec2[6] es false", !vector_guardar(vec2, 6, 40));

    /* Pruebo obtener los valores de un vector previamente guardados */
    int valor;
    print_test("se puede obtener vec2[0]", vector_obtener(vec2, 0, &valor));
    print_test("obtener vec2[0] es 15", valor == 15);
    print_test("se puede obtener vec2[1]", vector_obtener(vec2, 1, &valor));
    print_test("obtener vec2[1] es 30", valor == 30);
    print_test("no se puede obtener vec2[5]", !vector_obtener(vec2, 5, &valor));
    print_test("valor no fue modificado", valor == 30);

    /* Destruyo el vector*/
    vector_destruir(vec2);
    print_test("el vector fue destruido", true);
}

/* Pruebas al redimensionar un vector (agrandar y achicar) */
void pruebas_vector_redimension() {
    printf("INICIO DE PRUEBAS DE REDIMENSION\n");
    /* Creo un vector de tamanio 3*/
    vector_t* vec3 = vector_crear(3);

    /* Pruebo guardar elementos en el vector de tamanio 3*/
    print_test("guardar 5 en vec3[0] es true", vector_guardar(vec3, 0, 5));
    print_test("guardar 10 en vec3[1] es true", vector_guardar(vec3, 1, 10));

    /* Pruebo redimensionar (agrandar) el vector */
    print_test("redimensionar a tamanio 10", vector_redimensionar(vec3, 10));
    print_test("El nuevo tamanio del vector es 10", vector_obtener_tamanio(vec3) == 10);

    /* Pruebo que los elementos guardados antes son correctos*/
    int valor;
    print_test("puedo obtener el valor de vec3[0] luego de redimensionar (agrandar)", vector_obtener(vec3, 0, &valor));
    print_test("el valor contenido en vec3[0] es 5", valor == 5);
    print_test("puedo obtener el valor de vec3[1] luego de redimensionar (agrandar)", vector_obtener(vec3, 1, &valor));
    print_test("el valor contenido en vec3[1] es 10", valor == 10);

    /* Pruebo que se pueda agregar ahora en la posicion 5 */
    print_test("guardar 50 en vec3[5] es true, luego de redimensionar", vector_guardar(vec3, 5, 50));
    print_test("puedo obtener el valor de vec3[5], luego de redimensionar", vector_obtener(vec3, 5, &valor));
    print_test("el valor contenido en vec3[5] es 50", valor == 50);

    /* Pruebo redimensionar (achicar) el vector */
    print_test("redimensionar a tamanio 2", vector_redimensionar(vec3, 2));
    print_test("El nuevo tamanio del vector es 2", vector_obtener_tamanio(vec3) == 2);

    /* Pruebo que los elementos de las primeras posiciones sigan estando*/
    print_test("puedo obtener el valor de vec3[0] luego de redimensionar (achicar)", vector_obtener(vec3, 0, &valor));
    print_test("el valor contenido en vec3[0] es 5", valor == 5);
    print_test("puedo obtener el valor de vec3[1] luego de redimensionar (achicar)", vector_obtener(vec3, 1, &valor));
    print_test("el valor contenido en vec3[1] es 10", valor == 10);

    /* Pruebo que no puedo leer lo que esta en la posicion 5*/
    print_test("no puedo obtener el valor de vec3[5] luego de redimensionar (achicar)", !vector_obtener(vec3, 5, &valor));

    /* Puebo que no puedo guardar en la posicion 5*/
    print_test("no puedo guardar 0 en vec3[5] luego de redimensionar (achicar)", !vector_guardar(vec3, 5, 0));

    /* Destruyo el vector*/
    vector_destruir(vec3);
    print_test("el vector fue destruido", true);
}

/* Pruebas del vector al trabajar con un volumen grande de elementos */
void pruebas_vector_volumen() {
    printf("INICIO DE PRUEBAS DE VOLUMEN\n");

    /* Defino el tamanio del vector*/
    size_t tam = 10000;

    /* Creo el vector con ese tamanio*/
    vector_t* vec_vol = vector_crear(tam);

    /* Prueba de correcta creacion del vector */
    print_test("crear vec_vol con tamanio grande", vec_vol != NULL);
    print_test("obtener tamanio vec_vol es el indicado", vector_obtener_tamanio(vec_vol) == tam);

    /* Pruebo guardar en todas las posiciones */
    size_t i;
    bool ok = true;
    for (i = 0; i < tam; i++) {
        // Si algun elemento no se pudo guardar correctamente, ok sera false
        ok &= vector_guardar(vec_vol, i, (int) i);
    }
    print_test("se pudieron guardar todos los elementos", ok);
    print_test("no se puede guardar un elemento en vec_vol[tam]", !vector_guardar(vec_vol, tam, 10));

    /* Pruebo que lo guardado sea correcto */
    ok = true;
    int valor;
    for (i = 0; i < tam; i++) {
        ok &= vector_obtener(vec_vol, i, &valor);
        ok &= (valor == i);
    }
    print_test("se pudieron obtener todos los elementos", ok);
    print_test("no se puede obtener el valor de vec_vol[tam]", !vector_obtener(vec_vol, tam, &valor));

    /* Destruyo el vector*/
    vector_destruir(vec_vol);
    print_test("el vector fue destruido", true);
}


/* Programa principal. */
int main(void) {
    /* Ejecuta todas las pruebas. */
    pruebas_vector_nulo();
    pruebas_vector_algunos_elementos();
    pruebas_vector_redimension();
    pruebas_vector_volumen();

    return failure_count() > 0;
}
