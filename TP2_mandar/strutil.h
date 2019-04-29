#ifndef STRUTIL_H
#define STRUTIL_H

#include <stdbool.h>

char** split(const char* str, char sep);
char* join(char** stv, char sep);
#endif
