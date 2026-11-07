#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Cell {
  const void *data;
} Cell_t;

typedef struct Stack {
  Cell_t *cell;
  size_t size_;
  size_t used_;
} Stack_t;

bool init(Stack_t *const stack);

bool push(Stack_t *const stack, const Cell_t cell);

bool pop(Stack_t *const stack, Cell_t *const cell);

#endif
