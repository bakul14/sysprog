#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct Stack Stack_t;

Stack_t *stack_init();

void stack_deinit(Stack_t *const stack);

bool stack_push(Stack_t *const stack, const void *const data, const size_t size);

bool stack_pop(Stack_t *const stack, void **const data, size_t *const size);

void stack_data_free(void **const data);

typedef bool (*StackMatch_t)(const void *const data, const size_t size, const void *const key);

// clang-format off
bool stack_find(
  const Stack_t *const stack,
  const StackMatch_t match,
  const void *const key,
  const void **const data_out);
// clang-format on

typedef void (*StackVisit_t)(const void *const data, const size_t size, void *const context);

/* Visits items from top to bottom */
void stack_foreach(const Stack_t *const stack, const StackVisit_t visit, void *const context);

#endif
