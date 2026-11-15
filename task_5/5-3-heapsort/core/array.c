#include "array.h"

#include <stddef.h>
#include <stdlib.h>

typedef struct Array {
  long long *items;
  size_t size;
  size_t used;
} Array_t;

static inline bool double_array_(Array_t *const array)
{
  bool ret = false;

  long long *const new_items = realloc(array->items, array->size * sizeof(long long) * 2U);

  if (nullptr != new_items) {
    array->items = new_items;
    array->size  = array->size * 2U;
    ret          = true;
  }

  return ret;
}

Array_t *array_init()
{
  Array_t *array = malloc(sizeof(Array_t));

  if (nullptr != array) {
    constexpr size_t k_initial_array_size = 64U;

    long long *const items = malloc(k_initial_array_size * sizeof(long long));

    if (nullptr != items) {
      array->items = items;
      array->size  = k_initial_array_size;
      array->used  = 0U;
    } else {
      free(array);
      array = nullptr;
    }
  }

  return array;
}

void array_deinit(Array_t *const array)
{
  if (nullptr != array) {
    free(array->items);
    free(array);
  }
}

bool array_push(Array_t *const array, const long long item)
{
  bool ret = false;

  if (nullptr != array) {
    const bool array_has_free_space = (array->size > array->used) || double_array_(array);

    if (array_has_free_space) {
      array->items[array->used] = item;
      ++(array->used);
      ret = true;
    }
  }

  return ret;
}

size_t array_size(const Array_t *const array)
{
  return (nullptr != array) ? array->used : 0U;
}

long long array_at(const Array_t *const array, const size_t index)
{
  return ((nullptr != array) && (index < array->used)) ? array->items[index] : 0;
}

void array_swap(Array_t *const array, const size_t lhs, const size_t rhs)
{
  if ((nullptr != array) && (lhs < array->used) && (rhs < array->used)) {
    const long long tmp = array->items[lhs];
    array->items[lhs]   = array->items[rhs];
    array->items[rhs]   = tmp;
  }
}
