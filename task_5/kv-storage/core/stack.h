#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Stack Stack_t;

typedef struct Cell {
  void *data;
  size_t size;
} Cell_t;

Stack_t *stack_init();

void stack_deinit(Stack_t *const stack_ptr);

bool stack_push(Stack_t *const stack, const Cell_t cell);

Cell_t stack_pop(Stack_t *const stack);

void stack_cell_free(Cell_t *const cell);

#endif
