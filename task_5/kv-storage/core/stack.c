#include "stack.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

static inline bool double_stack_(Stack_t *const stack)
{
  bool ret = false;

  void *const new_stack_ptr = realloc((void *const)(stack->cell), (stack->size_) * 2);

  if (nullptr != new_stack_ptr) {
    stack->cell  = new_stack_ptr;
    stack->size_ = stack->size_ * 2;
    ret          = true;
  }

  return ret;
}

bool init(Stack_t *const stack)
{
  bool ret = false;

  constexpr size_t k_initial_stack_depth = 64U;

  Cell_t *const stack_area = (Cell_t *const)calloc(k_initial_stack_depth, sizeof(Cell_t));
  if (nullptr != stack_area) {
    stack->cell  = stack_area;
    stack->size_ = k_initial_stack_depth;
    stack->used_ = 0U;
    ret          = true;
  }

  return ret;
}

bool push(Stack_t *const stack, const Cell_t cell)
{
  bool ret = false;

  if (nullptr != stack) {
    const bool stack_has_free_space = (stack->size_ > stack->used_) || double_stack_(stack);

    if (stack_has_free_space) {
      stack->cell[stack->used_] = cell;
      ++(stack->used_);
      ret = true;
    }
  }

  return ret;
}

bool pop(Stack_t *const stack, Cell_t *const cell)
{
  bool ret = false;

  if (nullptr != stack) {
    const bool stack_is_not_empty = stack->used_ > 0U;

    if (stack_is_not_empty) {
      *cell = stack->cell[stack->used_ - 1U];
      --(stack->used_);
      ret = true;
    }
  }

  return ret;
}
