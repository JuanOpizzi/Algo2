#ifndef COUNTING_H
#define COUNTING_H
#include <stdbool.h>
#include <stddef.h>

typedef struct counting_filters count_t;

count_t* crear_counting();
bool couting_guardar(count_t* count, const char* ht);
size_t obtener_counting(count_t* count, const char* ht);
void destruir_counting(count_t* count);


#endif
