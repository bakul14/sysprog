#ifndef PARSER_H
#define PARSER_H

#include "../core/array.h"

typedef bool (*ParserRead_t)(const char *const source, Array_t *const array);

bool parser_read_file(const char *const filepath, Array_t *const array);

bool parser_read_string(const char *const string, Array_t *const array);

void parser_print(const Array_t *const array);

#endif
