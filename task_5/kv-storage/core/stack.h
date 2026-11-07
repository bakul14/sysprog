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

bool stack_init(Stack_t *const stack);

void stack_deinit(Stack_t *const stack);

bool stack_push(Stack_t *const stack, const Cell_t cell);

bool stack_pop(Stack_t *const stack, Cell_t *const cell);

#endif
