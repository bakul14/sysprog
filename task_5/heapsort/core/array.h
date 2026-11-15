#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

typedef struct Array Array_t;

Array_t *array_init();

void array_deinit(Array_t *const array);

bool array_push(Array_t *const array, const long long item);

size_t array_size(const Array_t *const array);

long long array_at(const Array_t *const array, const size_t index);

void array_swap(Array_t *const array, const size_t lhs, const size_t rhs);

#endif
