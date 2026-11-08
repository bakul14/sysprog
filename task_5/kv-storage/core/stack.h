#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Stack Stack_t;

Stack_t *stack_init();

void stack_deinit(Stack_t *const stack_ptr);

bool stack_push(Stack_t *const stack, const void *const data, const size_t size);

bool stack_pop(Stack_t *const stack, void **const data, size_t *const size);

void stack_data_free(void **const data);

#endif
