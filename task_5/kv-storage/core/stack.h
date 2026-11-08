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

void stack_deinit(Stack_t *stack_ptr);

bool stack_push(Stack_t *stack, Cell_t cell);

/* Ownership of the returned cell.data passes to the caller; release it with stack_cell_free(). */
Cell_t stack_pop(Stack_t *stack);

void stack_cell_free(Cell_t *cell);

#endif
