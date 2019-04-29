#ifndef _TESTING_H
#define _TESTING_H

#include <stdbool.h>

// Imprime el mensaje seguido de OK o ERROR. Contabiliza el número
// total de errores en una variable interna.
void print_test(const char* mensaje, bool ok);

// Devuelve el número total de errores registrados por print_test().
int failure_count(void);

#endif // _TESTING_H
