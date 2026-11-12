#include "stack.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cell {
  void *data;
  size_t size;
} Cell_t;

typedef struct Stack {
  Cell_t *cell;
  size_t size;
  size_t used;
} Stack_t;

static inline bool double_stack_(Stack_t *const stack)
{
  bool ret = false;

  void *const new_stack = realloc((void *const)(stack->cell), (stack->size) * sizeof(Cell_t) * 2U);

  if (nullptr != new_stack) {
    stack->cell = new_stack;
    stack->size = stack->size * 2U;
    ret         = true;
  }

  return ret;
}

Stack_t *stack_init()
{
  Stack_t *stack = malloc(sizeof(Stack_t));

  if (nullptr != stack) {
    constexpr size_t k_initial_stack_depth = 64U;

    Cell_t *const cell_area = (Cell_t *const)malloc(k_initial_stack_depth * sizeof(Cell_t));

    if (nullptr != cell_area) {
      stack->cell = cell_area;
      stack->size = k_initial_stack_depth;
      stack->used = 0U;
    } else {
      free(stack);
      stack = nullptr;
    }
  }

  return stack;
}

void stack_deinit(Stack_t *const stack)
{
  if (nullptr != stack) {
    for (size_t i = 0U; i < stack->used; ++i) {
      free((void *)(stack->cell[i].data));
    }
    free(stack->cell);
    free(stack);
  }
}

bool stack_push(Stack_t *const stack, const void *const data, const size_t size)
{
  bool ret = false;

  if ((nullptr != stack) && (nullptr != data) && (size > 0U)) {
    const bool stack_has_free_space = (stack->size > stack->used) || double_stack_(stack);

    if (stack_has_free_space) {
      void *const data_copy = malloc(size);

      if (nullptr != data_copy) {
        memcpy(data_copy, data, size);
        stack->cell[stack->used].data = data_copy;
        stack->cell[stack->used].size = size;
        ++(stack->used);
        ret = true;
      }
    }
  }

  return ret;
}

bool stack_pop(Stack_t *const stack, void **const data, size_t *const size)
{
  bool ret = false;

  if ((nullptr != stack) && (nullptr != data) && (nullptr != size)) {
    const bool stack_is_not_empty = stack->used > 0U;

    if (stack_is_not_empty) {
      const Cell_t cell             = stack->cell[stack->used - 1U];
      stack->cell[stack->used - 1U] = (Cell_t){.data = nullptr, .size = 0U};
      --(stack->used);
      *data = cell.data;
      *size = cell.size;
      ret   = true;
    }
  }

  return ret;
}

void stack_data_free(void **const data)
{
  if (nullptr != data) {
    free(*data);
    *data = nullptr;
  }
}
